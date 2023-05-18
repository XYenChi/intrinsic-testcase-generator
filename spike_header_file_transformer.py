#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import os
import collector

location = './riscv-isa-sim/riscv/insns'
function_set = set()
# save all the functions in spike head file
vector_function_set = set()
# save vector function
function_name_list = list()
# to write function

for i in collector.list_all_file(location):
    function_set = i

for i in sorted(function_set):
    if list(i)[0] == 'v':
        vector_function_set.add(i)
    else:
        continue

transformed_op_function = open("transformed_op_function.py", "w")
for i in vector_function_set:
    function_name = i.split('.')
    # remove .h suffix
    transformed_op_function.write("def " + str(function_name[0]) + "():\n")
