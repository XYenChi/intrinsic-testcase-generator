#!/usr/bin/env python3
sign_fix_i = ['i']
sign_fix_u = ['u']
sign_iu = ['i', 'u']
type_vx = ['vv', 'vx']
type_widen_vx = ['wv', 'wx']
class Index:
    def __init__(self):
        self.op_name = ''
        self.operand_num = set()
        # 1 for only vs2,
        self.operand_type = set()
        # v, x, w
        self.mask_type = set()
        # '', '_m', middle 'm'
        self.sign_type = set()
        # fixed i or u or both i and u
        self.suffix_list = set()
        self.suffix_type = ''
        # normal, narrow or widen

