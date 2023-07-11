# Read/Write URW vector CSRs Usage:
# enum __RISCV_VXRM {
#   __RISCV_VXRM_RNU = 0,
#   __RISCV_VXRM_RNE = 1,
#   __RISCV_VXRM_RDN = 2,
#   __RISCV_VXRM_ROD = 3,
# };
#

# import exe_op_generator

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
    if ((uvs2 ^ uvs1) & (uvs2 ^ res)) < 0:
        res = ux
        sat = 1
        return res, sat
