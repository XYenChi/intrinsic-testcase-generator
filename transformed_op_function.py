# Produced by spike_header_file_transformer.py, running spike_header_file_transformer.py again will override this file.def vaadd_op():
def vaaddu_op():

def vadc_op(vs2, vs1, carryin):
    return vs2 + vs1 + carryin

def vadd_op(vs2, vs1, vd=None, m=None):
    # vadd vwadd
    if m == 0:
        return vd
    else:
        return vs2 + vs1

# don't deal with them now
# def vamoaddei16_op():
# def vamoaddei32_op():
# def vamoaddei64_op():
# def vamoaddei8_op():
# def vamoandei16_op():
# def vamoandei32_op():
# def vamoandei64_op():
# def vamoandei8_op():
# def vamomaxei16_op():
# def vamomaxei32_op():
# def vamomaxei64_op():
# def vamomaxei8_op():
# def vamomaxuei16_op():
# def vamomaxuei32_op():
# def vamomaxuei64_op():
# def vamomaxuei8_op():
# def vamominei16_op():
# def vamominei32_op():
# def vamominei64_op():
# def vamominei8_op():
# def vamominuei16_op():
# def vamominuei32_op():
# def vamominuei64_op():
# def vamominuei8_op():
# def vamoorei16_op():
# def vamoorei32_op():
# def vamoorei64_op():
# def vamoorei8_op():
# def vamoswapei16_op():
# def vamoswapei32_op():
# def vamoswapei64_op():
# def vamoswapei8_op():
# def vamoxorei16_op():
# def vamoxorei32_op():
# def vamoxorei64_op():
# def vamoxorei8_op():

def vand_op(vs2, vs1, vd=None, m=None):
    vd = vs1 & vs2
    return vd

def vasub_op():

def vasubu_op():

def vcompress_op():

def vcpop_op():

def vdiv_op(vs2, vs1, vd=None, m=None):
    # vdiv
    if m == 0:
        return vd
    else:
        if vs1 == 0:
            return -1
        else:
            return vs2 // vs1

def vdivu_op(vs2, vs1, vd=None, m=None):
    # vdivu
    if m == 0:
        return vd
    else:
        if vs1 == 0:
            return -1
        else:
            return vs2 // vs1


def vfadd_op():

def vfclass_op():

def vfcvt_op():
def vfdiv_op():
def vfirst_op():
def vfmacc_op():
def vfmadd_op():
def vfmax_op():
def vfmerge_op():
def vfmin_op():
def vfmsac_op():
def vfmsub_op():
def vfmul_op():
def vfmv_op():
def vfncvt_op():
def vfnmacc_op():
def vfnmadd_op():
def vfnmsac_op():
def vfnmsub_op():
def vfrdiv_op():
def vfrec7_op():
def vfredmax_op():
def vfredmin_op():
def vfredosum_op():
def vfredusum_op():
def vfrsqrt7_op():
def vfrsub_op():
def vfsgnj_op():
def vfsgnjn_op():
def vfsgnjx_op():
def vfslide1down_op():
def vfslide1up_op():
def vfsqrt_op():
def vfsub_op():
def vfwadd_op():
def vfwcvt_op():
def vfwmacc_op():
def vfwmsac_op():
def vfwmul_op():
def vfwnmacc_op():
def vfwnmsac_op():
def vfwredosum_op():
def vfwredusum_op():
def vfwsub_op():

def vid_op():

def viota_op():


# don't deal with load and store instruction now
# def vl1re16_op():
# def vl1re32_op():
# def vl1re64_op():
# def vl1re8_op():
# def vl2re16_op():
# def vl2re32_op():
# def vl2re64_op():
# def vl2re8_op():
# def vl4re16_op():
# def vl4re32_op():
# def vl4re64_op():
# def vl4re8_op():
# def vl8re16_op():
# def vl8re32_op():
# def vl8re64_op():
# def vl8re8_op():
# def vle16_op():
# def vle16ff_op():
# def vle32_op():
# def vle32ff_op():
# def vle64_op():
# def vle64ff_op():
# def vle8_op():
# def vle8ff_op():
# def vlm_op():
# def vloxei16_op():
# def vloxei32_op():
# def vloxei64_op():
# def vloxei8_op():
# def vlse16_op():
# def vlse32_op():
# def vlse64_op():
# def vlse8_op():
# def vluxei16_op():
# def vluxei32_op():
# def vluxei64_op():
# def vluxei8_op():

def vmacc_op(vs2, vs1, vd, m=None):
    if m == 0:
        return vd
    else:
        vd = vs1 * vs2 + vd
        return vd

