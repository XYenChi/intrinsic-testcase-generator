"""
Generate execute file by operator
"""
import operator_py_function
import random
import sys
import math

# set VLEN as 64 bit

op = sys.argv[1]
Q_array = 16
ELEN = 64
_vx = ['v', 'x']
_suffix = ['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8',
           '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4',
           '32m1', '32m2', '32m4', '32m8', '32mf2',
           '64m1', '64m2', '64m4', '64m8']
_mask = ['', '_m']
IntegerOpList = ['vadc', 'vadd', 'vand', 'vdiv', 'vdivu', 'vmacc', 'vmadc', 'vmadd', 'vmax', 'vmaxu', 'vmerge', 'vmin',
                 'vminu', 'vmsbc', 'vmseq', 'vmsge', 'vmsgeu', 'vmsgt', 'vmsgtu', 'vmsle', 'vmsleu', 'vmslt', 'vmsltu',
                 'vmsne', 'vmul', 'vmulh', 'vmulhsu', 'vmulhu', 'vmv', 'vneg', 'vnmsac', 'vnmsub', 'vnot', 'vnsra',
                 'vnsrl', 'vor', 'vrem', 'vremu', 'vrsub', 'vsbc', 'vsext', 'vsll', 'vsra', 'vsrl', 'vsub', 'vwadd',
                 'vwaddu', 'vwmacc', 'vwmaccsu', 'vwmaccu', 'vwmaccus', 'vwmul', 'vwmulsu', 'vwmulu', 'vwsub', 'vwsubu',
                 'vxor', 'vzext']

lmul_dict = {'1': 1, '2': 2, '4': 4, '8': 8, 'f2': 0.5, 'f4': 0.25, 'f8': 0.125}


class Node:
    def __init__(self):
        self.op = op
        self.lmul = 0.0
        self.sew = 8
        self.mask = None
        # If _mask = '_m', vm = 0, masked, calculate if mask array[i] = 1
        self.sign = None
        self.dynamic_arrayQuantity_elementRange()
        self.Q_A_E = 64
        self.Range = 1
        self.masked = [0] * self.Q_A_E
        self.data1 = [0] * self.Q_A_E
        self.data2 = [0] * self.Q_A_E
        self.vd_default = [0] * self.Q_A_E
        self.out = [0] * self.Q_A_E
        self.val = None
        self.golden = [0] * self.Q_A_E
        self.random_gen()
        self.compute()

    def dynamic_arrayQuantity_elementRange(self):
        self.Q_A_E = int(128 * self.lmul / self.sew)
        # quantity of array element
        self.Range = pow(2, self.sew)
        self.masked = [0] * self.Q_A_E
        self.data1 = [0] * self.Q_A_E
        self.data2 = [0] * self.Q_A_E
        self.vd_default = [0] * self.Q_A_E
        self.golden = [0] * self.Q_A_E

    def compiler_option_write(self):
        fd.write("/* { dg-do run } */\n")
        fd.write("/* { dg-options \"-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2\" } */\n")

    def c_header_file_write(self):
        fd.write("#include <stdlib.h>\n")
        fd.write("#include <stdio.h>\n")
        fd.write("#include <string.h>\n")
        fd.write("#include \"riscv_vector.h\"\n")

    def c_main_entry_write(self):
        fd.write("int main(){\n")

    def pointer_iterator_write(self):
        fd.write("    for (int n = %d, Q_element = %s;n >= 0; n -= Q_element) {\n" % (a.Q_A_E, a.sew))

    def intrinsic_data_write(self):
        fd.write("data1, data2")

    def intrinsic_ELEN_write(self):
        fd.write("%s" % ELEN)

    def jump_to_next_write_mask(self):
        fd.write("        in1 += Q_element;\n")
        fd.write("        in2 += Q_element;\n")
        fd.write("        out += Q_element;\n")
        fd.write("        mask += Q_element;\n")
        fd.write("      }\n")

    def jump_to_next_write_wo_mask(self):
        fd.write("        in1 += Q_element;\n")
        fd.write("        in2 += Q_element;\n")
        fd.write("        out += Q_element;\n")
        fd.write("      }\n")

    def report_write(self):
        fd.write("    int fail = 0;\n")
        fd.write("    for (int i = 0; i < %d; i++){\n" % self.Q_A_E)
        fd.write("        if (golden[i] != out_data[i]) {\n")
        fd.write("            printf (\"idx=%d golden=%d out=%d\\n\", i, golden[i], out[i]);\n")
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

    def random_gen(self):
        for i in range(self.Q_A_E):
            self.data1[i] = random.randint(0, self.Range)
            self.data2[i] = random.randint(0, self.Range)
            self.vd_default[i] = random.randint(0, self.Range)

    def mask_gen(self):
        for i in range(self.Q_A_E):
            if self.mask:
                # if vm = 1, no matter what v0.mask[i] is equal to, calculate will continue, so do nothing and return.
                self.masked[i] = 1
            else:
                # if vm = 0, only when v0.mask[i] = 1, calculate would continue.
                self.masked[i] = random.randint(0, 1)

    def vs2_data_write(self):
        fd.write("    vint%s_t data1[] = {\n" % suffix)
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.data1)))
        fd.write("    };\n")
        fd.write("    const vint%s_t *in1 = &data1[0];\n" % suffix)

    def vs1_data_write(self):
        fd.write("    vint%s_t data2[] = {\n" % suffix)
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.data2)))
        fd.write("    };\n")
        fd.write("    const vint%s_t *in2 = &data2[0];\n" % suffix)

    def vd_declaration_write(self):
        fd.write("    vint%s_t out_data[%s];\n" % (suffix, ELEN))
        fd.write("    vint%s_t *out = &out_data[0];\n" % suffix)

    def vd_default_write(self):
        fd.write("    vint%s_t out_data[] = {\n" % suffix)
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.vd_default)))
        fd.write("    };\n")
        fd.write("    vint%s_t *out = &out_data[0];\n" % suffix)

    def mask_data_write(self):
        # todo: mask type
        fd.write("    int masked[] = {\n")
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.masked)))
        fd.write("    };\n")
        fd.write("    const int *mask = &masked[0];\n")

    def golden_by_python_write(self):
        fd.write("    vint%s_t golden[] = {\n" % suffix)
        fd.write("    %s\n" % ", ".join(map(lambda x: str(x), self.golden)))
        fd.write("    };\n")

    def specific_operator_c(self):
        if self.op is not None:
            match self.op:
                case 'vadd':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vsub':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vmul':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vdiv':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vmax':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vmin':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vrem':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vadc':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vsbc':
                    fd.write("        vint%s_t out = __riscv_%s_v%s_i%s%s (" % (suffix, op, vx, suffix, mask))
                case 'vmerge':
                    fd.write("        vint%s_t out = __riscv_%s_vv%s_i%s%s (" % (suffix, op, vx, suffix, mask))
        # todo: generate all the operate by default
        # else:
        #    for op in IntegerOpList:
        #        return "    vint%s_t out = __riscv_%s_v%s_i%s (" % (suffix, op, vx, suffix)

    def compute(self):
        op_list = {
            "vadd": operator_py_function.add_op,
            "vand": operator_py_function.and_op,
            "vsub": operator_py_function.sub_op,
            "vmul": operator_py_function.mul_op,
            "vdiv": operator_py_function.div_op,
            "vmax": operator_py_function.max_op,
            "vmin": operator_py_function.min_op,
            "vrem": operator_py_function.reminder,
            "vadc": operator_py_function.add_with_carry_op,
            "vsbc": operator_py_function.sub_with_borrow_op,
            "vmerge": operator_py_function.merge_op
        }
        if self.mask:
            for i in range(self.Q_A_E):
                self.golden[i] = op_list[op](self.data1[i], self.data2[i])
        else:
            if op == 'vmerge':
                for i in range(self.Q_A_E):
                    self.golden[i] = op_list[op](self.data1[i], self.data2[i], self.masked[i])
            else:
                for i in range(self.Q_A_E):
                    self.golden[i] = op_list[op](self.data1[i], self.data2[i], self.vd_default[i], self.masked[i])


