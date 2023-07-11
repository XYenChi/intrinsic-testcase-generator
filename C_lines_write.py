def compiler_option_write(fd):
    fd.write("/* { dg-do run } */\n")
    fd.write(
        "/* { dg-options \"-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w\" } */\n")


def c_header_file_write(fd):
    fd.write("#include <stdlib.h>\n")
    fd.write("#include <stdio.h>\n")
    fd.write("#include <string.h>\n")
    fd.write("#include \"riscv_vector.h\"\n")


def csr_write(fd):
    fd.write("enum __RISCV_VXRM {\n__RISCV_VXRM_RNU = 0,\n__RISCV_VXRM_RNE = 1,\n__RISCV_VXRM_RDN = 2,"
             "\n__RISCV_VXRM_ROD = 3,\n};\n")


def vl_set_write(fd, suffix):
    fd.write("    size_t avl = 64;\n")
    fd.write("    size_t vl = __riscv_vsetvl_e%s(avl);\n" % suffix)


def c_main_entry_write(fd):
    fd.write("int main(){\n")


def pointer_iterator_write(fd):
    fd.write("    for (size_t n = 0; n < vl; n++) {\n")


def vs2_load(fd, a, suffix, mask):
    if mask == 0:
        fd.write(f"    v%s%s_t data1_v = __riscv_vle%s_v_%s%s%s (mask, in1, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix, mask))
    else:
        fd.write("    v%s%s_t data1_v = __riscv_vle%s_v_%s%s (in1, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix))


def unsign_vs1_load(fd, a, suffix, mask):
    if mask == 0:
        fd.write("    vuint%s_t data2_v = __riscv_vle%s_v_%s%s%s (mask, in2, vl);\n"
                 % (suffix, str(a.SEW), a.sign, suffix, mask))
    else:
        fd.write("    vuint%s_t data2_v = __riscv_vle%s_v_%s%s (in2, vl);\n"
                 % (suffix, str(a.SEW), a.sign, suffix))


def vs1_load(fd, a, suffix, mask):
    if mask == 0:
        fd.write("    v%s%s_t data2_v = __riscv_vle%s_v_%s%s%s (mask, in2, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix, mask))
    else:
        fd.write("    v%s%s_t data2_v = __riscv_vle%s_v_%s%s (in2, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix))


def ext_vd_load(fd, a, ext_suffix, mask):
    if mask == 0:
        fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s%s (mask, out, vl);\n"
                 % (a.vtype, ext_suffix, a.ext_sew, a.sign, ext_suffix, mask))
    else:
        fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s (out, vl);\n"
                 % (a.vtype, ext_suffix, a.ext_sew, a.sign, ext_suffix))


def vd_load(fd, a, suffix, mask):
    if mask == 0:
        fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s%s (mask, out, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix, mask))
    else:
        fd.write("    v%s%s_t out_v = __riscv_vle%s_v_%s%s (out, vl);\n"
                 % (a.vtype, suffix, str(a.SEW), a.sign, suffix))


# def mask_load(a):
# todo: load mask
def vd_store(fd, a, suffix, iu, mask):
    if mask == 0:
        fd.write("        void __riscv_vse%s_v_%s%s (bool%s_t mask, %s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                 % (str(a.SEW), iu, suffix, str(a.SEW), a.vtype, str(a.SEW), a.vtype, suffix))
    else:
        fd.write("        void __riscv_vse%s_v_%s%s (%s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                 % (str(a.SEW), iu, suffix, a.vtype, str(a.SEW), a.vtype, suffix))


def ext_vd_store(fd, a, ext_suffix, bool_width, iu, mask):
    if mask == 0:
        fd.write("        void __riscv_vse%s_v_%s%s (bool%s_t mask, %s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                 % (a.ext_sew, iu, ext_suffix, bool_width, a.vtype, a.ext_sew, a.vtype, ext_suffix))
    else:
        fd.write("        void __riscv_vse%s_v_%s%s (%s%s_t *out, v%s%s_t out_v, size_t vl);\n"
                 % (a.ext_sew, iu, ext_suffix, a.vtype, a.ext_sew, a.vtype, ext_suffix))


def parameter_seq_write(fd, a, vx, suffix, iu):
    library_name = 'one_time_c_template_lib.txt'
    merger = f"{iu+suffix}"
    with open(library_name) as f:
        for line in f:
            if str(a.OP) in line:
                if str(a.sign) in line:
                    if vx in line:
                        if merger in line:
                            if a.mask == 1 & ("_m" not in line):
                                fd.write(f"\t\t{line}")
                            elif a.mask == 0 & ("_m" in line):
                                fd.write(f"\t\t{line}")
                            else:
                                continue
                        else:
                            continue
                    else:
                        continue
                else:
                    continue
            else:
                print("can't find line, please check collector.py")


def jump_to_next_write_mask(fd, a, op):
    fd.write("        in1 += %s;\n" % int(a.SEW / 8))
    if op == 'vnot':
        return
    else:
        fd.write("        in2 += %s;\n" % int(a.SEW / 8))
    fd.write("        out += %s;\n" % int(a.SEW / 8))
    fd.write("        mask += %s;\n" % int(a.SEW / 8))
    fd.write("      }\n")


def jump_to_next_write_wo_mask(fd, a, op):
    fd.write("        in1 += %s;\n" % int(a.SEW / 8))
    if op == 'vmv' or op == 'vneg':
        return
    else:
        fd.write("        in2 += %s;\n" % int(a.SEW / 8))
    fd.write("        out += %s;\n" % int(a.SEW / 8))
    fd.write("      }\n")


def report_write(fd, q_array):
    fd.write("    int fail = 0;\n")
    fd.write("    for (int i = 0; i < %d; i++){\n" % q_array)
    fd.write("        if (golden[i] != out_data[i]) {\n")
    fd.write("            printf (\"idx=%d golden=%d out=%d\\n\", i, golden[i], out_data[i]);\n")
    fd.write("            fail++;\n")
    fd.write("            }\n")
    fd.write("        }\n")
    fd.write("    if (fail) {\n")
    # fd.write("    printf(\"FAIL\\n\");\n")
    fd.write("        return 1;\n")
    fd.write("    } else {\n")
    # fd.write("    printf(\"PASS\\n\");\n")
    fd.write("        return 0;\n")
    fd.write("    }\n")
    fd.write("}\n")


def vs2_data_write(fd, a):
    fd.write("    const %s%s_t data1[] = {\n" % (a.vtype, str(a.SEW)))
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.data1)))
    fd.write("    };\n")
    fd.write("    const %s%s_t *in1 = &data1[0];\n" % (a.vtype, str(a.SEW)))


def vs1_data_write(fd, a):
    fd.write("    const %s%s_t data2[] = {\n" % (a.vtype, str(a.SEW)))
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.data2)))
    fd.write("    };\n")
    fd.write("    const %s%s_t *in2 = &data2[0];\n" % (a.vtype, str(a.SEW)))


