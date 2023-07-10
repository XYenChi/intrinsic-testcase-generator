#!/usr/bin/env python3
# sign type
sign_fix_i = ['i']
sign_fix_u = ['u']
sign_iu = ['i', 'u']

# operand type
type_vx = ['vv', 'vx']
only_v = ['v']
type_widen_vx = ['wv', 'wx']
type_vw_vx = ['vx', 'vv', 'wx', 'wv']
type_extension = ['vf2', 'vf4', 'vf8']
type_middle_mask = ['vvm', 'vxm']
type_middle_mask_and_normal_vx = ['vv', 'vvm', 'vx', 'vxm']

# todo: Change the exe_op_generator variant name to iterate
vx_list = ['v', 'x']
wv_list = ['v', 'w']
iu_list = ['i', 'u']
ext_list = ['f2', 'f4', 'f8']

# suffix type
normal_suffix = ['16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4', '32m1', '32m2', '32m4', '32m8', '32mf2', '64m1',
                 '64m2', '64m4', '64m8', '8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8']
widen_suffix = ['16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4', '32m1', '32m2', '32m4', '32m8', '32mf2', '64m1',
                '64m2', '64m4', '64m8']
narrow_suffix = []

GeneralFormatOpList = []
# 'vadd', 'vand', 'vmacc', 'vmadd', 'vmseq', 'vmsne', 'vmul', 'vnmsac', 'vnmsub', 'vor', 'vrsub',
#                    'vsll', 'vsub', 'vxor']
# loop _vx, _iu, _suffix, _mask
SpMaskOpList = []
# 'vadc', 'vmerge']
# loop _vx, _iu, _suffix, have to with middle mask
Sp2MaskOpList = []
# 'vmadc', 'vmsbc']
# loop _vx, _iu, _suffix, and middle mask. don't have _mask
SignOpList = []
# 'vdiv', 'vmax', 'vmin', 'vmsge', 'vmsgt', 'vmsle', 'vmslt', 'vmulh', 'vmulhsu', 'vrem', 'vsra', 'vwmacc',
#           'vwmaccsu', 'vwmul', 'vwmulsu']
# loop _vx, _suffix, _mask, with fixed i
WSignOpList = []
# 'vnsra', 'vwmaccus']
# loop different position _vx(vnsra) or fixed vx , _suffix, _mask, with fixed i
SpWsignOpList = []
# 'vwadd', 'vwsub']
# loop _wv, _vx , _suffix, _mask, with fixed i
UnsignOpList = []
# 'vdivu', 'vmaxu', 'vminu', 'vmsgeu', 'vmsgtu', 'vmsleu', 'vmsltu', 'vmulhu', 'vremu', 'vsrl', 'vwmaccu',
#             'vwmaccu', 'vwmulu']
# loop _vx, _suffix, _mask with fixed u
WUnsignOpList = []
# 'vnsrl']
# loop different position _vx , _suffix, _mask, with fixed u
SpWUnsignOpList = []
# 'vwaddu', 'vwsubu']
# loop _wv, _vx , _suffix, _mask, with fixed u
SpecialFormatList = []
# 'vmv']
# loop _iu, _suffix and _vx with "_"
SpVOplist = []
# 'vneg']
# loop _suffix, _mask and only v, with fixed i
Sp2VOplist = []
# 'vnot']
# loop _suffix, _iu, _mask and only v
ZeroExtOpList = []
# 'vzext']
# loop _ext, _suffix, _mask with fixed u
SignExtOpList = []

RMOpList = []

# 'vsext']
# loop _ext, _suffix, _mask with fixed i
class Index:
    def __init__(self):
        self.op_name = ''
        self.operand_num = set()
        # 1 for only vs2,
        self.operand_type = set()
        # v, x, w
        self.mask = None
        # '', '_m', middle 'm'
        self.sign_type = set()
        # fixed i or u or both i and u
        self.suffix_list = set()
        self.suffix_type = ''
        self.vxrm = None
        # normal, narrow or widen
