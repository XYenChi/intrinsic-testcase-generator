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

def vmnand_op():

def vmnor_op():
def vmor_op():
def vmorn_op():
def vmsbc_op():
def vmsbf_op():
def vmseq_op():
def vmsgt_op():
def vmsgtu_op():
def vmsif_op():
def vmsle_op():
def vmsleu_op():
def vmslt_op():
def vmsltu_op():
def vmsne_op():
def vmsof_op():
def vmul_op():
def vmulh_op():
def vmulhsu_op():
def vmulhu_op():
def vmv_op():
def vmv1r_op():
def vmv2r_op():
def vmv4r_op():
def vmv8r_op():
def vmvnfr_op():
def vmxnor_op():
def vmxor_op():
def vnclip_op():
def vnclipu_op():
def vnmsac_op():
def vnmsub_op():
def vnsra_op():
def vnsrl_op():
def vor_op():
def vredand_op():
def vredmax_op():
def vredmaxu_op():
def vredmin_op():
def vredminu_op():
def vredor_op():
def vredsum_op():
def vredxor_op():
def vrem_op():
def vremu_op():
def vrgather_op():
def vrgatherei16_op():
def vrsub_op():
def vs1r_op():
def vs2r_op():
def vs4r_op():
def vs8r_op():
def vsadd_op():
def vsaddu_op():
def vsbc_op():
def vse16_op():
def vse32_op():
def vse64_op():
def vse8_op():
def vsetivli_op():
def vsetvl_op():
def vsetvli_op():
def vsext_op():
def vslide1down_op():
def vslide1up_op():
def vslidedown_op():
def vslideup_op():
def vsll_op():
def vsm_op():
def vsmul_op():
def vsoxei16_op():
def vsoxei32_op():
def vsoxei64_op():
def vsoxei8_op():
def vsra_op():
def vsrl_op():
def vsse16_op():
def vsse32_op():
def vsse64_op():
def vsse8_op():
def vssra_op():
def vssrl_op():
def vssub_op():
def vssubu_op():
def vsub_op():
def vsuxei16_op():
def vsuxei32_op():
def vsuxei64_op():
def vsuxei8_op():
def vwadd_op():
def vwaddu_op():
def vwmacc_op():
def vwmaccsu_op():
def vwmaccu_op():
def vwmaccus_op():
def vwmul_op():
def vwmulsu_op():
def vwmulu_op():
def vwredsum_op():
def vwredsumu_op():
def vwsub_op():
def vwsubu_op():
def vxor_op():
def vzext_op():
