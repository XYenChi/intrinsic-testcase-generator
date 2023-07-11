#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
import os
import collector
import re

location = './riscv-isa-sim/riscv/insns'
function_set = set()
# save all the functions in spike head file
vector_function_set = set()
# save vector function
function_name_list = list()
# to write function
function_name_set = set()

for i in collector.list_all_file(location):
    function_set = i

for i in sorted(function_set):
    if list(i)[0] == 'v':
        vector_function_set.add(i)
    else:
        continue

transformed_op_function = open("transformed_op_function.py", "w")
for i in vector_function_set:
    function_name_rm_point = i.split('.')
    function_name = function_name_rm_point[0].split('_')
    function_name_set.add(function_name[0])
    # remove .h suffix

transformed_op_function.write("# Produced by spike_header_file_transformer.py, running "
                              "spike_header_file_transformer.py again will override this file.")
for i in sorted(function_name_set):
    transformed_op_function.write("def " + str(i) + "_op():\n")


