#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import os
import filter
import sys
import random

filelist = set()
location = './rvv-intrinsic-doc/auto-generated/intrinsic_funcs/'


def list_all_file(base):
    for files in os.walk(base, topdown=False):
        for file_name in files:
            yield file_name


for i in list_all_file(location):
    filelist = i

c_dir_file_name = 'c_dir_file_name'
function_set = set()
special_set = set()
operand_type_set = set()
sign = set()
suffix = set()
C_example = []
# to save operator instance
op_instance_list = list()
# to list all kinds of operand_type, sign_type and suffix_type for sorting and iterating.
# save all the different type for iterator
operand_type_4_iterator = list()
sign_type_4_iterator = list()
suffix_type_4_iterator = list()


def name_parser(line_string):
    # parse a line to produce a tuple contain intrinsic function
    return_type_parser = line_string.split('__riscv_')
    op_parser = return_type_parser[1].split('_')
    if op_parser[3] == 'rm':
        mask_parser = op_parser[4].split(' ')
        rounding_mode = op_parser[3]
    else:
        mask_parser = op_parser[3].split(' ')
        rounding_mode = ''
    operand_type_parser = op_parser[2].split(' ')
    a = operand_type_parser[0][0]
    b = operand_type_parser[0]
    divided_suffix = b.split(a, 1)
    function_factor = op_parser[0], op_parser[1], op_parser[2][0], divided_suffix[1], mask_parser[0], rounding_mode
    return function_factor


def reduction_function_parser(line_string):
    # todo: edit judge function
    return_type_parser = line_string.split('__riscv_')
    op_parser = return_type_parser[1].split('_')
    first_suffix = []
    second_suffix = []
    mask_second_suffix = op_parser[4].split(' ')
    if mask_second_suffix[0] == 't':
        second_suffix = (op_parser[3].split(' '))[0]
        first_suffix = op_parser[2]
    elif mask_second_suffix[0] == 'm':
        second_suffix = op_parser[3]
        first_suffix = op_parser[2]
    else:
        print("find a special format")
    operand_type_parser = op_parser[2].split(' ')
    a = operand_type_parser[0][0]
    b = operand_type_parser[0]
    divided_suffix = b.split(a, 1)
    function_factor = op_parser[0], op_parser[1], op_parser[2][0], divided_suffix[1], mask_second_suffix[0], \
        first_suffix, second_suffix
    return function_factor


def c_function_parser(line_string):
    # to remove operand type and add "out = "
    # can deal with fix point file.
    c_string = "out = "
    function = []
    param_list = []
    function_param = line_string.split('(')
    # function_param[0] : function name
    # function_param[1] : param
    param = function_param[1].split(', ')
    function.append(function_param[0].split(' ')[1])
    for p_sn in range(0, len(param)):
        type_param = param[p_sn].split(' ')
        # print(type_param[1])
        remove = type_param[1].split(';')
        param_list.append(remove[0])
        # type_param[0] : type
        # type_param[1] : param
    # function[0]: function name, operand type, sign, sew+lmul and mask, like "__riscv_vwadd_wv_i32m1_m"
    function.insert(1, '(')
    for param in param_list:
        function.append(param)
    list_sn = 3
    while True:
        max_sn = len(function)
        if list_sn < max_sn:
            function.insert(list_sn, ', ')
            list_sn += 2
        else:
            break
    function.insert(len(function), ';')
    for element in function:
        c_string = c_string + "%s" % element
    return c_string


def c_directory_auto_gen(function, file_name):
    with open(file_name, "a") as fd:
        fd.write("\"%s\": transformed_op_function.%s_op,\n" % (function, function))


