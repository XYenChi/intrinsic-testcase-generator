"""
Generate execute file by operator
"""
import operator_py_function
import random
import sys
import math

# set VLEN as 64 bit

op = sys.argv[1]
Q_array = 16
avl = 64
_vx = ['v', 'x']
_wv = ['v', 'w']
_iu = ['i', 'u']
_ext = ['f2', 'f4', 'f8']
# 'i' for signed int, 'u' for unsigned int
_suffix = ['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8',
           '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4',
           '32m1', '32m2', '32m4', '32m8', '32mf2',
           '64m1', '64m2', '64m4', '64m8']
_widen_suffix = ['16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4',
                 '32m1', '32m2', '32m4', '32m8', '32mf2',
                 '64m1', '64m2', '64m4', '64m8']
_narrow_suffix = ['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8',
                  '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4',
                  '32m1', '32m2', '32m4', '32m8', '32mf2']
_mask = ['', '_m']
_middle_mask = ['', 'm']
IntegerOpList = ['vadc', 'vadd', 'vand', 'vdiv', 'vdivu', 'vmacc', 'vmadc', 'vmadd', 'vmax', 'vmaxu', 'vmerge', 'vmin',
                 'vminu', 'vmsbc', 'vmseq', 'vmsge', 'vmsgeu', 'vmsgt', 'vmsgtu', 'vmsle', 'vmsleu', 'vmslt', 'vmsltu',
                 'vmsne', 'vmul', 'vmulh', 'vmulhsu', 'vmulhu', 'vmv', 'vneg', 'vnmsac', 'vnmsub', 'vnot', 'vnsra',
                 'vnsrl', 'vor', 'vrem', 'vremu', 'vrsub', 'vsbc', 'vsext', 'vsll', 'vsra', 'vsrl', 'vsub', 'vwadd',
                 'vwaddu', 'vwmacc', 'vwmaccsu', 'vwmaccu', 'vwmaccus', 'vwmul', 'vwmulsu', 'vwmulu', 'vwsub', 'vwsubu',
                 'vxor', 'vzext']
GeneralFormatOpList = ['vadd', 'vand', 'vmacc', 'vmadd', 'vmseq', 'vmsne', 'vmul', 'vnmsac', 'vnmsub', 'vor', 'vrsub',
                       'vsll', 'vsub', 'vxor']
# loop _vx, _iu, _suffix, _mask
SpMaskOpList = ['vadc', 'vmerge']
# loop _vx, _iu, _suffix, have to with middle mask
Sp2MaskOpList = ['vmadc', 'vmsbc']
# loop _vx, _iu, _suffix, and middle mask. don't have _mask
SignOpList = ['vdiv', 'vmax', 'vmin', 'vmsge', 'vmsgt', 'vmsle', 'vmslt', 'vmulh', 'vmulhsu', 'vrem', 'vsra', 'vwmacc',
              'vwmaccsu', 'vwmul', 'vwmulsu']
# loop _vx, _suffix, _mask, with fixed i
WSignOpList = ['vnsra', 'vwmaccus']
# loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
SpWsignOpList = ['vwadd', 'vwsub']
# loop _wv, _vx , _suffix, _mask, with fixed i
UnsignOpList = ['vdivu', 'vmaxu', 'vminu', 'vmsgeu', 'vmsgtu', 'vmsleu', 'vmsltu', 'vmulhu', 'vremu', 'vsrl', 'vwmaccu',
                'vwmaccu', 'vwmulu']
# loop _vx, _suffix, _mask with fixed u
WUnsignOpList = ['vnsrl']
# loop different position _vx , _suffix, _mask, with fixed u
SpWUnsignOpList = ['vwaddu', 'vwsubu']
# loop _wv, _vx , _suffix, _mask, with fixed u
SpecialFormatList = ['vmv']
# loop _iu, _suffix and _vx with "_"
SpVOplist = ['vneg']
# loop _suffix, _mask and only v, with fixed i
Sp2VOplist = ['vnot']
# loop _suffix, _iu, _mask and only v
ExtOpList = ['vsext', 'vzext']
# loop _ext, _suffix, _mask with fixed i(vsext) or u(vzext)
lmul_dict = {'1': 1, '2': 2, '4': 4, '8': 8, 'f2': 0.5, 'f4': 0.25, 'f8': 0.125}

def cross(*args):
    list = [()]
    for i in args:
        list = [(*o, n) for o in list for n in i]
    return list

