#!/usr/bin/env python3
class index:
    def __init__(self):
        self.operand_num = None
        # 1 for only vs2,
        self.operand_type = None
        # v, x, w
        self.mask_type = None
        # '', '_m', middle 'm'
        self.sign_type = None
        # fixed i or u or both i and u
        self.suffix_type = None
        # normal, narrow or widen

with open('./rvv-intrinsic-doc/auto-generated/intrinsic_funcs/04_vector_integer_arithmetic_functions.md') as f:
    integer_op_lists = set()
    operand_type_lists = set()
    sign = set()
    suffix = set()
    for line in f:
        if '__riscv_' not in line:
            continue
        return_type_parser = line.split('__riscv_')
        op_parser = return_type_parser[1].split('_')
        operand_type_pasrser = op_parser[1].split('_')
        integer_op_lists.add(op_parser[0])
        operand_type_lists.add(operand_type_pasrser[0])
        sign.add(operand_type_pasrser[1][0])
        suffix.add(operand_type_pasrser[1].split(operand_type_pasrser[1][0]))
        print(integer_op_lists)

