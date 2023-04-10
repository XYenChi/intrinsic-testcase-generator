#!/usr/bin/env python3
import os

filelist = set()
location = './rvv-intrinsic-doc/auto-generated/intrinsic_funcs/'


def list_all_file(base):
    for files in os.walk(base, topdown=False):
        for name in files:
            yield name


for i in list_all_file(location):
    filelist = i

function_set = set()

for file in filelist:
    with open(os.path.join(location, file)) as f:
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
            print(operand_type_parser[0])
            sign.add(operand_type_parser[1][0])
            suffix.add(operand_type_parser[1].split(operand_type_parser[1][0]))
print(function_set)
print(sign)
print(suffix)