class Node:
    def __init__(self, sign):
        self.op = op
        self.op_mask = ""
        # pass different parameter sequence
        self.lmul = 0.0
        self.sew = 8
        self.mask = None
        # If _mask = '_m', vm = 0, masked, calculate if mask array[i] = 1
        self.carryin = None
        # vmadc don't have mask and must have carry in bit
        self.sign = sign
        if self.sign == 'i':
            self.vtype = 'int'
            self.max = pow(2, self.sew-1)-1
            self.min = -pow(2, self.sew-1)
        else:
            self.vtype = 'uint'
            self.max = pow(2, self.sew)-1
            self.min = 0
        self.Q_A_E = 16
        self.range = pow(2, self.sew)
        self.masked = [0] * Q_array
        self.data1 = [0] * Q_array
        self.data2 = [0] * Q_array
        self.vd_default = [0] * Q_array
        self.out = [0] * Q_array
        self.val = None
        self.golden = [0] * Q_array
        self.random_gen()
        self.compute()

    def compiler_option_write(self):
        fd.write("/* { dg-do run } */\n")
        fd.write(
            "/* { dg-options \"-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w\" } */\n")

    def c_header_file_write(self):
        fd.write("#include <stdlib.h>\n")
        fd.write("#include <stdio.h>\n")
        fd.write("#include <string.h>\n")
        fd.write("#include \"riscv_vector.h\"\n")

    def vl_set_write(self):
        fd.write("    size_t avl = 64;\n")
        fd.write("    size_t vl = __riscv_vsetvl_e%s(avl);\n" % suffix)

    def c_main_entry_write(self):
        fd.write("int main(){\n")

    def pointer_iterator_write(self):
        fd.write("    for (size_t n = 0; n < vl; n++) {\n")

    def vs2_load(self):
        if self.mask == 0:
            fd.write("    v%s%s_t data1_v = __riscv_vle%s_v_%s%s%s (mask, in1, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix, mask))
        else:
            fd.write("    v%s%s_t data1_v = __riscv_vle%s_v_%s%s (in1, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix))

    def vs1_load(self):
        if self.mask == 0:
            fd.write("    v%s%s_t data2_v = __riscv_vle%s_v_%s%s%s (mask, in2, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix, mask))
        else:
            fd.write("    v%s%s_t data2_v = __riscv_vle%s_v_%s%s (in2, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix))

    def vd_load(self):
        if self.mask == 0:
            fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s%s (mask, out, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix, mask))
        else:
            fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s (out, vl);\n"
                     % (a.vtype, suffix, a.sew, a.sign, suffix))

    # def mask_load(self):
    # todo: load mask
    def vd_store(self):
        if self.mask == 0:
            fd.write("        void __riscv_vse%s_v_%s%s (bool%s_t mask, %s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                     % (a.sew, iu, suffix, a.sew, a.vtype, a.sew, a.vtype, suffix))
        else:
            fd.write("        void __riscv_vse%s_v_%s%s (%s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                     % (a.sew, iu, suffix, a.vtype, a.sew, a.vtype, suffix))

    def parameter_seq_write(self):
        # todo: generate all the operate by default
        # else:
        #    for op in IntegerOpList:
        #        return "    vint%s_t out = __riscv_%s_v%s_i%s (" % (suffix, op, vx, suffix)

        match self.op_mask:
            case 'vadd':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, data2_v, vl);\n" % (op, vx, iu, suffix, mask))
            #case 'vadd_m':
            #    fd.write(
            #        "        out_v = __riscv_%s_v%s_%s%s%s (mask, data1_v, data2_v, vl);\n"
            #        % (op, vx, iu, suffix, mask))
            case 'vsub':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vsub_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vmul':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmul_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vdiv':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vdiv_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmax':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmax_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmin':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmin_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vrem':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vrem_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vadc':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, mask, vl);\n" % (op, vx, suffix, mask))
            case 'vsbc':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vsbc_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, data2_v, vl);\n" % (op, vx, suffix, mask))
            case 'vmerge':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, data2_v, size_t vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vmacc':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vmacc_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vmadd':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
                # default vd will be passed as out_data
            case 'vmadd_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vmsbc':
                fd.write(
                    "        out_v = __riscv_%s_v%s%s_%s%s_b%s (data1_v, data2_v, vl);\n"
                    % (op, vx, mask, iu, suffix, int(self.sew / self.lmul)))
            case 'vmsbc_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s%s_%s%s_b%s (data1_v, data2_v, mask, vl);\n"
                    % (op, vx, mask, iu, suffix, int(self.sew / self.lmul)))
            case 'vmadc':
                fd.write(
                    "        out_v = __riscv_%s_v%s%s_%s_b%s(data1_v, data2_v, vl);\n"
                    % (op, vx, mask, suffix, int(self.sew / self.lmul)))
            case 'vmadc_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s%s_%s_b%s (data1_v, data2_v, carryin, vl);\n"
                    % (op, vx, mask, suffix, int(self.sew / self.lmul)))
            case 'vmseq':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmseq_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsge':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsge_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsgt':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsgt_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsgtu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsgtu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsle':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsle_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmslt':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmslt_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsne':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmsne_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul), mask))
            case 'vmulh':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmulh_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmulhsu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmulhsu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmsgeu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmsgeu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s_b%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, int(self.sew / self.lmul)))
            case 'vmv':
                fd.write(
                    "        out_v = __riscv_%s_v_%s_%s%s (src, vl);\n"
                    % (op, vx, iu, suffix))
            case 'vneg':
                fd.write(
                    "        out_v = __riscv_%s_v_%s (data1_v, vl);\n"
                    % (op, suffix))
            case 'vneg_m':
                fd.write(
                    "        out_v = __riscv_%s_v_%s (mask, data1_v, vl);\n"
                    % (op, suffix))
            case 'vnmsac':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
                # default vd will be passed as out_data
            case 'vnmsac_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vnmsub':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
                # default vd will be passed as out_data
            case 'vnmsub_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vnot':
                fd.write(
                    "        out_v = __riscv_%s_v_%s%s (data1_v, vl);\n"
                    % (op, iu, suffix))
            case 'vnot_m':
                fd.write(
                    "        out_v = __riscv_%s_v_%s%s (mask, data1_v, vl);\n"
                    % (op, iu, suffix))
            case 'vnsra':
                fd.write(
                    "        out_v = __riscv_%s_w%s_%s%s (data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vnsra_m':
                fd.write(
                    "        out_v = __riscv_%s_w%s_%s%s (mask, data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vnsrl':
                fd.write(
                    "        out_v = __riscv_%s_w%s_%s%s (data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vnsrl_m':
                fd.write(
                    "        out_v = __riscv_%s_w%s_%s%s (mask, data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vor':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vor_m':
                fd.write(
                    "        out_v = __riscv_%s_w%s_%s%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, iu, mask))
            case 'vremu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vremu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vrsub':
                fd.write(
                    "        out_v = __riscv_%s_vx_%s%s%s (data1_v, data2_v, vl);\n"
                    % (op, iu, suffix, mask))
            case 'vrsub_m':
                fd.write(
                    "        out_v = __riscv_%s_vx_%s%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, iu, suffix, mask))
            case 'vsext':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, vl);\n"
                    % (op, ext, suffix, mask))
            case 'vsext_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, vl);\n"
                    % (op, ext, suffix, mask))
            case 'vzext':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (data1_v, vl);\n"
                    % (op, ext, suffix, mask))
            case 'vzext_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (mask, data1_v, vl);\n"
                    % (op, ext, suffix, mask))
            case 'vnsll':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, shift, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vnsll_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, data1_v, shift, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vsra':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vsra_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, data1_v, shift, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vsrl':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (data1_v, shift, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vsrl_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_%s%s%s (mask, data1_v, shift, vl);\n"
                    % (op, vx, iu, suffix, mask))
            case 'vwadd':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_i%s%s (data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwadd_m':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_i%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwaddu':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_u%s%s (data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwaddu_m':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_u%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwmacc':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmacc_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccsu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccsu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccus':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmaccus_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmul':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmul_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmulsu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmulsu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_i%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmulu':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwmulu_m':
                fd.write(
                    "        out_v = __riscv_%s_v%s_u%s%s (mask, out_data, data1_v, data2_v, vl);\n"
                    % (op, vx, suffix, mask))
            case 'vwsub':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_i%s%s (data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwsub_m':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_i%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwsubu':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_u%s%s (data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vwsubu_m':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_u%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, wv, vx, suffix, mask))
            case 'vxor':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_%s%s%s (data1_v, data2_v, vl);\n"
                    % (op, wv, vx, iu, suffix, mask))
            case 'vxor_m':
                fd.write(
                    "        out_v = __riscv_%s_%s%s_%s%s%s (mask, data1_v, data2_v, vl);\n"
                    % (op, wv, vx, iu, suffix, mask))

    def jump_to_next_write_mask(self):
        fd.write("        in1 += %s;\n" % int(self.sew / 8))
        if op == 'vnot':
            return
        else:
            fd.write("        in2 += %s;\n" % int(self.sew / 8))
        fd.write("        out += %s;\n" % int(self.sew / 8))
        fd.write("        mask += %s;\n" % int(self.sew / 8))
        fd.write("      }\n")

    def jump_to_next_write_wo_mask(self):
        fd.write("        in1 += %s;\n" % int(self.sew / 8))
        if op == 'vmv' or op == 'vneg':
            return
        else:
            fd.write("        in2 += %s;\n" % int(self.sew / 8))
        fd.write("        out += %s;\n" % int(self.sew / 8))
        fd.write("      }\n")

    def report_write(self):
        fd.write("    int fail = 0;\n")
        fd.write("    for (int i = 0; i < %d; i++){\n" % Q_array)
        fd.write("        if (golden[i] != out_data[i]) {\n")
        fd.write("            printf (\"idx=%d golden=%d out=%d\\n\", i, golden[i], out_data[i]);\n")
        fd.write("            fail++;\n")
        fd.write("            }\n")
        fd.write("        }\n")
        fd.write("    if (fail) {\n")
        # fd.write("    printf(\"FAIL\\n\");\n")
        fd.write("        return 1;\n")
        fd.write("    } else {\n")
        # fd.write("    printf(\"PASS\\n\");\n")
        fd.write("        return 0;\n")
        fd.write("    }\n")
        fd.write("}\n")

    def random_gen(self):
        for i in range(Q_array):
            self.data1[i] = random.randint(self.min, self.max)
            self.data2[i] = random.randint(self.min, self.max)
            self.vd_default[i] = random.randint(0, 1)


    def mask_gen(self):
        for i in range(self.Q_A_E):
            if self.mask:
                # if vm = 1, no matter what v0.mask[i] is equal to, calculate will continue, so do nothing and return.
                self.masked[i] = 1
            else:
                # if vm = 0, only when v0.mask[i] = 1, calculate would continue.
                self.masked[i] = random.randint(0, 1)

    def vs2_data_write(self):
        fd.write("    const %s%s_t data1[] = {\n" % (self.vtype, self.sew))
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.data1)))
        fd.write("    };\n")
        fd.write("    const %s%s_t *in1 = &data1[0];\n" % (self.vtype, self.sew))

    def vs1_data_write(self):
        fd.write("    const %s%s_t data2[] = {\n" % (self.vtype, self.sew))
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.data2)))
        fd.write("    };\n")
        fd.write("    const %s%s_t *in2 = &data2[0];\n" % (self.vtype, self.sew))

    def vd_declaration_write(self):
        fd.write("    const %s%s_t out_data[%s];\n" % (self.vtype, self.sew, Q_array))
        # Declare the array of 10 elements
        fd.write("    const %s%s_t *out = &out_data[0];\n" % (self.vtype, self.sew))

    def vd_default_write(self):
        fd.write("    const %s out_data[] = {\n" % self.vtype)
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.vd_default)))
        fd.write("    };\n")
        fd.write("    const %s%s_t *out = &out_data[0];\n" % (self.vtype, self.sew))

    def vd_mask_default_write(self):
        # todo: load vd mask
        fd.write("    const bool%s_t vd_mask_data[%s];\n" % (self.sew, Q_array))
        fd.write("    const bool%s_t *vd_mask = &vd_mask_data[0];\n" % self.sew)

    def mask_data_write(self):
        # todo: mask type
        fd.write("    uint%s_t masked[] = {\n" % int(self.sew / self.lmul))
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.masked)))
        fd.write("    };\n")
        fd.write("    const uint%s_t *mask = &masked[0];\n" % int(self.sew / self.lmul))

    def golden_by_python_write(self):
        fd.write("    %s%s_t golden[] = {\n" % (self.vtype, self.sew))
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.golden)))
        fd.write("    };\n")

    def compute(self):
        op_list = {
            "vadd": operator_py_function.add_op,
            "vand": operator_py_function.and_op,
            "vsub": operator_py_function.sub_op,
            "vmul": operator_py_function.mul_op,
            "vdiv": operator_py_function.div_op,
            "vmax": operator_py_function.max_op,
            "vmin": operator_py_function.min_op,
            "vrem": operator_py_function.reminder,
            "vremu": operator_py_function.reminder,
            "vadc": operator_py_function.add_with_carry_op,
            "vsbc": operator_py_function.sub_with_borrow_op,
            "vmerge": operator_py_function.merge_op,
            "vmacc": operator_py_function.multiply_add_overwrite_addend_op,
            "vmadd": operator_py_function.multiply_add_overwrite_multiplicand_op,
            "vmsbc": operator_py_function.multiply_sbc_overwrite_multiplicand_op,
            "vmseq": operator_py_function.equal_to_op,
            "vmv": operator_py_function.move_op,
            "vneg": operator_py_function.neg_op,
            "vnot": operator_py_function.not_op,
            "vmadc": operator_py_function.add_with_carry_return_mask_op,
            "vnmsac": operator_py_function.nmsac_op,
            "vnmsub": operator_py_function.nmsub_op,
            "vor": operator_py_function.or_op,
            "vsra": operator_py_function.sra_op

        }
        if op in GeneralFormatOpList or op in SignOpList or op in UnsignOpList:
            if self.mask:
                for i in range(self.Q_A_E):
                    if op == "vnmsac" or op == "vnmsub":
                        self.golden[i] = op_list[op](self.data1[i], self.data2[i], self.vd_default[i])
                    else:
                        self.golden[i] = op_list[op](self.data1[i], self.data2[i])
                    self.golden[i] = self.golden[i] & (2**self.sew-1)
            else:
                for i in range(self.Q_A_E):
                    self.golden[i] = op_list[op](
                        self.data1[i], self.data2[i], self.vd_default[i], self.masked[i])
                    self.golden[i] = self.golden[i] & (2**self.sew-1)
        elif op in SpMaskOpList:
            for i in range(self.Q_A_E):
                self.golden[i] = op_list[op](
                    self.data1[i], self.data2[i], self.masked[i])
        elif op == 'vmv' or op == 'vneg':
            for i in range(self.Q_A_E):
                self.golden[i] = op_list[op](self.data1[i])
        elif op == 'vnot':
            if self.mask:
                for i in range(self.Q_A_E):
                    self.golden[i] = op_list[op](self.data1[i])
            else:
                for i in range(self.Q_A_E):
                    self.golden[i] = op_list[op](self.data1[i], self.vd_default[i], self.masked[i])
        elif op in Sp2MaskOpList:
            if self.mask:
                for i in range(self.Q_A_E):
                    self.golden[i] = 1 if op_list[op](self.data1[i], self.data2[i], self.vd_default[i], self.masked[i])>self.max else 0
                    self.golden[i] = 1 if op_list[op](self.data1[i], self.data2[i], self.vd_default[i], self.masked[i])<self.min else 0
            else:
                for i in range(self.Q_A_E):
                    self.golden[i] = 1 if op_list[op](self.data1[i], self.data2[i], self.vd_default[i])>self.max else 0
                    self.golden[i] = 1 if op_list[op](self.data1[i], self.data2[i], self.vd_default[i])<self.min else 0
        elif op == "vsra" or op == "vsrl":
            shift = log(2, self.sew)
            for i in range(self.Q_A_E):
                self.golden[i] =
