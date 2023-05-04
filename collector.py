#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import os

import exe_op_generator
import filter
import sys

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
instance_operand_type_lists = set()
instance_sign = set()
instance_suffix = set()
op_instance_list = list()
for file in filelist:
    temp = str(file)
    sn = temp.split('_')
    file_to_test = sys.argv[1]
    if sn[0] == file_to_test:
        with open(os.path.join(location, file)) as f:
            counter = 0
            for line in f:
                counter += 1
                if '__riscv_' not in line:
                    continue
                return_type_parser = line.split('__riscv_')
                op_parser = return_type_parser[1].split('_')
                operand_type_parser = op_parser[2].split(' ')
                a = operand_type_parser[0][0]
                b = operand_type_parser[0]
                divided_suffix = b.split(a, 1)
                # todo: "_m"
                if divided_suffix[1] == '':
                    special_set.add(op_parser[0])
                elif op_parser[1] == 'rtz':
                    special_set.add(op_parser[0])
                elif divided_suffix[1] == 'u':
                    special_set.add(op_parser[0])
                else:
                    operand_type_lists_counter1 = len(operand_type_lists)
                    operand_type_lists.add(op_parser[1])
                    operand_type_lists_counter2 = len(operand_type_lists)
                    sign_counter1 = len(sign)
                    sign.add(op_parser[2][0])
                    sign_counter2 = len(sign)
                    function_counter1 = len(function_set)
                    function_set.add(op_parser[0])
                    function_counter2 = len(function_set)
                    suffix_counter1 = len(suffix)
                    suffix.add(divided_suffix[1])
                    suffix_counter2 = len(suffix)
                    if function_counter1 != function_counter2:
                        instance_sign = set()
                        instance_operand_type_lists = set()
                        instance_suffix = set()
                        instance_name = set()
                    elif (operand_type_lists_counter1 == operand_type_lists_counter2) & (sign_counter1 == sign_counter2
                    ) & (function_counter1 == function_counter2) & (suffix_counter1 == suffix_counter2):
                        instance_sign.add(op_parser[2][0])
                        instance_operand_type_lists.add(op_parser[1])
                        instance_suffix.add(divided_suffix[1])
                    else:
                        continue
                    if (function_counter1 != function_counter2) & (counter == 1):
                        continue
                    elif function_counter1 != function_counter2:
                        x = filter.Index()
                        x.op_name = op_parser[0]
                        x.sign_type = instance_sign
                        x.operand_type = instance_operand_type_lists
                        x.suffix_list = instance_suffix
                        op_instance_list.append(x)
generate_file = open("collector_product.txt", "w")
generate_file.write("function_set:\n" + str(function_set) + "\n")
generate_file.write("operand_type_lists:\n" + str(operand_type_lists) + "\n")
generate_file.write("sign:\n" + str(sign) + "\n")
generate_file.write("suffix:\n" + str(suffix) + "\n")
generate_file.write("special_set:\n" + str(special_set) + "\n")
for i in op_instance_list:
    generate_file.write(f"function name:\n{i.op_name}\noperand type:\n{sorted(i.operand_type)}\nsign type:\n"
                        f"{sorted(i.sign_type)}\nsuffix list:\n{sorted(i.suffix_list)}\n")
    if i.operand_type == filter.type_vx:
        if i.sign_type == filter.sign_iu:
            if i.suffix_list == exe_op_generator.suffix:
                exe_op_generator.GeneralFormatOpList.append(i.op_name)
            elif i.suffix_list == exe_op_generator.widen_suffix:
                exe_op_generator.SpWsignOpList.append(i.op_name)
            else:
                special_set.add(i.op_name)
                print("find a sign_iu suffix issue")
        elif i.sign_type == filter.sign_fix_i:
            if i.suffix_list == exe_op_generator.suffix:
                exe_op_generator.SignOpList.append(i.op_name)
            elif i.suffix_list == exe_op_generator.widen_suffix:
                exe_op_generator.SpWsignOpList.append(i.op_name)
            else:
                special_set.add(i.op_name)
                print("find a sign_fix_i suffix issue")
        elif i.sign_type == filter.sign_fix_u:
            if i.suffix_list == exe_op_generator.suffix:
                exe_op_generator.UnsignOpList.append(i.op_name)
            elif i.suffix_list == exe_op_generator.widen_suffix:
                exe_op_generator.SpWUnsignOpList.append(i.op_name)
            else:
                special_set.add(i.op_name)
                print("find a sign_fix_u suffix issue")
generate_file.write("GeneralFormatOpList:\n" + str(exe_op_generator.GeneralFormatOpList) + "\n")
generate_file.write("SignOpList:\n" + str(exe_op_generator.SignOpList) + "\n")
generate_file.write("UnsignOpList:\n" + str(exe_op_generator.UnsignOpList) + "\n")