def judge(op_name):
    if op_name.operand_type == filter.type_vx:
        if op_name.sign_type == filter.sign_iu:
            if op_name.suffix_list == filter.normal_suffix:
                filter.GeneralFormatOpList.append(op_name.op_name)
            elif op_name.suffix_list == filter.widen_suffix:
                filter.SpWsignOpList.append(op_name.op_name)
            else:
                special_set.add(op_name.op_name)
                print("find a sign_iu suffix issue")
        elif op_name.sign_type == filter.sign_fix_i:
            if op_name.vxrm != 5:
                filter.RMOpList.append(op_name.op_name)
            if op_name.operand_type == filter.only_v:
                filter.SpVOplist.append(op_name.op_name)
            elif op_name.operand_type == filter.type_vx:
                if op_name.suffix_list == filter.normal_suffix:
                    filter.SignOpList.append(op_name.op_name)
                elif op_name.suffix_list == filter.widen_suffix:
                    filter.SpWsignOpList.append(op_name.op_name)
            else:
                special_set.add(op_name.op_name)
                print("find a sign_fix_i suffix issue")
        elif op_name.sign_type == filter.sign_fix_u:
            if op_name.vxrm != 5:
                filter.RMOpList.append(op_name.op_name)
            if op_name.suffix_list == filter.normal_suffix:
                filter.UnsignOpList.append(op_name.op_name)
            elif op_name.suffix_list == filter.widen_suffix:
                filter.SpWUnsignOpList.append(op_name.op_name)
            else:
                special_set.add(op_name.op_name)
                print("find a sign_fix_u suffix issue")
        else:
            # todo: float
            special_set.add(op_name.op_name)
    elif op_name.operand_type == filter.type_vw_vx:
        if op_name.sign_type == filter.sign_fix_i:
            if op_name.suffix_list == filter.type_widen_vx:
                filter.SpWsignOpList.append(op_name.op_name)
            else:
                special_set.add(op_name.op_name)
        elif op_name.sign_type == filter.sign_fix_u:
            if op_name.suffix_list == filter.type_widen_vx:
                filter.SpWUnsignOpList.append(op_name.op_name)
            else:
                special_set.add(op_name.op_name)
        elif op_name.sign_type == filter.sign_iu:
            print("find a widen but i or u is not fixed")
            special_set.add(op_name.op_name)
        else:
            # todo: for float
            special_set.add(op_name.op_name)
    elif op_name.operand_type == filter.type_extension:
        # operand type: vf2 vf4 vf8
        if op_name.sign_type == filter.sign_fix_i:
            if op_name.suffix_list == filter.widen_suffix:
                filter.SignExtOpList.append(op_name.op_name)
            else:
                print(op_name.op_name)
                print("find a special sign extension type suffix issue")
                special_set.add(op_name.op_name)
        elif op_name.sign_type == filter.sign_fix_u:
            if op_name.suffix_list == filter.widen_suffix:
                filter.ZeroExtOpList.append(op_name.op_name)
            else:
                print("find a special zero extension type suffix issue")
                special_set.add(op_name.op_name)
        else:
            print("find a special extension issue")
            special_set.add(op_name.op_name)
    elif op_name.operand_type == filter.type_middle_mask_and_normal_vx:
        if op_name.sign_type == filter.sign_iu:
            if op_name.suffix_list == filter.normal_suffix:
                filter.Sp2MaskOpList.append(op_name.op_name)
            else:
                print("find a special mask carry in issue")
                special_set.add(op_name.op_name)
        else:
            print("find a sign mask carry in issue")
    elif op_name.operand_type == filter.type_middle_mask:
        if op_name.sign_type == filter.sign_iu:
            if op_name.suffix_list == filter.normal_suffix:
                filter.SpMaskOpList.append(op_name.op_name)
            else:
                print("find a middle mask and suffix issue")
        else:
            print("find a middle mask and sign issue")
    elif op_name.operand_type == filter.type_vf:
        if op_name.sign_type == filter.float:
            if op_name.suffix_list == filter.widen_suffix:
                filter.FloatOpList.append(op_name.op_name)
            elif op_name.suffix_list == filter.widen_widen_suffix:
                filter.FloatWOpList.append(op_name.op_name)
            else:
                print("find a float point suffix issue")
        else:
            print("find a float point type issue")
    elif op_name.operand_type == filter.only_v:
        if op_name.sign_type == filter.float:
            if op_name.suffix_list == filter.widen_suffix:
                filter.FloatVOpList.append(op_name.op_name)
            else:
                print("find a float point only v suffix issue.")
        elif op_name.sign_type == filter.sign_fix_u:
            if op_name.suffix_list == filter.widen_suffix:
                filter.FloatUOpList.append(op_name.op_name)
            else:
                print("find a float point unsign only v suffix issue.")
        else:
            print("find a float point only v type issue")
    elif op_name.operand_type == filter.type_f:
        if op_name.sign_type == filter.float:
            if op_name.suffix_list == filter.widen_suffix:
                filter.FloatFOpList.append(op_name.op_name)
            else:
                print("find a float point vf suffix issue.")
        else:
            print("find a float sign type issue")
    elif op_name.operand_type == filter.type_vw_vf:
        if op_name.sign_type == filter.float:
            if op_name.suffix_list == filter.widen_widen_suffix:
                filter.FloatWWOpList.append(op_name.op_name)
            else:
                print("find a float point widen suffix isuue.")
        else:
            print("find a float point widen issue.")


for file in filelist:
    temp = str(file)
    sn = temp.split('_')
    file_to_test = sys.argv[1]
    if sn[0] == file_to_test:
        # Temporarily use a file to debug
        with open(os.path.join(location, file)) as f:
            for line in f:
                if '__riscv_' not in line:
                    continue
                mask = 0
                vxrm = random.randint(0, 3)
                C_example.append(c_function_parser(line))
                inf = name_parser(line)
                # inf[0]: function name op_parser[0],
                # inf[1]: operand type, vector or scalar. op_parser[1],
                # inf[2]: operand sign. op_parser[2][0],
                # inf[3]: sew + lmul. divided_suffix[1],
                # inf[4]: mask. mask_parser[0]
                # inf[5]: xrm
                if inf[3] == '':
                    special_set.add(inf[0])
                elif inf[1] == 'rtz':
                    special_set.add(inf[0])
                elif inf[3] == 'u':
                    special_set.add(inf[0])
                else:
                    function_set.add(inf[0])
            for i in function_set:
                instance_operand_type_set = set()
                instance_sign = set()
                instance_suffix = set()
                with open(os.path.join(location, file)) as w:
                    for line in w:
                        if '__riscv_' not in line:
                            continue
                        inf = name_parser(line)
                        if inf[0] == i:
                            instance_operand_type_set.add(inf[1])
                            instance_sign.add(inf[2])
                            instance_suffix.add(inf[3])
                            if inf[4] == 'm':
                                mask = 1
                            else:
                                continue
                            if inf[5] == 'rm':
                                vxrm = random.randint(0, 3)
                            else:
                                vxrm = 5
                        else:
                            continue
                    x = filter.Index()
                    x.op_name = i
                    x.sign_type = sorted(instance_sign)
                    x.operand_type = sorted(instance_operand_type_set)
                    x.suffix_list = sorted(instance_suffix)
                    x.mask = mask
                    x.vxrm = vxrm
                    op_instance_list.append(x)