a = Node()
a.op = op
for suffix in _suffix:
    divider = suffix.split('m')
    a.sew = int(divider[0])
    a.lmul = lmul_dict["%s" % divider[1]]
    a.dynamic_arrayQuantity_elementRange()
    for vx in _vx:
        for mask in _mask:
            filename = "testcase/%s_v%s_i%s%s.c" % (op, vx, suffix, mask)
            if mask != '_m':
                with open(filename, 'w') as fd:
                    if op == 'vmerge':
                        a.mask = 0
                        # mask and have v0.mask[i] value
                        a.compiler_option_write()
                        a.c_header_file_write()
                        a.c_main_entry_write()
                        a.random_gen()
                        a.vs2_data_write()
                        a.vs1_data_write()
                        a.mask_gen()
                        a.mask_data_write()
                        a.pointer_iterator_write()
                        a.specific_operator_c()
                        a.intrinsic_data_write()
                        fd.write(", mask, ")
                        a.intrinsic_ELEN_write()
                        fd.write(");\n")
                        a.jump_to_next_write_mask()
                        a.compute()
                        a.golden_by_python_write()
                        a.report_write()
                    else:
                        a.mask = 1
                        # don't hava mask
                        a.compiler_option_write()
                        a.c_header_file_write()
                        a.c_main_entry_write()
                        a.random_gen()
                        a.vs2_data_write()
                        a.vs1_data_write()
                        a.vd_declaration_write()
                        a.pointer_iterator_write()
                        a.specific_operator_c()
                        a.intrinsic_data_write()
                        fd.write(", ")
                        a.intrinsic_ELEN_write()
                        fd.write(");\n")
                        a.jump_to_next_write_wo_mask()
                        a.compute()
                        a.golden_by_python_write()
                        a.report_write()
            else:
                if op == 'vmerge':
                    break
                else:
                    with open(filename, 'w') as fd:
                        a.mask = 0
                        # mask and have v0.mask[i] value
                        a.compiler_option_write()
                        a.c_header_file_write()
                        a.c_main_entry_write()
                        a.random_gen()
                        a.vs2_data_write()
                        a.vs1_data_write()
                        a.vd_default_write()
                        # set vd default value if v0.mask[i] = 0, golden = default
                        a.mask_gen()
                        a.mask_data_write()
                        a.pointer_iterator_write()
                        a.specific_operator_c()
                        fd.write(", mask, ")
                        a.intrinsic_data_write()
                        a.intrinsic_ELEN_write()
                        fd.write(");\n")
                        a.jump_to_next_write_mask()
                        a.compute()
                        a.golden_by_python_write()
                        a.report_write()
