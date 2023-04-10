#!/usr/bin/env python3
import os

import exe_op_generator

filelist = set()
for files in os.walk("./rvv-intrinsic-doc/auto-generated/intrinsic_funcs/", topdown=False):
    for name in files:
        filelist.add(os.path.join(name))


class Index:
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
    def thrower(self):
        if self.suffix_type == 'normal':
            if self.sign_type == 'iu':
                if self.mask == 'normal':
                    if self.operand_type == 'vx':
                        exe_op_generator.GeneralFormatOpList.append(op)



function_set = set()

for file in filelist:
    with open(file) as f:
        operand_type_lists = set()
        sign = set()
        suffix = set()
        for line in f:
            if '__riscv_' not in line:
                continue
            return_type_parser = line.split('__riscv_')
            op_parser = return_type_parser[1].split('_')
            operand_type_parser = op_parser[1].split('_')
            function_set.add(op_parser[0])
            operand_type_lists.add(operand_type_parser[0])
            sign.add(operand_type_parser[1][0])
            suffix.add(operand_type_parser[1].split(operand_type_parser[1][0]))