for temp in GeneralFormatOpList:
    if op != temp:
        continue
    else:
        for suffix, vx, mask, iu in cross(_suffix, _vx, _mask, _iu):
            a = Node(iu)
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_v%s_%s%s%s.c" % (op, vx, iu, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_declaration_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_wo_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_default_write()
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    a.mask_data_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    # a.specific_operator_c()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
for temp in SpMaskOpList:
    # SpMaskOpList = ['vadc', 'vmerge']
    # loop _vx, _iu, _suffix, have to with middle mask
    if op != temp:
        continue
    else:
        for suffix, vx, iu in cross(_suffix, _vx, _iu):
            a = Node(iu)
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.range = pow(2, a.sew)
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_v%sm_%s%s.c" % (op, vx, iu, suffix)
            with open(filename, 'w') as fd:
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.mask_gen()
                a.mask_data_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
for temp in Sp2MaskOpList:
    # Sp2MaskOpList = ['vmadc', 'vmsbc']
    # loop _vx, _iu, _suffix, and middle mask. don't have _mask
    if op != temp:
        continue
    else:
        for vx, iu, suffix, mask in cross(_vx, _iu, _suffix, _middle_mask):
            a = Node(iu)
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.range = pow(2, a.sew)
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_v%s%s_%s%s.c" % (op, vx, mask, iu, suffix)
            with open(filename, 'w') as fd:
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                # a.mask_gen()
                # a.mask_data_write()
                # todo: a special mask write function if masked, write 1s, else 0s.
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
for temp in SignOpList:
    # SignOpList = ['vdiv', 'vmax', 'vmin', 'vmsge', 'vmsgt', 'vmsle', 'vmslt', 'vmulh', 'vmulhsu', 'vrem',
    #              'vsra', 'vwmacc',
    #              'vwmaccsu', 'vwmul', 'vwmulsu']
    # loop _vx, _suffix, _mask, with fixed i
    if op != temp:
        continue
    else:
        for suffix, vx, mask in cross(_suffix, _vx, _mask):
            a = Node('i')
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.range = pow(2, a.sew)
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_v%s_i%s%s.c" % (op, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            iu = 'i'
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_declaration_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_wo_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_default_write()
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    a.mask_data_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    # a.specific_operator_c()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
for temp in UnsignOpList:
    # UnsignOpList = ['vdivu', 'vmaxu', 'vminu', 'vmsgeu', 'vmsgtu', 'vmsleu', 'vmsltu', 'vmulhu', 'vremu', 'vsrl',
    # 'vwmaccu', 'vwmaccu', 'vwmulu']
    # loop _vx, _suffix, _mask with fixed u
    if op != temp:
        continue
    else:
        for suffix, vx, mask in cross(_suffix, _vx, _mask):
            a = Node('u')
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.range = pow(2, a.sew)
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_v%s_u%s%s.c" % (op, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            iu = 'u'
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_declaration_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_wo_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_default_write()
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    a.mask_data_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    # a.specific_operator_c()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
if op == 'vwmaccus':
    # WSignOpList = ['vnsra', 'vwmaccus']
    # loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
    for suffix, mask in cross(_widen_suffix, _mask):
        a = Node(iu)
        a.op = op
        divider = suffix.split('m')
        a.sew = int(divider[0])
        a.range = pow(2, a.sew)
        a.lmul = lmul_dict["%s" % divider[1]]
        filename = "testcase/%s_vx_i%s%s.c" % (op, suffix, mask)
        a.op_mask = "%s%s" % (op, mask)
        a.sign = 'i'
        if mask != '_m':
            with open(filename, 'w') as fd:
                a.mask = 1
                # don't hava mask
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_declaration_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_wo_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
        else:
            with open(filename, 'w') as fd:
                a.mask = 0
                # mask and have v0.mask[i] value
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                a.mask_data_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
if op == 'vnsra' or op == 'vnsrl':
    # WSignOpList = ['vnsra', 'vwmaccus']
    # loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
    for suffix, mask, vx in cross(_narrow_suffix, _mask, _vx):
        a = Node(iu)
        a.op = op
        divider = suffix.split('m')
        a.sew = int(divider[0])
        a.range = pow(2, a.sew)
        a.lmul = lmul_dict["%s" % divider[1]]
        if op == 'vnsra':
            filename = "testcase/%s_w%s_i%s%s.c" % (op, vx, suffix, mask)
            a.sign = 'i'
        else:
            filename = "testcase/%s_w%s_u%s%s.c" % (op, vx, suffix, mask)
            a.sign = 'u'
        a.op_mask = "%s%s" % (op, mask)
        if mask != '_m':
            with open(filename, 'w') as fd:
                a.mask = 1
                # don't hava mask
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_declaration_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_wo_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
        else:
            with open(filename, 'w') as fd:
                a.mask = 0
                # mask and have v0.mask[i] value
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                a.mask_data_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
for temp in SpWUnsignOpList:
    if op != temp:
        continue
    # SpWUnsignOpList = ['vwaddu', 'vwsubu']
    # loop _wv, _vx , _suffix, _mask, with fixed u
    else:
        for wv, vx, suffix, mask in cross(_wv, _vx, _widen_suffix, _mask):
            a = Node(iu)
            a.op = op
            divider = suffix.split('m')
            a.sew = int(divider[0])
            a.range = pow(2, a.sew)
            a.lmul = lmul_dict["%s" % divider[1]]
            filename = "testcase/%s_%s%s_u%s%s.c" % (op, wv, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_declaration_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_wo_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    a.compiler_option_write()
                    a.c_header_file_write()
                    a.c_main_entry_write()
                    a.random_gen()
                    a.vs2_data_write()
                    a.vs1_data_write()
                    a.vl_set_write()
                    a.vd_default_write()
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    a.mask_data_write()
                    a.vs2_load()
                    a.vs1_load()
                    a.vd_load()
                    a.pointer_iterator_write()
                    # a.specific_operator_c()
                    a.parameter_seq_write()
                    a.vd_store()
                    a.jump_to_next_write_mask()
                    a.compute()
                    a.golden_by_python_write()
                    a.report_write()
if op == 'vmv':
    # loop _iu, _suffix and _vx with "_"
    for iu, suffix, vx in cross(_iu, _suffix, _vx):
        a = Node(iu)
        a.op_mask = op
        divider = suffix.split('m')
        a.sew = int(divider[0])
        a.range = pow(2, a.sew)
        a.lmul = lmul_dict["%s" % divider[1]]
        filename = "testcase/%s_v_%s_%s%s.c" % (op, vx, iu, suffix)
        with open(filename, 'w') as fd:
            a.mask = 1
            # don't hava mask
            a.compiler_option_write()
            a.c_header_file_write()
            a.c_main_entry_write()
            a.random_gen()
            a.vs2_data_write()
            a.vl_set_write()
            a.vd_declaration_write()
            a.vs2_load()
            a.vd_load()
            a.pointer_iterator_write()
            a.parameter_seq_write()
            a.vd_store()
            a.jump_to_next_write_wo_mask()
            a.compute()
            a.golden_by_python_write()
            a.report_write()
if op == 'vneg' or op == 'vnot':
    # SpVOplist = ['vneg']
    # loop _suffix, _mask and only v, with fixed i
    # Sp2VOplist = ['vnot']
    # loop _suffix, _iu, _mask and only v
    for suffix, mask, iu in cross(_suffix, _mask, _iu):
        a = Node(iu)
        a.op = op
        divider = suffix.split('m')
        a.sew = int(divider[0])
        a.range = pow(2, a.sew)
        a.lmul = lmul_dict["%s" % divider[1]]
        if op == 'vneg':
            if iu == 'i':
                filename = "testcase/%s_v_i%s%s.c" % (op, suffix, mask)
        else:
            filename = "testcase/%s_v_%s%s%s.c" % (op, iu, suffix, mask)
        a.op_mask = "%s%s" % (op, mask)
        if mask != '_m':
            with open(filename, 'w') as fd:
                a.mask = 1
                # don't hava mask
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vl_set_write()
                a.vd_declaration_write()
                a.vs2_load()
                a.vd_load()
                a.pointer_iterator_write()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_wo_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
        else:
            with open(filename, 'w') as fd:
                a.mask = 0
                # mask and have v0.mask[i] value
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vl_set_write()
                a.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                a.mask_data_write()
                a.vs2_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
# ExtOpList = ['vsext', 'vzext']
# loop _ext, _suffix, _mask with fixed i(vsext) or u(vzext)
if op == 'vsext' or op == 'vzext':
    for ext, suffix, mask in cross(_ext, _suffix, _mask):
        a = Node(iu)
        a.op = op
        if op == 'vsext':
            filename = "testcase/%s_v%s_i%s%s.c" % (op, ext, suffix, mask)
            a.sign = 'i'
        else:
            filename = "testcase/%s_v%s_u%s%s.c" % (op, ext, suffix, mask)
            a.sign = 'u'
        if mask != '_m':
            with open(filename, 'w') as fd:
                a.mask = 1
                # don't hava mask
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_declaration_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_wo_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
        else:
            with open(filename, 'w') as fd:
                a.mask = 0
                # mask and have v0.mask[i] value
                a.compiler_option_write()
                a.c_header_file_write()
                a.c_main_entry_write()
                a.random_gen()
                a.vs2_data_write()
                a.vs1_data_write()
                a.vl_set_write()
                a.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                a.mask_data_write()
                a.vs2_load()
                a.vs1_load()
                a.vd_load()
                a.pointer_iterator_write()
                # a.specific_operator_c()
                a.parameter_seq_write()
                a.vd_store()
                a.jump_to_next_write_mask()
                a.compute()
                a.golden_by_python_write()
                a.report_write()
