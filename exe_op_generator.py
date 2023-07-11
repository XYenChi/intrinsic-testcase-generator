"""
Generate execute file by operator
"""
import collector
import filter
import random
import sys
import intrinsic_function_type_05
import intrinsic_function_type_06

sys.path.append("./rvv-intrinsic-doc/rvv-intrinsic-generator/rvv_intrinsic_gen")
import math
import utils
import generator
import enums
import constants
import C_lines_write
import transformed_op_function
# set VLEN as 64 bit

op = sys.argv[1]
q_array = 16
avl = 64

# 'i' for signed int, 'u' for unsigned int

mask_list = ['', '_m']
middle_mask_list = ['', 'm']

def cross(*args):
    list = [()]
    for i in args:
        list = [(*o, n) for o in list for n in i]
    return list

for sew, lmul in cross(constants.SEWS, constants.LMULS):
    if sew/utils.get_float_lmul(lmul) <= 64:
        filter.normal_suffix.append(f'{sew}m{lmul}')
    else:
        continue
for sew, lmul in cross(constants.FSEWS, constants.WLMULS):
    if sew/utils.get_float_lmul(lmul) <= 64:
        filter.widen_suffix.append(f'{sew}m{lmul}')
    else:
        continue
for sew, lmul in cross(constants.WSEWS, constants.LMULS):
    if sew/utils.get_float_lmul(lmul) <= 64:
        filter.widen_suffix.append(f'{sew}m{lmul}')
    else:
        continue
