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
        return a / b


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