# generate_file = open("product.txt", "a")
# generated 05~10

generate_file = open("one_time_product.txt", "w")

# c_function_template = open("c_template_lib.txt", "a")
# generated 05~10

c_function_template = open("one_time_c_template_lib.txt", "w")
for strs in C_example:
    c_function_template.writelines(strs)
    c_function_template.write("\n")

generate_file.write("function_set:\n" + str(function_set) + "\n")
for i in function_set:
    c_directory_auto_gen(i, c_dir_file_name)
# generate_file.write("operand_type_lists:\n" + str(operand_type_set) + "\n")
# generate_file.write("sign:\n" + str(sign) + "\n")
# generate_file.write("suffix:\n" + str(suffix) + "\n")
generate_file.write("special_set:\n" + str(special_set) + "\n")

for i in op_instance_list:
    judge(i)
    generate_file.write(f"\nfunction name:\n{i.op_name}\noperand type:\n{sorted(i.operand_type)}\nsign type:\n"
                        f"{sorted(i.sign_type)}\nsuffix list:\n{sorted(i.suffix_list)}\nmask:\n{i.mask}\n")

for i in op_instance_list:
    if i.sign_type not in sign_type_4_iterator:
        sign_type_4_iterator.append(i.sign_type)
        print(sign_type_4_iterator)
    else:
        continue
    if i.operand_type not in operand_type_4_iterator:
        operand_type_4_iterator.append(i.operand_type)
        print(operand_type_4_iterator)
    else:
        continue
    if sorted(i.suffix_list) not in suffix_type_4_iterator:
        suffix_type_4_iterator.append(sorted(i.suffix_list))
        print(suffix_type_4_iterator)
    else:
        continue
generate_file.write("sign_type_4_iterator:\n" + str(sign_type_4_iterator) + "\n")
generate_file.write("operand_type_4_iterator:\n" + str(operand_type_4_iterator) + "\n")
generate_file.write("suffix_type_4_iterator:\n" + str(suffix_type_4_iterator) + "\n")
generate_python = open("intrinsic_function_type_07.py", "w")
generate_python.write("#!/usr/bin/env python3\n")
generate_python.write("GeneralFormatOpList = " + str(filter.GeneralFormatOpList) + "\n")
generate_python.write("SignOpList = " + str(filter.SignOpList) + "\n")
generate_python.write("UnsignOpList = " + str(filter.UnsignOpList) + "\n")
generate_python.write("SpWsignOpList = " + str(filter.SpWsignOpList) + "\n")
generate_python.write("SpWUnsignOpList = " + str(filter.SpWUnsignOpList) + "\n")
generate_python.write("SpVOplist = " + str(filter.SpVOplist) + "\n")
generate_python.write("SpMaskOpList = " + str(filter.SpMaskOpList) + "\n")
generate_python.write("Sp2MaskOpList = " + str(filter.Sp2MaskOpList) + "\n")
generate_python.write("WSignOpList = " + str(filter.WSignOpList) + "\n")
generate_python.write("WUnsignOpList = " + str(filter.WUnsignOpList) + "\n")
generate_python.write("SpecialFormatList = " + str(filter.SpecialFormatList) + "\n")
generate_python.write("SpVOplist = " + str(filter.SpVOplist) + "\n")
generate_python.write("Sp2VOplist = " + str(filter.Sp2VOplist) + "\n")
generate_python.write("ZeroExtOpList = " + str(filter.ZeroExtOpList) + "\n")
generate_python.write("SignExtOpList = " + str(filter.SignExtOpList) + "\n")
generate_python.write("RMOpList = " + str(filter.RMOpList) + "\n")
generate_python.write("FloatOpList = " + str(filter.FloatOpList) + "\n")
generate_python.write("FloatVOpList = " + str(filter.FloatVOpList) + "\n")
generate_python.write("FloatWOpList = " + str(filter.FloatWOpList) + "\n")
generate_python.write("FloatUOpList = " + str(filter.FloatUOpList) + "\n")
generate_python.write("FloatFOpList = " + str(filter.FloatFOpList) + "\n")
generate_python.write("FloatWWOpList = " + str(filter.FloatWWOpList) + "\n")