class extra_inst_info(enums.InstInfo):
    def __init__(self,
                 iu,
                 SEW,
                 LMUL,
                 OP):
        super().__init__(SEW, LMUL, OP)
        self.SEW = SEW
        self.LMUL = LMUL
        self.OP = OP
        self.op_mask = ""
        self.mask = None
        # If _mask = '_m', vm = 0, masked, calculate if mask array[i] = 1
        self.carryin = None
        # vmadc don't have mask and must have carry in bit
        self.sign = iu
        if self.sign == 'i':
            self.vtype = 'int'
            self.max = pow(2, self.SEW-1)-1
            self.min = -pow(2, self.SEW-1)
        else:
            self.vtype = 'uint'
            self.max = pow(2, self.SEW)-1
            self.min = 0
        self.Q_A_E = 16
        self.range = pow(2, self.SEW)
        self.masked = [0] * q_array
        self.data1 = [0] * q_array
        self.data2 = [0] * q_array
        self.vd_default = [0] * q_array
        self.out = [0] * q_array
        self.val = None
        self.golden = [0] * q_array
        self.random_gen()
        self.compute()
        self.vxrm = random.randint(0, 3)
        # todo: fix-point: save CSR


    def random_gen(self):
        for i in range(q_array):
            self.data1[i] = random.randint(self.min, self.max)
            if op == "vmulhsu":
                self.data2[i] = random.randint(0, 2*self.max)
            else:
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



    def compute(self):
        op_list = {
            # "vneg": transformed_op_function.vneg_op,
            # "vadc": transformed_op_function.vadc_op,
            # "vnmsub": transformed_op_function.vnmsub_op,
            # "vremu": transformed_op_function.vremu_op,
            # "vmsltu": transformed_op_function.vmsltu_op,
            # "vsext": transformed_op_function.vsext_op,
            # "vnot": transformed_op_function.vnot_op,
            # "vwmaccsu": transformed_op_function.vwmaccsu_op,
            # "vrsub": transformed_op_function.vrsub_op,
            # "vwmulu": transformed_op_function.vwmulu_op,
            # "vwmaccus": transformed_op_function.vwmaccus_op,
            # "vrem": transformed_op_function.vrem_op,
            # "vmsne": transformed_op_function.vmsne_op,
            # "vsbc": transformed_op_function.vsbc_op,
            # "vmsleu": transformed_op_function.vmsleu_op,
            # "vminu": transformed_op_function.vminu_op,
            # "vmsgtu": transformed_op_function.vmsgtu_op,
            # "vwsubu": transformed_op_function.vwsubu_op,
            # "vwmul": transformed_op_function.vwmul_op,
            # "vmsbc": transformed_op_function.vmsbc_op,
            # "vnsra": transformed_op_function.vnsra_op,
            # "vwmacc": transformed_op_function.vwmacc_op,
            # "vmsle": transformed_op_function.vmsle_op,
            # "vxor": transformed_op_function.vxor_op,
            # "vdivu": transformed_op_function.vdivu_op,
            # "vmin": transformed_op_function.vmin_op,
            # "vnmsac": transformed_op_function.vnmsac_op,
            # "vor": transformed_op_function.vor_op,
            # "vmulhsu": transformed_op_function.vmulhsu_op,
            # "vmseq": transformed_op_function.vmseq_op,
            # "vwmaccu": transformed_op_function.vwmaccu_op,
            # "vmsgt": transformed_op_function.vmsgt_op,
            # "vsra": transformed_op_function.vsra_op,
            # "vwadd": transformed_op_function.vwadd_op,
            # "vmulh": transformed_op_function.vmulh_op,
            # "vsub": transformed_op_function.vsub_op,
            # "vsll": transformed_op_function.vsll_op,
            # "vmacc": transformed_op_function.vmacc_op,
            # "vmul": transformed_op_function.vmul_op,
            # "vmadc": transformed_op_function.vmadc_op,
            # "vsrl": transformed_op_function.vsrl_op,
            # "vwsub": transformed_op_function.vwsub_op,
            # "vdiv": transformed_op_function.vdiv_op,
            # "vmsge": transformed_op_function.vmsge_op,
            # "vmaxu": transformed_op_function.vmaxu_op,
            # "vmadd": transformed_op_function.vmadd_op,
            # "vmerge": transformed_op_function.vmerge_op,
            # "vnsrl": transformed_op_function.vnsrl_op,
            # "vzext": transformed_op_function.vzext_op,
            # "vmax": transformed_op_function.vmax_op,
            "vadd": transformed_op_function.vadd_op,
            # "vmulhu": transformed_op_function.vmulhu_op,
            # "vand": transformed_op_function.vand_op,
            # "vmsgeu": transformed_op_function.vmsgeu_op,
            # "vwaddu": transformed_op_function.vwaddu_op,
            # "vmslt": transformed_op_function.vmslt_op,
            # "vwmulsu": transformed_op_function.vwmulsu_op,
            # "vnclipu": transformed_op_function.vnclipu_op,
            # "vsmul": transformed_op_function.vsmul_op,
            # "vasub": transformed_op_function.vasub_op,
            # "vaaddu": transformed_op_function.vaaddu_op,
            # "vsadd": transformed_op_function.vsadd_op,
            # "vnclip": transformed_op_function.vnclip_op,
            # "vssubu": transformed_op_function.vssubu_op,
            # "vaadd": transformed_op_function.vaadd_op,
            # "vssub": transformed_op_function.vssub_op,
            # "vasubu": transformed_op_function.vasubu_op,
            # "vsaddu": transformed_op_function.vsaddu_op,
            # "vssrl": transformed_op_function.vssrl_op,
            # "vssra": transformed_op_function.vssra_op,
            # "vfwsub": transformed_op_function.vfwsub_op,
            # "vfwadd": transformed_op_function.vfwadd_op,
            # "vfnmsac": transformed_op_function.vfnmsac_op,
            # "vmfgt": transformed_op_function.vmfgt_op,
            # "vfabs": transformed_op_function.vfabs_op,
            # "vfclass": transformed_op_function.vfclass_op,
            # "vfwmsac": transformed_op_function.vfwmsac_op,
            # "vmfge": transformed_op_function.vmfge_op,
            # "vfmacc": transformed_op_function.vfmacc_op,
            # "vfmsub": transformed_op_function.vfmsub_op,
            # "vmfeq": transformed_op_function.vmfeq_op,
            # "vfmul": transformed_op_function.vfmul_op,
            # "vmfle": transformed_op_function.vmfle_op,
            # "vfnmsub": transformed_op_function.vfnmsub_op,
            # "vfneg": transformed_op_function.vfneg_op,
            # "vmflt": transformed_op_function.vmflt_op,
            # "vfmerge": transformed_op_function.vfmerge_op,
            # "vfsgnjn": transformed_op_function.vfsgnjn_op,
            # "vfmin": transformed_op_function.vfmin_op,
            # "vfnmacc": transformed_op_function.vfnmacc_op,
            # "vfrsqrt7": transformed_op_function.vfrsqrt7_op,
            # "vfsgnj": transformed_op_function.vfsgnj_op,
            # "vfrsub": transformed_op_function.vfrsub_op,
            # "vfrdiv": transformed_op_function.vfrdiv_op,
            # "vfwmul": transformed_op_function.vfwmul_op,
            # "vfwnmsac": transformed_op_function.vfwnmsac_op,
            # "vfwmacc": transformed_op_function.vfwmacc_op,
            # "vfsub": transformed_op_function.vfsub_op,
            # "vfmadd": transformed_op_function.vfmadd_op,
            # "vfdiv": transformed_op_function.vfdiv_op,
            # "vfmsac": transformed_op_function.vfmsac_op,
            # "vfmax": transformed_op_function.vfmax_op,
            # "vfadd": transformed_op_function.vfadd_op,
            # "vfrec7": transformed_op_function.vfrec7_op,
            # "vmfne": transformed_op_function.vmfne_op,
            # "vfsqrt": transformed_op_function.vfsqrt_op,
            # "vfwnmacc": transformed_op_function.vfwnmacc_op,
            # "vmerge": transformed_op_function.vmerge_op,
            # "vfnmadd": transformed_op_function.vfnmadd_op,
            # "vfsgnjx": transformed_op_function.vfsgnjx_op,
            # "vredxor": transformed_op_function.vredxor_op,
            # "vredsum": transformed_op_function.vredsum_op,
            # "vwredsumu": transformed_op_function.vwredsumu_op,
            # "vredor": transformed_op_function.vredor_op,
            # "vredmaxu": transformed_op_function.vredmaxu_op,
            # "vfredmax": transformed_op_function.vfredmax_op,
            # "vfredmin": transformed_op_function.vfredmin_op,
            # "vredminu": transformed_op_function.vredminu_op,
            # "vredmax": transformed_op_function.vredmax_op,
            # "vredmin": transformed_op_function.vredmin_op,
            # "vfwredusum": transformed_op_function.vfwredusum_op,
            # "vfredosum": transformed_op_function.vfredosum_op,
            # "vfredusum": transformed_op_function.vfredusum_op,
            # "vfwredosum": transformed_op_function.vfwredosum_op,
            # "vredand": transformed_op_function.vredand_op,
            # "vwredsum": transformed_op_function.vwredsum_op,
            # "vmorn": transformed_op_function.vmorn_op,
            # "vmsof": transformed_op_function.vmsof_op,
            # "vmnor": transformed_op_function.vmnor_op,
            # "viota": transformed_op_function.viota_op,
            # "vmor": transformed_op_function.vmor_op,
            # "vmclr": transformed_op_function.vmclr_op,
            # "vmmv": transformed_op_function.vmmv_op,
            # "vmsif": transformed_op_function.vmsif_op,
            # "vmset": transformed_op_function.vmset_op,
            # "vlm": transformed_op_function.vlm_op,
            # "vcpop": transformed_op_function.vcpop_op,
            # "vfirst": transformed_op_function.vfirst_op,
            # "vmxor": transformed_op_function.vmxor_op,
            # "vmxnor": transformed_op_function.vmxnor_op,
            # "vmnand": transformed_op_function.vmnand_op,
            # "vmandn": transformed_op_function.vmandn_op,
            # "vid": transformed_op_function.vid_op,
            # "vmnot": transformed_op_function.vmnot_op,
            # "vsm": transformed_op_function.vsm_op,
            # "vmand": transformed_op_function.vmand_op,
            # "vmsbf": transformed_op_function.vmsbf_op,
            # "vrgatherei16": transformed_op_function.vrgatherei16_op,
            # "vrgather": transformed_op_function.vrgather_op,
            # "vslide1down": transformed_op_function.vslide1down_op,
            # "vcompress": transformed_op_function.vcompress_op,
            # "vslide1up": transformed_op_function.vslide1up_op,
            # "vslideup": transformed_op_function.vslideup_op,
            # "vfslide1up": transformed_op_function.vfslide1up_op,
            # "vfslide1down": transformed_op_function.vfslide1down_op,
            # "vslidedown": transformed_op_function.vslidedown_op
        }

        if op in intrinsic_function_type_05.GeneralFormatOpList or op in intrinsic_function_type_05.SignOpList or op in intrinsic_function_type_05.UnsignOpList:
            if op == "vsra" or op == "vsrl" or op == "vsll":
                if self.mask:
                    for i in range(self.Q_A_E):
                        self.golden[i] = op_list[op](self.data1[i], self.data2[i] & (self.SEW - 1), self.vd_default[i],
                                                     self.masked[i])
                else:
                    for i in range(self.Q_A_E):
                        self.golden[i] = op_list[op](self.data1[i], self.data2[i] & (self.SEW - 1), self.vd_default[i])
            else:
                if self.mask:
                    for i in range(self.Q_A_E):
                        self.golden[i] = op_list[op](self.data1[i], self.data2[i], self.vd_default[i])
                        if op == "vmulh" or op == "vmulhu" or op == "vmulhsu":
                            self.golden[i] = self.golden[i] >> (2**self.SEW)
                        else:
                            self.golden[i] = self.golden[i] & (2**self.SEW-1)
                else:
                    for i in range(self.Q_A_E):
                        self.golden[i] = op_list[op](
                            self.data1[i], self.data2[i], self.vd_default[i], self.masked[i])
                        if op == "vmulh" or op == "vmulhu" or op == "vmulhsu":
                            self.golden[i] = self.golden[i] >> (2 ** self.SEW)
                        else:
                            self.golden[i] = self.golden[i] & (2 ** self.SEW - 1)
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
        elif op == "vzext":
            if self.mask:
                for i in range(self.Q_A_E):
                    if self.masked[i] == 1:
                        self.golden[i] = self.data1[i]
                    else:
                        self.golden[i] = self.vd_default[i]
            else:
                for i in range(self.Q_A_E):
                    self.golden[i] = self.data1[i]

        elif op == "vsext":
            if self.mask:
                for i in range(self.Q_A_E):
                    if self.masked[i] == 1:
                        if self.data1[i] < 0:
                            self.golden[i] = self.data1[i] + pow(2, self.SEW) - 1
                        else:
                            self.golden[i] = self.data1[i]
                    else:
                        self.golden[i] = self.vd_default[i]
            else:
                for i in range(self.Q_A_E):
                    if self.data1[i] < 0:
                        self.golden[i] = self.data1[i] + pow(2, self.SEW) - 1
                    else:
                        self.golden[i] = self.data1[i]

