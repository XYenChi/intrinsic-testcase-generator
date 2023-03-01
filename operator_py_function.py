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
        if b == 0:
            return -1
        else:
            return a // b


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
        if b == 0:
            return a
        else:
            return a % b


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
def multiply_add_op(c, a, b, m=None):
    if m == 0:
        return c
    else:
        return a*b+c

  #  def equal_op(a, b, m):
