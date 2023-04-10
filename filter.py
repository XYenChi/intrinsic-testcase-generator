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



