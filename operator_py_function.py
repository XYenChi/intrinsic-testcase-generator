def add_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        return a + b
        # todo: if vm = 0, but v0.mask[i] = 0, what vd will be.


def sub_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        return a - b


def mul_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        return a * b


def div_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        if a == 0:
            return -1
        else:
            return b // a


def max_op(a, b, c=None, m=None):
    if m == 0:
        return c
    else:
        if a > b:
            return a
        else:
            return b


def min_op(a, b, c=None, m=None):
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


def add_with_carry_op(a, b, c=None, m=None):
    if m == 1:
        return a + b + m
    else:
        return a + b


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


def multiply_add_overwrite_addend_op(c, a, b, m=None):
    #vmacc
    if m == 0:
        return c
    else:
        return a * b + c

def multiply_add_overwrite_multiplicand_op(c, a, b, m=None):
    #vmadd
    if m == 0:
        return c
    else:
        return b * c + a
def substract_with_borrow_op(c, a, b, m=None):
    #vmsbc
    # Produce borrow out in mask register format
    if m == 0:



def equal_op(a, b, n, m=None):
    #n present the vd.mask
    if m == 0:
        return n
    else:
        if a == b:
            return 1
        else:
            return 0


