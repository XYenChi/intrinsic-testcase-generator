#!/usr/bin/env python3
# default parameter reference:
#    vs/rs2 --> b
#    vs/rs1 --> a
#    vd --> self.input_ops[2].val

# don't know how to calculate:
#   vwsub: Widening unsigned integer add/subtract, 2*SEW = SEW +/- SEW
#   vmadc: vd.mask[i] = carry_out(vs2[i] + vs1[i] + v0.mask[i])
#   vmseq: Unit-stride Fault-Only-First Loads

# with mask:
#   vmslt:
#   vmsgt:
#   vmsqge:
#   vmsltu:
#   vwmul:
#   vwmacc

# def less_than (self):
#    ops_mask[]
#    a
#    b

def max_(self):
    # vmaxu
    if not self.mask:
        # if v0.mask[i] = 0, do nothing and return
        return
    else:
        if a > b:
            return a
        else:
            return b


def min_(self):
    # vminu
    if not self.mask:
        # if v0.mask[i] = 0, do nothing and return
        return
    else:
        if a < b:
            return a
        else:
            return b


def add(self):
    # vadd
    # vwadd
    # vwaddu
    if not self.mask:
        # if v0.mask[i] = 0, do nothing and return
        return
    else:
        # if unmasked or v0.mask[i] = 1, execute.
        if self.immediate:
            return a + self.immediate
        else:
            return a + b


def add_with_carry(self):
    # vmadc
    if self.mask:
        return a + b + self.mask
    else:
        return a + b


def substract(self):
    # vnmsub
    return a - b

def substract_with_carry(self):
    # vmsbc
    if self.mask:
        return a - self.input_ops - self.mask
    else:
        return self.input_ops[0] - b

def reverse_sub(self):
    # vrsub
    return b - a


def move(self):
    # vmv
    if self.immediate:
        return self.immediate
    else:
        return a


def multiply(self):
    # vwmul
    # vwmulsu : the widening feature depends on the passed parameter,
    #           result calculated with python couldn't represent difference.
    # vwmulu
    return a * b


def divide(self):
    # vdivu
    return a / b


def reminder(self):
    # vrem
    return a % b


def xor(self):
    # vxor
    return a ^ b


def zext_sew8_vf2(self):
    # vzext SEW=8 Zero-extend SEW/2 source to SEW destination
    return a & 0b1111


def zext_sew8_vf4(self):
    # vzext SEW=8 Zero-extend SEW/4 source to SEW destination
    return a & 0b11


def zext_sew8_vf8(self):
    # vzext SEW=8 Zero-extend SEW/8 source to SEW destination
    return a & 0b1


def zext_sew16_vf2(self):
    # vzext SEW=16 Zero-extend SEW/2 source to SEW destination
    return a & 0b11111111


def zext_sew16_vf4(self):
    # vzext SEW=16 Zero-extend SEW/4 source to SEW destination
    return a & 0b1111


def zext_sew16_vf8(self):
    # vzext SEW=16 Zero-extend SEW/8 source to SEW destination
    return a & 0b11


def zext_sew32_vf2(self):
    # vzext SEW=32 Zero-extend SEW/2 source to SEW destination
    return a & 0b11111111


def zext_sew32_vf4(self):
    # vzext SEW=32 Zero-extend SEW/4 source to SEW destination
    return a & 0b1111


def zext_sew32_vf8(self):
    # vzext SEW=32 Zero-extend SEW/8 source to SEW destination
    return a & 0b1111


def zext_sew64_vf2(self):
    # vzext SEW=64 Zero-extend SEW/2 source to SEW destination
    return a & 0b11111111111111111111111111111111


def zext_sew64_vf4(self):
    # vzext SEW=64 Zero-extend SEW/4 source to SEW destination
    return a & 0b1111111111111111


def zext_sew64_vf8(self):
    # vzext SEW=64 Zero-extend SEW/8 source to SEW destination
    return a & 0b11111111


def Mulyiply_Add(self):
    # vmacc
    # vwmaccsu
    return (a * b) + self.input_ops[2].val