def unsign_vs1_data_write(fd, a):
    fd.write("    const uint%s_t data2[] = {\n" % str(a.SEW))
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.data2)))
    fd.write("    };\n")
    fd.write("    const uint%s_t *in2 = &data2[0];\n" % str(a.SEW))


def vd_declaration_write(fd, a, q_array):
    fd.write("    const %s%s_t out_data[%s];\n" % (a.vtype, str(a.SEW), q_array))
    # Declare the array of 10 elements
    fd.write("    const %s%s_t *out = &out_data[0];\n" % (a.vtype, str(a.SEW)))


def ext_vd_declaration_write(fd, a, q_array):
    fd.write("    const %s%s_t out_data[%s];\n" % (a.vtype, a.ext_sew, q_array))
    # Declare the array of 10 elements
    fd.write("    const %s%s_t *out = &out_data[0];\n" % (a.vtype, a.ext_sew))


def vd_default_write(fd, a):
    fd.write("    const %s out_data[] = {\n" % a.vtype)
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.vd_default)))
    fd.write("    };\n")
    fd.write("    const %s%s_t *out = &out_data[0];\n" % (a.vtype, str(a.SEW)))


def widen_vd_default_write(fd, a):
    fd.write("    const %s out_data[] = {\n" % a.vtype)
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.vd_default)))
    fd.write("    };\n")
    fd.write("    const %s%s_t *out = &out_data[0];\n" % (a.vtype, a.ext_sew))


def vd_mask_default_write(fd, a, q_array):
    # todo: load vd mask
    fd.write("    const bool%s_t vd_mask_data[%s];\n" % (str(a.SEW), q_array))
    fd.write("    const bool%s_t *vd_mask = &vd_mask_data[0];\n" % str(a.SEW))


def mask_data_write(fd, a):
    # todo: mask type
    fd.write("    uint%s_t masked[] = {\n" % int(a.SEW / a.LMUL))
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.masked)))
    fd.write("    };\n")
    fd.write("    const uint%s_t *mask = &masked[0];\n" % int(a.SEW / a.LMUL))


def golden_by_python_write(fd, a):
    fd.write("    %s%s_t golden[] = {\n" % (a.vtype, str(a.SEW)))
    fd.write("    %s\n" % ", ".join(map(lambda x: str(x), a.golden)))
    fd.write("    };\n")
