"""
Generate execute file by operator
"""
import filter
import operator_py_function
import random
import sys
import intrinsic_function_type_05
sys.path.append("./rvv-intrinsic-doc/rvv-intrinsic-generator/rvv_intrinsic_gen")
import math
import utils
import generator
import enums
import constants
import C_lines_write

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
        self.extra = None
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
            "vadd": operator_py_function.add_op,
            "vwadd": operator_py_function.add_op,
            "vwaddu": operator_py_function.add_op,
            "vand": operator_py_function.and_op,
            "vsub": operator_py_function.sub_op,
            "vwsub": operator_py_function.sub_op,
            "vwsubu": operator_py_function.sub_op,
            "vmul": operator_py_function.mul_op,
            "vwmul":operator_py_function.mul_op,
            "vmulh": operator_py_function.mul_op,
            "vmulhu": operator_py_function.mul_op,
            "vmulsu": operator_py_function.mul_op,
            "vmulhsu": operator_py_function.mul_op,
            "vwmulsu": operator_py_function.mul_op,
            "vwmulu": operator_py_function.mul_op,
            "vdiv": operator_py_function.div_op,
            "vdivu": operator_py_function.div_op,
            "vmax": operator_py_function.max_op,
            "vmaxu": operator_py_function.max_op,
            "vmin": operator_py_function.min_op,
            "vminu": operator_py_function.min_op,
            "vrem": operator_py_function.reminder,
            "vremu": operator_py_function.reminder,
            "vadc": operator_py_function.add_with_carry_op,
            "vsbc": operator_py_function.sub_with_borrow_op,
            "vmerge": operator_py_function.merge_op,
            "vmacc": operator_py_function.multiply_add_overwrite_addend_op,
            "vwmacc": operator_py_function.multiply_add_overwrite_addend_op,
            "vwmaccu": operator_py_function.multiply_add_overwrite_addend_op,
            "vwmaccus": operator_py_function.multiply_add_overwrite_addend_op,
            "vwmaccsu": operator_py_function.multiply_add_overwrite_addend_op,
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
            "vxor": operator_py_function.xor_op,
            "vsra": operator_py_function.shift_right_op,
            "vnsra": operator_py_function.shift_right_op,
            "vsrl": operator_py_function.shift_right_op,
            "vnsrl": operator_py_function.shift_right_op,
            "vsll": operator_py_function.shift_left_op,
            "vnsll": operator_py_function.shift_left_op,
            "vmsge": operator_py_function.greater_equal_op,
            "vmsle": operator_py_function.less_equal_op,
            "vmsleu": operator_py_function.less_equal_op,
            "vmslt": operator_py_function.less_than_op,
            "vmsltu": operator_py_function.less_than_op,
            "vmsgt": operator_py_function.greater_than_op,
            "vmsne": operator_py_function.not_equal_to_op,
            "vrsub": operator_py_function.reverse_sub_op,
            "vmsgeu": operator_py_function.greater_equal_op,
            "vmsgtu": operator_py_function.greater_than_op
            # don't need
            # "vsext": operator_py_function.sign_extesion_op,
            # "vzext": operator_py_function.zero_extesion_op,
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
            filename = "testcase/%s_v%s_%s%s%s.c" % (op, vx, iu, suffix, mask)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
            a = extra_inst_info('i')
            a.OP = op
            divider = suffix.split('m')
            a.SEW = int(divider[0])
            a.range = pow(2, a.SEW)
            a.lmul = utils.get_float_lmul(divider[1])
            filename = "testcase/%s_v%s_i%s%s.c" % (op, vx, suffix, mask)
            a.op_mask = "%s%s" % (op, mask)
            iu = 'i'
            if mask != '_m':
                with open(filename, 'w') as fd:
                    a.mask = 1
                    # don't hava mask
                    C_lines_write.compiler_option_write(fd, a)
                    C_lines_write.c_header_file_write(fd)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
                C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
                    C_lines_write.parameter_seq_write(fd, a)
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
            C_lines_write.parameter_seq_write(fd, a)
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
                        C_lines_write.parameter_seq_write(fd, a)
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
                        C_lines_write.parameter_seq_write(fd, a)
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
                            C_lines_write.parameter_seq_write(fd, a)
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
                            C_lines_write.parameter_seq_write(fd, a)
                            C_lines_write.ext_vd_store()
                            C_lines_write.jump_to_next_write_mask()
                            a.compute()
                            C_lines_write.golden_by_python_write(fd, a)
                            C_lines_write.report_write(fd, q_array)
                else:
                    continue