normal_suffix = ['16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4', '32m1', '32m2', '32m4', '32m8', '32mf2', '64m1', '64m2', '64m4', '64m8', '8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8']
vx_list = ['vv', 'vx']
mask_list = ['', '_m']
iu_list = ['i', 'u']
for temp in intrinsic_function_type_05.GeneralFormatOpList:
    if op != temp:
        continue
    else:
        for suffix, vx, mask, iu in cross(normal_suffix, vx_list, mask_list, iu_list):
            OP = op
            divider = suffix.split('m')
            SEW = int(divider[0])
            LMUL = utils.get_float_lmul(divider[1])
            a = extra_inst_info(iu, SEW, LMUL, OP)
            filename = "testcase/%s_%s_%s%s%s.c" % (op, vx, iu, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            if mask != '_m':
                with open(filename, 'a') as fd:
                    a.mask = 1
                    # don't hava mask
                    C_lines_write.compiler_option_write(fd)
                    C_lines_write.c_header_file_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_declaration_write(fd, a, q_array)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.pointer_iterator_write(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_wo_mask(fd, a, op)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    C_lines_write.compiler_option_write(fd)
                    C_lines_write.c_header_file_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_default_write(fd, a)
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    C_lines_write.mask_data_write(fd, a)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    # a.C_lines_write.specific_operator_c()
                    C_lines_write.pointer_iterator_write(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_mask(fd, a, op)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
for temp in intrinsic_function_type_05.SpMaskOpList:
    # SpMaskOpList = ['vadc', 'vmerge']
    # loop _vx, _iu, _suffix, have to with middle mask
    if op != temp:
        continue
    else:
        for suffix, vx, iu in cross(normal_suffix, vx_list, iu_list):
            a = extra_inst_info(iu)
            a.OP = op
            divider = suffix.split('m')
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.lmul = utils.get_float_lmul(divider[1])
            a.op_mask = op
            filename = "testcase/%s_v%sm_%s%s.c" % (op, vx, iu, suffix)
            with open(filename, 'w') as fd:
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                a.mask_gen()
                C_lines_write.mask_data_write(fd, a)
                C_lines_write.vs2_load(fd, a, suffix, mask)
                C_lines_write.v1_load(fd, a, suffix, mask)
                C_lines_write.vd_load(fd, a, suffix, mask)
                # a.C_lines_write.specific_operator_c()
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.jump_to_next_write_mask()
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
for temp in intrinsic_function_type_05.Sp2MaskOpList:
    # Sp2MaskOpList = ['vmadc', 'vmsbc']
    # loop _vx, _iu, _suffix, and middle mask. don't have _mask
    if op != temp:
        continue
    else:
        for vx, iu, suffix, mask in cross(vx_list, iu_list, normal_suffix, middle_mask_list):
            a = extra_inst_info(iu)
            a.OP = op
            divider = suffix.split('m')
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.lmul = utils.get_float_lmul(divider[1])
            filename = "testcase/%s_v%s%s_%s%s.c" % (op, vx, mask, iu, suffix)
            with open(filename, 'w') as fd:
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                C_lines_write.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                # a.a.mask_gen()
                # a.C_lines_write.mask_data_write()
                # todo: a special mask write function if masked, write 1s, else 0s.
                C_lines_write.vs2_load(fd, a, suffix, mask)
                C_lines_write.v1_load(fd, a, suffix, mask)
                C_lines_write.vd_load(fd)
                # a.C_lines_write.specific_operator_c()
                C_lines_write.pointer_iterator_write(fd)
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.jump_to_next_write_mask()
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
for temp in intrinsic_function_type_05.SignOpList:
    # SignOpList = ['vdiv', 'vmax', 'vmin', 'vmsge', 'vmsgt', 'vmsle', 'vmslt', 'vmulh', 'vmulhsu', 'vrem',
    #              'vsra', 'vwmacc',
    #              'vwmaccsu', 'vwmul', 'vwmulsu']
    # loop _vx, _suffix, _mask, with fixed i
    if op != temp:
        continue
    else:
        for suffix, vx, mask in cross(normal_suffix, vx_list, mask_list):
            divider = suffix.split('m')
            a = extra_inst_info('i', int(divider[0]), utils.get_float_lmul(divider[1]), op)
            a.OP = op
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.LMUL = utils.get_float_lmul(divider[1])
            filename = "testcase/%s_v%s_i%s%s.c" % (op, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            iu = 'i'
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    if temp in intrinsic_function_type_06.RMOpList:
                        # must be fix point file sn, if not, plz edit.
                        C_lines_write.csr_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    if op == "vmulhsu" or op == "vwmaccsu":
                        C_lines_write.unsign_vs1_data_write(fd, a)
                    else:
                        C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_declaration_write(fd, a, q_array)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    if op == "vmulhsu" or "vwmaccsu":
                        C_lines_write.unsign_vs1_load()
                    else:
                        C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.pointer_iterator_write(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_wo_mask(fd, a, op)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    if temp in intrinsic_function_type_06.RMOpList:
                        # must be fix point file sn, if not, plz edit.
                        C_lines_write.csr_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    if op == "vmulhsu" or "vwmaccsu":
                        C_lines_write.unsign_vs1_data_write(fd, a)
                    else:
                        C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_default_write(fd, a)
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    C_lines_write.mask_data_write(fd, a)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    if op == "vmulhsu" or "vwmaccsu":
                        C_lines_write.unsign_vs1_load(fd, a, suffix, mask)
                    else:
                        C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd)
                    # a.C_lines_write.specific_operator_c()
                    C_lines_write.pointer_iterator_write(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_mask(fd, a, op)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
for temp in intrinsic_function_type_05.UnsignOpList:
    # UnsignOpList = ['vdivu', 'vmaxu', 'vminu', 'vmsgeu', 'vmsgtu', 'vmsleu', 'vmsltu', 'vmulhu', 'vremu', 'vsrl',
    # 'vwmaccu', 'vwmaccu', 'vwmulu']
    # loop _vx, _suffix, _mask with fixed u
    if op != temp:
        continue
    else:
        for suffix, vx, mask in cross(normal_suffix, vx_list, mask_list):
            a = extra_inst_info('u')
            a.OP = op
            divider = suffix.split('m')
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.lmul = utils.get_float_lmul(divider[1])
            filename = "testcase/%s_v%s_u%s%s.c" % (op, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            iu = 'u'
            if mask != '_m':
                with open(filename, 'w') as fd:
                    C_lines_write.mask = 1
                    # don't hava mask
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    if temp in intrinsic_function_type_06.RMOpList:
                        # must be fix point file sn, if not, plz edit.
                        C_lines_write.csr_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_declaration_write(fd, a, q_array)
                    C_lines_write.vs1_data_write(fd, a, suffix, mask)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_mask(fd, a)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    if temp in intrinsic_function_type_06.RMOpList:
                        # must be fix point file sn, if not, plz edit.
                        C_lines_write.csr_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_default_write(fd, a)
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    C_lines_write.mask_data_write(fd, a)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs1_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.pointer_iterator_write(fd)
                    # C_lines_write.specific_operator_c()
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_mask()
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
if op == 'vwmaccus':
    # WSignOpList = ['vnsra', 'vwmaccus']
    # loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
    for suffix, mask in cross(widen_suffix, mask_list):
        # todo: sign scalar * unsign vector
        iu = 'i'
        a = extra_inst_info(iu)
        a.OP = op
        divider = suffix.split('m')
        a.SEW = int(divider[0])
        a.range = pow(2, a.SEW)
        a.lmul = utils.get_float_lmul(divider[1])
        filename = "testcase/%s_vx_i%s%s.c" % (op, suffix, mask)
        a.op_mask = "%s%s" % (op, mask)
        a.sign = 'i'
        if mask != '_m':
            with open(filename, 'w') as fd:
                a.mask = 1
                # don't hava mask
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                C_lines_write.vd_declaration_write(fd, a, q_array)
                C_lines_write.vs2_load(fd, a, suffix, mask)
                # C_lines_write.vs2_load(fd, a, suffix, mask)
                # scalar don't need load
                C_lines_write.vd_load(fd, a, suffix, mask)
                C_lines_write.pointer_iterator_write(fd)
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.jump_to_next_write_wo_mask(fd, a, op)
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
        else:
            with open(filename, 'w') as fd:
                a.mask = 0
                # mask and have v0.mask[i] value
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                C_lines_write.vd_default_write(fd, a)
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                C_lines_write.mask_data_write(fd ,a)
                C_lines_write.vs1_data_write(fd, a, suffix, mask)
                # C_lines_write.vs2_load(fd, a, suffix, mask)
                # scalar don't need load
                C_lines_write.vd_load(fd, a, suffix, mask)
                C_lines_write.pointer_iterator_write(fd)
                # C_lines_write.specific_operator_c()
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.jump_to_next_write_mask(fd, a, op)
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
if op == 'vnsra' or op == 'vnsrl':
    # WSignOpList = ['vnsra', 'vwmaccus']
    # loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
    for suffix, mask, vx in cross(narrow_suffix, mask_list, vx_list):
        if op == 'vnsra':
            iu = 'i'
            filename = "testcase/%s_w%s_i%s%s.c" % (op, vx, suffix, mask)
        else:
            iu = 'u'
            filename = "testcase/%s_w%s_u%s%s.c" % (op, vx, suffix, mask)
        a = extra_inst_info(iu)
        a.OP = op
        divider = suffix.split('m')
        a.SEW = int(divider[0])
        a.range = pow(2, a.SEW)
        a.lmul = utils.get_float_lmul(divider[1])
        a.op_mask = "%s%s" % (op, mask)
        if mask != '_m':
            with open(filename, 'w') as fd:
                C_lines_write.mask = 1
                # don't hava mask
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                C_lines_write.vd_declaration_write(fd, a, q_array)
                C_lines_write.vs2_load(fd, a, suffix, mask)
                C_lines_write.vs1_load(fd, a, suffix, mask)
                C_lines_write.vd_load(fd, a, suffix, mask)
                C_lines_write.vd_load(fd)
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.vd_store(fd, a, op)
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
        else:
            with open(filename, 'w') as fd:
                C_lines_write.mask = 0
                # mask and have v0.mask[i] value
                C_lines_write.compiler_option_write(fd, a)
                C_lines_write.c_header_file_write(fd)
                C_lines_write.c_main_entry_write(fd)
                a.random_gen()
                C_lines_write.vs2_data_write(fd, a)
                C_lines_write.vs1_data_write(fd, a)
                C_lines_write.vl_set_write(fd, suffix)
                C_lines_write.vd_default_write()
                # set vd default value if v0.mask[i] = 0, golden = default
                a.mask_gen()
                C_lines_write.mask_data_write()
                C_lines_write.vs2_load(fd, a, suffix, mask)
                C_lines_write.vs1_load(fd, a, suffix, mask)
                C_lines_write.vd_load(fd, a, suffix, mask)
                C_lines_write.pointer_iterator_write(fd)
                # C_lines_write.specific_operator_c()
                C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                C_lines_write.vd_store(fd, a, suffix, iu, mask)
                C_lines_write.jump_to_next_write_mask(fd, op)
                a.compute()
                C_lines_write.golden_by_python_write(fd, a)
                C_lines_write.report_write(fd, q_array)
for temp in intrinsic_function_type_05.SpWUnsignOpList:
    if op != temp:
        continue
    # SpWUnsignOpList = ['vwaddu', 'vwsubu']
    # loop _wv, _vx , _suffix, _mask, with fixed u
    else:
        for wv, vx, suffix, mask in cross(wv_list, vx_list, widen_suffix, mask_list):
            iu = 'u'
            a = extra_inst_info(iu)
            a.OP = op
            divider = suffix.split('m')
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.lmul = utils.get_float_lmul(divider[1])
            filename = "testcase/%s_%s%s_u%s%s.c" % (op, wv, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_declaration_write(fd, a, q_array)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.pointer_iterator_write(fd)
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.vd_store(fd, a, op)
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
            else:
                with open(filename, 'w') as fd:
                    a.mask = 0
                    # mask and have v0.mask[i] value
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
                    C_lines_write.c_main_entry_write(fd)
                    a.random_gen()
                    C_lines_write.vs2_data_write(fd, a)
                    C_lines_write.vs1_data_write(fd, a)
                    C_lines_write.vl_set_write(fd, suffix)
                    C_lines_write.vd_default_write()
                    # set vd default value if v0.mask[i] = 0, golden = default
                    a.mask_gen()
                    C_lines_write.mask_data_write()
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vs2_load(fd, a, suffix, mask)
                    C_lines_write.vd_load(fd, a, suffix, mask)
                    C_lines_write.pointer_iterator_write(fd)
                    # C_lines_write.specific_operator_c()
                    C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                    C_lines_write.vd_store(fd, a, suffix, iu, mask)
                    C_lines_write.jump_to_next_write_mask()
                    a.compute()
                    C_lines_write.golden_by_python_write(fd, a)
                    C_lines_write.report_write(fd, q_array)
if op == 'vmv':
    # loop _iu, _suffix and _vx with "_"
    for iu, suffix, vx in cross(iu_list, normal_suffix, vx_list):
        a = extra_inst_info(iu)
        a.op_mask = op
        divider = suffix.split('m')
        a.SEW = int(divider[0])
        a.range = pow(2, a.SEW)
        a.lmul = utils.get_float_lmul(divider[1])
        filename = "testcase/%s_v_%s_%s%s.c" % (op, vx, iu, suffix)
        with open(filename, 'w') as fd:
            a.mask = 1
            # don't hava mask
            C_lines_write.compiler_option_write(fd, a)
            C_lines_write.c_header_file_write(fd)
            C_lines_write.c_main_entry_write(fd)
            a.random_gen()
            C_lines_write.vs2_data_write(fd, a)
            C_lines_write.vl_set_write(fd, suffix)
            C_lines_write.vd_declaration_write(fd, a, q_array)
            C_lines_write.vs2_load(fd, a, suffix, mask)
            C_lines_write.vd_load(fd, a, suffix, mask)
            C_lines_write.pointer_iterator_write(fd)
            C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
            C_lines_write.vd_store(fd, a, suffix, iu, mask)
            C_lines_write.vd_store(fd, a, op)
            a.compute()
            C_lines_write.golden_by_python_write(fd, a)
            C_lines_write.report_write(fd, q_array)
        if op == 'vneg' or op == 'vnot':
            # SpVOplist = ['vneg']
            # loop _suffix, _mask and only v, with fixed i
            # Sp2VOplist = ['vnot']
            # loop _suffix, _iu, _mask and only v
            for suffix, mask, iu in cross(normal_suffix, mask_list, iu_list):
                a = extra_inst_info(iu)
                OP = op
                divider = suffix.split('m')
                SEW = int(divider[0])
                range = pow(2, SEW)
                lmul = utils.get_float_lmul(divider[1])
                if op == 'vneg':
                    if iu == 'i':
                        filename = "testcase/%s_v_i%s%s.c" % (op, suffix, mask)
                else:
                    filename = "testcase/%s_v_%s%s%s.c" % (op, iu, suffix, mask)
                op_mask = "%s%s" % (op, mask)
                if mask != '_m':
                    with open(filename, 'w') as fd:
                        a.mask = 1
                        # don't hava mask
                        C_lines_write.compiler_option_write(fd, a)
                        C_lines_write.c_header_file_write(fd)
                        C_lines_write.c_main_entry_write(fd)
                        a.random_gen()
                        C_lines_write.vs2_data_write(fd, a)
                        C_lines_write.vl_set_write(fd, suffix)
                        C_lines_write.vd_declaration_write(fd, a, q_array)
                        C_lines_write.vs2_load(fd, a, suffix, mask)
                        C_lines_write.vd_load(fd, a, suffix, mask)
                        C_lines_write.pointer_iterator_write(fd)
                        C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                        C_lines_write.vd_store(fd, a, suffix, iu, mask)
                        C_lines_write.vd_store(fd, a, op)
                        a.compute()
                        C_lines_write.golden_by_python_write(fd, a)
                        C_lines_write.report_write(fd, q_array)
                else:
                    with open(filename, 'w') as fd:
                        a.mask = 0
                        # mask and have v0.mask[i] value
                        C_lines_write.compiler_option_write(fd, a)
                        C_lines_write.c_header_file_write(fd)
                        C_lines_write.c_main_entry_write(fd)
                        a.random_gen()
                        C_lines_write.vs2_data_write(fd, a)
                        C_lines_write.vl_set_write(fd, suffix)
                        C_lines_write.vd_default_write()
                        # set vd default value if v0.mask[i] = 0, golden = default
                        a.mask_gen()
                        a.mask_data_write()
                        C_lines_write.vs2_load(fd, a, suffix, mask)
                        C_lines_write.vd_load(fd, a, suffix, mask)
                        C_lines_write.pointer_iterator_write(fd)
                        # C_lines_write.specific_operator_c()
                        C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                        C_lines_write.vd_store(fd, a, suffix, iu, mask)
                        C_lines_write.jump_to_next_write_mask()
                        a.compute()
                        C_lines_write.golden_by_python_write(fd, a)
                        C_lines_write.report_write(fd, q_array)
        # ExtOpList = ['vsext', 'vzext']
        # loop _ext, _suffix, _mask with fixed i(vsext) or u(vzext)
        if op == 'vsext' or op == 'vzext':
            for suffix, ext, mask in cross(normal_suffix, ext_list, mask_list):
                if op == 'vsext':
                    iu = 'i'
                else:
                    iu = 'u'
                a = extra_inst_info(iu)
                OP = op
                divider = suffix.split('m')
                SEW = int(divider[0])
                C_lines_write.ext_sew = int(SEW / utils.get_float_lmul(ext))
                lmul = utils.get_float_lmul(divider[1])
                C_lines_write.ext_lmul = lmul / utils.get_float_lmul(ext)
                op_mask = "%s%s" % (op, mask)
                if SEW / utils.get_float_lmul(ext) <= 64 and SEW / lmul <= 64 and lmul / utils.get_float_lmul(ext) <= 8:
                    ext_suffix = "%sm%s" % (int(C_lines_write.ext_sew), utils.get_string_lmul(C_lines_write.ext_lmul))
                    bool_width = int(C_lines_write.ext_sew) / C_lines_write.ext_lmul
                    if op == 'vsext':
                        a.sign = 'i'
                        filename = "testcase/%s_v%s_i%s%s.c" % (op, ext, ext_suffix, mask)
                    else:
                        a.sign = 'u'
                        filename = "testcase/%s_v%s_u%s%s.c" % (op, ext, ext_suffix, mask)
                    if mask != '_m':
                        with open(filename, 'w') as fd:
                            a.mask = 1
                            # don't hava mask
                            C_lines_write.compiler_option_write(fd, a)
                            C_lines_write.c_header_file_write(fd)
                            C_lines_write.c_main_entry_write(fd)
                            a.random_gen()
                            C_lines_write.vs2_data_write(fd, a)
                            C_lines_write.vl_set_write(fd, suffix)
                            C_lines_write.ext_vd_declaration_write()
                            C_lines_write.vs2_load(fd, a, suffix, mask)
                            C_lines_write.ext_vd_load()
                            C_lines_write.pointer_iterator_write(fd)
                            C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                            C_lines_write.ext_vd_store()
                            C_lines_write.vd_store(fd, a, op)
                            a.compute()
                            C_lines_write.golden_by_python_write(fd, a)
                            C_lines_write.report_write(fd, q_array)
                    else:
                        with open(filename, 'w') as fd:
                            a.mask = 0
                            # mask and have v0.mask[i] value
                            C_lines_write.compiler_option_write(fd, a)
                            C_lines_write.c_header_file_write(fd)
                            C_lines_write.c_main_entry_write(fd)
                            a.random_gen()
                            C_lines_write.vs2_data_write(fd, a)
                            C_lines_write.vl_set_write(fd, suffix)
                            C_lines_write.ext_vd_declaration_write()
                            # set vd default value if v0.mask[i] = 0, golden = default
                            a.mask_gen()
                            a.mask_data_write()
                            C_lines_write.vs2_load(fd, a, suffix, mask)
                            C_lines_write.ext_vd_load()
                            C_lines_write.pointer_iterator_write(fd)
                            # C_lines_write.specific_operator_c()
                            C_lines_write.parameter_seq_write(fd, a, vx, suffix, iu)
                            C_lines_write.ext_vd_store()
                            C_lines_write.jump_to_next_write_mask()
                            a.compute()
                            C_lines_write.golden_by_python_write(fd, a)
                            C_lines_write.report_write(fd, q_array)
                else:
                    continue