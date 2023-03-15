def add_op(a, b, c=None, m=None):
    # vadd
    if m == 0:
        return c
    else:
        return a + b


def sub_op(a, b, c=None, m=None):
    # vsub
    if m == 0:
        return c
    else:
        return a - b


def mul_op(a, b, c=None, m=None):
    # vmul
    if m == 0:
        return c
    else:
        return a * b


def div_op(a, b, c=None, m=None):
    # vdiv
    if m == 0:
        return c
    else:
        if a == 0:
            return -1
        else:
            return b // a


def max_op(a, b, c=None, m=None):
    # vmax
    if m == 0:
        return c
    else:
        if a > b:
            return a
        else:
            return b


def min_op(a, b, c=None, m=None):
    # vmin
    if m == 0:
        return c
    else:
        if a > b:
            return a
        else:
            return b


def reminder(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        if a == 0:
            return b
        else:
            return b % a


def add_with_carry_op(a, b, m):
    return a + b + m


def sub_with_borrow_op(a, b, c=None, m=None):
    if m == 1:
        return a - b - m
    else:
        return a - b


def and_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        return a and b


def merge_op(a, b, m):
    # always should be masked
    if m == 0:
        return a
    else:
        return b


def multiply_add_overwrite_addend_op(a, b, c=None, m=None):
    # vmacc
    if m == 0:
        return c
    else:
        return a * b + c


def multiply_add_overwrite_multiplicand_op(c, a, b, m=None):
    # vmadd
    if m == 0:
        return c
    else:
        return b * c + a


def multiply_sbc_overwrite_multiplicand_op(c, a, b, m=None):
    # vmsbc
    # Produce borrow out in mask register format
    if m == 0:
        if a >= b:
            c = 0
            return c
        else:
            c = 1
            return c
    else:
        if a >= (b - 1):
            c = 0
            return c
        else:
            c = 1
            return c


def equal_to_op(a, b, n, m=None):
    # vmseq
    # n present the vd.mask
    if m == 0:
        return n
    else:
        if a == b:
            return 1
        else:
            return 0


def not_equal_to_op(a, b, n, m=None):
    # vmsne
    # n present the vd.mask
    if m == 0:
        return n
    else:
        if a == b:
            return 0
        else:
            return 1


def move_op(a):
    # vmv
    return a


def neg_op(a):
    # vneg
    return -a


def not_op(a, c=None, m=None):
    # vnot
    if m == 0:
        return c
    else:
        return a ^ -1


def add_with_carry_return_mask_op(a, b, m):
    # vmadc
    return a + b + m


def sub_with_borrow_return_mask_op(a, b, m):
    # vmsbc
    return a - b - m


def nmsac_op(a, b, c, m=None):
    # vnmsac
    # Integer multiply-sub, overwrite minuend
    if m == 0:
        return c
    else:
        c = -(a * b) + c
        return c


def nmsub_op(a, b, c, m=None):
    # vnmsub
    # vd[i] = -(vs1[i] * vd[i]) + vs2[i]
    if m == 0:
        return c
    else:
        c = -(b * c) + a
        return c


def or_op(a, b, c, m=None):
    # vor
    if m == 0:
        return c
    else:
        c = a | b
        return c


def shift_right_op(a, b, c, m=None):
    # vsra, vsrl
    if m == 0:
        return c
    else:
        c = a >> b
        return c


def shift_left_op(a, b, c, m=None):
    # vsll
    if m == 0:
        return c
    else:
        c = a << b
        return c


def greater_equal_op(a, b, c, m=None):
    # vmsge
    if m == 0:
        return c
    else:
        if a >= b:
            c = 1
            return c
        else:
            c = 0
            return c


def less_equal_op(a, b, c, m=None):
    # vmsle
    if m == 0:
        return c
    else:
        if a <= b:
            c = 1
            return c
        else:
            c = 0
            return c


def less_than_op(a, b, c, m=None):
    # vmslt
    if m == 0:
        return c
    else:
        if a < b:
            c = 1
            return c
        else:
            c = 0
            return c


def greater_than_op(a, b, c, m=None):
    # vmsge
    if m == 0:
        return c
    else:
        if a > b:
            c = 1
            return c
        else:
            c = 0
            return c


def reverse_sub_op(a, b, c=None, m=None):
    # vrsub
    if m == 0:
        return c
    else:
        return b - a


def xor_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        if a == b:
            c = 0
            return c
        else:
            c = 1
            return c