def vmadc_op(vs2, vs1, m=None):
    # vmadc
    return vs2 + vs1 + m

def vmadd_op(vs2, vs1, vd, m=None):
    # vmadd
    if m == 0:
        return vd
    else:
        return vs1 * vd + vs2

def vmand_op():

def vmandn_op():

def vmax_op(vs2, vs1, vd, m=None):
    # vmax
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            return vs2
        else:
            return vs1

def vmaxu_op(vs2, vs1, vd, m=None):
    # vmaxu
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            return vs2
        else:
            return vs1

def vmerge_op(vs2, vs1, m):
    # always should be masked
    if m == 0:
        return vs2
    else:
        return vs1

def vmfeq_op():
def vmfge_op():
def vmfgt_op():
def vmfle_op():
def vmflt_op():
def vmfne_op():

def vmin_op(vs2, vs1, vd=None, m=None):
    # vmin
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            return vs2
        else:
            return vs1

def vminu_op(vs2, vs1, vd=None, m=None):
    # vminu
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            return vs2
        else:
            return vs1

# todo: need vs2.mask[i] and vs1.mask[i]
def vmnand_op():
def vmnor_op():
def vmor_op():
def vmorn_op():

def vmsbc_op(vs2, vs1, vd, m):
    # Produce borrow out in mask register format
    if m == 0:
        if vs2 >= vs1:
            vd = 0
            return vd
        else:
            vd = 1
            return vd
    else:
        if vs2 >= (vs1 - 1):
            vd = 0
            return vd
        else:
            vd = 1
            return vd
def vmsbf_op():
def vmseq_op(vs2, vs1, n, m=None):
    # vmseq
    # n present the vd.mask
    if m == 0:
        return n
    else:
        if vs2 == vs1:
            return 1
        else:
            return 0

def vmsgt_op(vs2, vs1, vd, m=None):
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsgtu_op(vs2, vs1, vd, m=None):
    if m == 0:
        return vd
    else:
        if vs2 > vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsif_op():
def vmsle_op(vs2, vs1, vd, m=None):
    # vmsle
    if m == 0:
        return vd
    else:
        if vs2 <= vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsleu_op(vs2, vs1, vd, m=None):
    # vmsleu
    if m == 0:
        return vd
    else:
        if vs2 <= vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmslt_op(vs2, vs1, vd, m=None):
    # vmslt
    if m == 0:
        return vd
    else:
        if vs2 < vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsltu_op(vs2, vs1, vd, m=None):
    # vmsltu
    if m == 0:
        return vd
    else:
        if vs2 <= vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsne_op(vs2, vs1, vd, m=None):
    # vmsne
    if m == 0:
        return vd
    else:
        if vs2 != vs1:
            vd = 1
            return vd
        else:
            vd = 0
            return vd
def vmsof_op():
def vmul_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vmulh_op(vs2, vs1, vd=None, m=None):
    # vmul
    # resolved operand width issue at the exe_op_generator
    # todo: optimize filter method
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vmulhsu_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vmulhu_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vmv_op(vs2):
    # vmv
    return vs2
def vmv1r_op():
def vmv2r_op():
def vmv4r_op():
def vmv8r_op():
def vmvnfr_op():
def vmxnor_op():
    # need vs2.mask[i] and vs1.mask[i]
def vmxor_op():
    # need vs2.mask[i] and vs1.mask[i]
def vnclip_op():
def vnclipu_op():
def vnmsac_op(vs2, vs1, vd, m=None):
    # vnmsac
    # Integer multiply-sub, overwrite minuend
    if m == 0:
        return vd
    else:
        vd = -(vs2 * vs1) + vd
        return vd
def vnmsub_op(vs2, vs1, vd, m=None):
    # vnmsub
    # vd[i] = -(vs1[i] * vd[i]) + vs2[i]
    if m == 0:
        return vd
    else:
        vd = -(vs1 * vd) + vs2
        return vd
def vnsra_op(vs2, vs1, sew, vd, m=None):
    if m == 0:
        return vd
    else:
        vd = vs2 >> (vs1 & (sew * 2 - 1))
        return vd
def vnsrl_op(vs2, vs1, sew, vd, m=None):
    # operand type should be unsign
    if m == 0:
        return vd
    else:
        vd = vs2 >> (vs1 & (sew * 2 - 1))
        return vd
def vor_op(vs2, vs1, vd, m=None):
    # vor
    if m == 0:
        return vd
    else:
        vd = vs1 | vs2
        return vd