def single_width_right_shift_logical_sew8(self):
    # vsrl log2(SEW)=3
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b111
            return a >> uimm
        else:
            shift = b & 0b111
            return self.input_ops[0] .val >> shift


def single_width_right_shift_logical_sew16(self):
    # vsrl log2(SEW)=4
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b1111
            return a >> uimm
        else:
            shift = b & 0b1111
            return a >> shift


def single_width_right_shift_logical_sew32(self):
    # vsrl log2(SEW)=5
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b11111
            return a >> uimm
        else:
            shift = b & 0b11111
            return a >> shift

def single_width_right_shift_logical_sew64(self):
    # vsrl log2(SEW)=6
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b111111
            return a >> uimm
        else:
            shift = self.input_ops[1] & 0b111111
            return a >> shift

def single_width_right_shift_arithmetic_sew8(self):
    # vsra log2(SEW)=3
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b111
            sign = a & 0b100
            if sign:
                return -(a & 0b11 >> uimm)
            else:
                return a & 0b11 >> uimm
        else:
            shift = b & 0b111
            sign = a & 0b100
            if sign:
                return -(a & 0b11 >> shift)
            else:
                return a & 0b11 >> shift

def single_width_right_shift_alarithmetic_sew16(self):
    # vsra log2(SEW)=4
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b1111
            sign = a & 0b1000
            if sign:
                return -(a & 0b111 >> uimm)
            else:
                return a & 0b111 >> uimm
        else:
            shift = b & 0b1111
            sign = a & 0b1000
            if sign:
                return -(a & 0b111 >> shift)
            else:
                return a & 0b111 >> shift


def single_width_right_shift_arithmetic_sew32(self):
    # vsrl log2(SEW)=5
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b11111
            sign = a & 0b10000
            if sign:
                return -(a & 0b1111 >> uimm)
            else:
                return a & 0b1111 >> uimm
        else:
            shift = b & 0b11111
            sign = a & 0b10000
            if sign:
                return -(a & 0b1111 >> shift)
            else:
                return a & 0b1111 >> shift

def single_width_right_shift_arithmetic_sew64(self):
    # vsrl log2(SEW)=6
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b111111
            sign = a & 0b100000
            if sign:
                return -(a & 0b11111 >> uimm)
            else:
                return a & 0b11111 >> uimm
        else:
            shift = b & 0b111111
            sign = a & 0b100000
            if sign:
                return -(a & 0b11111 >> shift)
            else:
                return a & 0b11111 >> shift

def narrowing_width_right_shift_logical_sew16(self):
    # vnsrl log2(SEW)=4
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b1111
            return a >> uimm & 0b111
        else:
            shift = b & 0b1111
            return a >> shift & 0b111


def narrowing_width_right_shift_logical_sew32(self):
    # vnsrl log2(SEW)=5
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b11111
            return a >> uimm & 0b1111
        else:
            shift = b & 0b11111
            return a >> shift & 0b1111


def narrowing_width_right_shift_logical_sew64(self):
    # vnsrl log2(SEW)=6
    if not self.mask:
        return
    else:
        if self.immediate:
            uimm = self.immediate & 0b111111
            return a >> uimm & 0b11111
        else:
            shift = self.input_ops[1] & 0b111111
            return a >> shift & 0b11111

def multiply_add(self):
    # vwmacc
    if not self.mask:
        # if v0.mask[i] = 0, do nothing and return
        return
    else:
        # if v0.mask[i] = 1 or unmaskes, execute.
        return self.input_ops[0] * self.input_ops[1] + self.input_ops[2]


def less_than_equal(self):
    # vmsleu
    # vmsle
    if self.immediate:
        if self.immediate_sign == 0:
            self.immediate_bit = 5
            immediate = self.immediate & 0b11111
            if a <= immediate:
                return a
            else:
                return immediate
        else:
            immediate_abs = self.immediate & 0b1111
            immediate_sign = self.immediate & 0b10000
            if immediate_sign == 1:
                immediate = -immediate_abs-1
                if a <= immediate:
                    return a
                else:
                    return immediate
            else:
                if a <= immediate_abs:
                    return a
                else:
                    return immediate_abs
    else:
        if a <= b:
            return a
        else:
            return b



