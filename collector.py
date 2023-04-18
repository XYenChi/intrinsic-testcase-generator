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
special_set = set()
operand_type_lists = set()
sign = set()
suffix = set()
for file in filelist:
    temp = str(file)
    sn = temp.split('_')
    if sn[0] != '00' and sn[0] != '01' and sn[0] != '08' and sn[0] != '09' and sn[0] != '10' and sn[0] != '11':
        with open(os.path.join(location, file)) as f:
            for line in f:
                if '__riscv_' not in line:
                    continue
                return_type_parser = line.split('__riscv_')
                op_parser = return_type_parser[1].split('_')
                operand_type_parser = op_parser[2].split(' ')
                a = operand_type_parser[0][0]
                b = operand_type_parser[0]
                divided_suffix = b.split(a, 1)
                if divided_suffix[1] == '':
                    special_set.add(op_parser[0])
                elif op_parser[1] == 'rtz':
                    special_set.add(op_parser[0])
                elif divided_suffix[1] == 'u':
                    special_set.add(op_parser[0])
                else:
                    operand_type_lists.add(op_parser[1])
                    sign.add(op_parser[2][0])
                    function_set.add(op_parser[0])
                    suffix.add(divided_suffix[1])
print(function_set)
print(operand_type_lists)
print(sign)
print(suffix)
print(special_set)
