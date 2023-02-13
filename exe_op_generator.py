"""
Generate execute file by operator
"""
import random
import sys

op = sys.argv[1]
vl = 64
filename = 'v'+'self.sign'+'self.sew'+'self.lmul'+'_'+'op'+'.c'
IntegerOpList = ['vadc', 'vadd', 'vand', 'vdiv', 'vdivu', 'vmacc', 'vmadc', 'vmadd', 'vmax', 'vmaxu', 'vmerge', 'vmin',
                 'vminu', 'vmsbc', 'vmseq', 'vmsge', 'vmsgeu', 'vmsgt', 'vmsgtu', 'vmsle', 'vmsleu', 'vmslt', 'vmsltu',
                 'vmsne', 'vmul', 'vmulh', 'vmulhsu', 'vmulhu', 'vmv', 'vneg', 'vnmsac', 'vnmsub', 'vnot', 'vnsra',
                 'vnsrl', 'vor', 'vrem', 'vremu', 'vrsub', 'vsbc', 'vsext', 'vsll', 'vsra', 'vsrl', 'vsub', 'vwadd',
                 'vwaddu', 'vwmacc', 'vwmaccsu', 'vwmaccu', 'vwmaccus', 'vwmul', 'vwmulsu', 'vwmulu', 'vwsub', 'vwsubu',
                 'vxor', 'vzext']

def add_op(a, b):
    return a + b
class Node:
    def __init__(self):
        self.lmul = ['1', '2', '4', '8', 'f2', 'f4', 'f8']
        self.sew = ['8', '16', '32', '64']
        self.suffix = ['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8',
                   '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4',
                   '32m1', '32m2', '32m4', '32m8', '32mf2',
                   '64m1', '64m2', '64m4', '64m8',]
        self.mask = None
        self.sign = None
        self.data1 = [0] * vl
        self.data2 = [0] * vl
        self.out = []
        self.val = None
        self.golden = [0] * vl
        self.v_or_x = ['v', 'x']
        self.random_gen()
        self.compute()
    def random_gen(self):
        for i in range(vl):
            self.data1[i] = random.randint(0, 0xff)
            self.data2[i] = random.randint(0, 0xff)

    def C_write(self, fd):
        def specific_operator_C():
            if op != None:
                match op:
                    case vadd:
                        return "    vint%s_t out = __riscv_%s_v%s_i%s (data1, data2);\n" % (self.suffix[0], op, self.v_or_x[0], self.suffix[0])
                    # case vadc:
                    #    ;
        fd.write ("/* { dg-do run } */\n")
        fd.write ("/* { dg-options \"-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2\" } */\n")
        fd.write ("#include <stdlib.h>\n")
        fd.write ("#include <stdio.h>\n")
        fd.write ("#include <string.h>\n")
        fd.write ("#include <riscv_vector.h>\n")
        fd.write ("int main(){\n")
        fd.write("    int data1[] = {\n")
        fd.write("  %s\n" % ", ".join(map(lambda x:str(x), self.data1)))
        fd.write("  };\n")
        fd.write("  const int *in1 = &data1[0];\n")
        fd.write("    int data2[] = {\n")
        fd.write ("  %s\n" % ", ".join(map(lambda x:str(x), self.data2)))
        fd.write ("  const int *in2 = &data2[0];\n")
        fd.write ("  int out_data[%d];\n" % (vl))
        fd.write ("  int *out = &out_data[0];\n" )
        fd.write ("  for (int n = %d, Q_element = 4;n >= 0; n -= Q_element) {\n" % vl)

        fd.write(specific_operator_C())
        fd.write ("    in1 += Q_element;\n" )
        fd.write ("    out += Q_element;\n" )
        fd.write ("  }\n")
        fd.write ("  int golden[] = {\n")
        fd.write ("  %s\n" % ", ".join(map(lambda x:str(x), self.golden)))
        fd.write ("  };\n")
        fd.write ("  int fail = 0;\n")
        fd.write ("  for (int i = 0; i < %d; ++i)\n" % (vl))
        fd.write ("     if (golden0[i] != out0_data[i]) {\n")
        fd.write ("       printf (\"idx=%d golden=%d out=%d\\n\", i, golden0[i], out0[i]);\n")
        fd.write ("       fail++;\n")
        fd.write ("     }\n")
        fd.write ("  if (fail) {\n")
        fd.write ("    printf(\"FAIL\\n\");\n")
        fd.write ("    return 1;\n")
        fd.write ("  } else {\n")
        fd.write ("    printf(\"PASS\\n\");\n")
        fd.write ("    return 0;\n")
        fd.write ("  }\n")
        fd.write ("}\n")

    def compute(self):
        op_list = {
            "vadd": add_op
        }
        for i in range(vl):
            self.golden[i] = op_list[op](self.data1[i], self.data2[i])
a=Node()
with open(filename, 'w') as fd:
    a.C_write(fd)