def vredand_op():
def vredmax_op():
def vredmaxu_op():
def vredmin_op():
def vredminu_op():
def vredor_op():
def vredsum_op():
def vredxor_op():
def vrem_op(vs2, vs1, vd=None, m=None):
    if m == 0:
        return vd
    else:
        if vs1 == 0:
            return vs2
        else:
            return vs2 % vs1
def vremu_op(vs2, vs1, vd=None, m=None):
    if m == 0:
        return vd
    else:
        if vs1 == 0:
            return vs2
        else:
            return vs2 % vs1
def vrgather_op():
def vrgatherei16_op():
def vrsub_op(vs2, vs1, vd=None, m=None):
    # vrsub
    if m == 0:
        return vd
    else:
        return vs1 - vs2

# don't deal with load and store function now
# def vs1r_op():
# def vs2r_op():
# def vs4r_op():
# def vs8r_op():
def vsadd_op():
def vsaddu_op():
def vsbc_op(vs2, vs1, c=None, m=None):
    if m == 1:
        return vs2 - vs1 - m
    else:
        return vs2 - vs1

# don't deal with load and store now
# def vse16_op():
# def vse32_op():
# def vse64_op():
# def vse8_op():

# set avl = 64 bit now
# def vsetivli_op():
# def vsetvl_op():
# def vsetvli_op():


# don't need sign extension python golden function to calculate now
# def vsext_op():
def vslide1down_op():
def vslide1up_op():
def vslidedown_op():
def vslideup_op():
def vsll_op(vs2, vs1, vd, sew, m=None):
    # vsll
    if m == 0:
        return vd
    else:
        vd = vs2 << (vs1 & (sew - 1))
        return vd

def vsmul_op():

# don't deal with load and store now
# def vsm_op():
# def vsoxei16_op():
# def vsoxei32_op():
# def vsoxei64_op():
# def vsoxei8_op():
def vsra_op(vs2, vs1, vd, sew, m=None):
    # vsra
    if m == 0:
        return vd
    else:
        vd = vs2 >> (vs1 & (sew - 1))
        return vd
def vsrl_op(vs2, vs1, vd, sew, m=None):
    # vsrl
    if m == 0:
        return vd
    else:
        vd = vs2 >> (vs1 & (sew - 1))
        return vd

# don't deal with load and store now
# def vsse16_op():
# def vsse32_op():
# def vsse64_op():
# def vsse8_op():
def vssra_op():
def vssrl_op():
def vssub_op():
def vssubu_op():
def vsub_op(vs2, vs1, vd=None, m=None):
    # vsub
    if m == 0:
        return vd
    else:
        return vs2 - vs1

# don't deal with load and store now
# def vsuxei16_op():
# def vsuxei32_op():
# def vsuxei64_op():
# def vsuxei8_op():
def vwadd_op(vs2, vs1, vd=None, m=None):
    # vadd vwadd
    if m == 0:
        return vd
    else:
        return vs2 + vs1
def vwaddu_op(vs2, vs1, vd=None, m=None):
    # vadd vwadd
    if m == 0:
        return vd
    else:
        return vs2 + vs1
def vwmacc_op(vs2, vs1, vd=None, m=None):
    # vmacc
    if m == 0:
        return vd
    else:
        return vs2 * vs1 + vd
def vwmaccsu_op(vs2, vs1, vd=None, m=None):
    # vmacc
    if m == 0:
        return vd
    else:
        return vs2 * vs1 + vd
def vwmaccu_op(vs2, vs1, vd=None, m=None):
    # vmacc
    if m == 0:
        return vd
    else:
        return vs2 * vs1 + vd
def vwmaccus_op(vs2, vs1, vd=None, m=None):
    # vmacc
    if m == 0:
        return vd
    else:
        return vs2 * vs1 + vd
def vwmul_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vwmulsu_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vwmulu_op(vs2, vs1, vd=None, m=None):
    # vmul
    if m == 0:
        return vd
    else:
        return vs2 * vs1
def vwredsum_op():
def vwredsumu_op():
def vwsub_op(vs2, vs1, vd=None, m=None):
    # vsub
    if m == 0:
        return vd
    else:
        return vs2 - vs1
def vwsubu_op(vs2, vs1, vd=None, m=None):
    # vsub
    if m == 0:
        return vd
    else:
        return vs2 - vs1
def vxor_op(vs2, vs1, vd=None, m=None):
    if m == 0:
        return vd
    else:
        vd = vs1 ^ vs2
        return vd

# def vzext_op():
# calculated at the exe_op_generator, don't need now
# todo: optimize the exe_op_generator