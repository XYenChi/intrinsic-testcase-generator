# Read/Write URW vector CSRs Usage:
# enum RVV_CSR {
#   RVV_VSTART = 0,
#   RVV_VXSAT,
#   RVV_VXRM,
#   RVV_VCSR,
# };
#
# unsigned long __riscv_vread_csr(enum RVV_CSR csr);
# void __riscv_vwrite_csr(enum RVV_CSR csr, unsigned long value);
#
# unsigned long __riscv_vlenb();
import random
import exe_op_generator

vstart = random.randint(0, 255)
vxsat = random.randint(0, 1)
vxrm = random.randint(0, 3)
vcsr = random.randint(0, 1)


def csr_write(vxrm, fd):
    fd.write("enum RVV_CSR {\nRVV_VSTART = 0,\nRVV_VXSAT,\nRVV_VXRM,\nRVV_VCSR,\n};\n")
    # void __riscv_vwrite_csr(enum RVV_CSR csr, unsigned long value);
    fd.write("void __riscv_vwrite_csr(%s, %s);" % (vxrm, exe_op_generator.avl / 8))


def int_rounding(result, xrm, gb):
    # todo: what is gb ?
    # gb represent the "d", the bits of result to be rounded off
    lsb = 1 << gb
    lsb_half = lsb >> 1
    match xrm:
        case 0:
            # RNU
            # round to nearest up(add + 0.5 LSB)
            result += lsb_half
        case 1:
            # RNE
            # round to nearest even
            if (result & lsb_half) & ((result & (lsb_half - 1)) | (result & lsb)):
                result += lsb
        case 2:
            # RDN
            # round-down (truncate)
            result = result
        case 3:
            # ROD
            # round to odd (OR bits into LSB, aka "jam")
            if result & (lsb - 1):
                result |= lsb
    return result >> gb


def sat_sub(vs2, vs1, sew, sat):
    uvs2 = vs2 & (sew - 1)
    uvs1 = vs1 & (sew - 1)
    res = uvs2 - uvs1
    sat = 0
# Calculate overflowed result.(Don't change the sign bit of ux) */
    ux = (uvs2 >> (sew - 1)) + ((1 << (sew - 1)) - 1)

# Force compiler to use cmovns instruction
    if ((uvs2 ^ uvs1) & (uvs2 ^ res)) <0:
        res = ux
        sat = 1
        return res, sat
