#!/usr/bin/env python3

import random
import sys
import os

STORE = -1
LOAD = 0
ADD = 1
SUB = 2

UID = 0


filename = "autogen.c"
dot_filename = os.path.basename(filename) + ".dot"

if (len(sys.argv) > 1):
    filename = sys.argv[1]
    dot_filename =filename+'.dot'

def op2str(op):
    xdict = {
        STORE : 'store',
        LOAD : 'load',
        ADD : 'ADD',
        SUB : 'SUB',
    }
    return xdict[op]

input_content = dict()

load_nodes = []
def func(node):
    global load_nodes
    if node.node_type == LOAD:
        load_nodes.append(node)
        input_content[node.uid] = []

#root.apply(func)

class Node:
    def __init__(self, node_type):
        self.input_ops = []
        self.output_user = []
        self.node_type = node_type
        global UID
        self.uid = UID
        UID += 1
        self.visted = False
        self.val = None
        random_mask = random.randint(0, 1)
        if random_mask:
            self.mask = random.randint(0, 1)
        else:
            return
        random_immediate = random.randint(0, 1)
        if random_immediate:
            self.immediate_bit = None
            self.immediate_sign = None
            self.immediate = random_randint(0, 4095)  # set 12 bit immediate as default
        else:
            return

    def random_gen(self):
        global load_nodes
        if self.node_type == LOAD:
            load_nodes.append(self)
            input_content[self.uid] = []

        global UID
        if self.node_type == LOAD:
            return

        num_op = 2
        if self.node_type == STORE:
            num_op = 1
        for i in range(num_op):
            if UID > 5:
                node_type = LOAD
            else:
                node_type = random.randint(0,2)
                while UID < 3 and node_type == LOAD:
                    node_type = random.randint(0,2)

            if node_type == LOAD:
                # 50% to reuse exist load node.
                if len (load_nodes) == 0 or (random.randint(0,1)):
                    node = Node(node_type)
                else:
                    node = random.choice(load_nodes)
                    self.input_ops.append(node)
                    continue
            else:
                node = Node(node_type)
            self.input_ops.append(node)
            node.output_user.append(self)
            node.random_gen()

    def gen_code(self, fd):
        if self.visted:
            return
        for input_op in self.input_ops:
            input_op.gen_code(fd)

        if self.node_type == ADD:
            fd.write ("    vint32m1_t t%d = vadd_vv_i32m1 (t%d, t%d);\n" %
                   (self.uid, self.input_ops[0].uid, self.input_ops[1].uid));
        elif self.node_type == SUB:
            fd.write ("    vint32m1_t t%d = vsub_vv_i32m1 (t%d, t%d);\n" %
                   (self.uid, self.input_ops[0].uid, self.input_ops[1].uid));
        elif self.node_type == STORE:
            fd.write ("    vstore_i32m1 (out%d, t%d);\n" %
                   (self.uid, self.input_ops[0].uid));
        elif self.node_type == LOAD:
            fd.write ("    vint32m1_t t%d = vload_i32m1 (in%d);\n" %
                   (self.uid, self.uid));
        else:
            assert False
        self.visted = True

    def reset_visted(self):
        self.visted = False
        for op in self.input_ops:
            op.reset_visted()

    def _output_dot_node(self, fd):
        if self.visted:
            return
        fd.write("t%d [label=\"%s\"];\n" % (self.uid, op2str(self.node_type)))
        for op in self.input_ops:
            op._output_dot_node(fd)
            fd.write("t%d -> t%d;\n" %(op.uid, self.uid))

    def output_dot(self, file_name):
        self.reset_visted()
        with open(file_name, "w") as fd:
            fd.write ("digraph {\n")
            # Prologure for dot
            self._output_dot_node(fd)
            # Epilogue for dot
            fd.write ("}\n")

    def apply(self, func):
        func (self)
        self.visted = True
        for op in self.input_ops:
            op.apply(func)

    def compute(self):
        if self.visted:
            return

        self.visted = True

        for op in self.input_ops:
            op.compute()

        try:
            if self.node_type == ADD:
                self.val = self.input_ops[0].val + self.input_ops[1].val
            elif self.node_type == SUB:
                self.val = self.input_ops[0].val - self.input_ops[1].val
            elif self.node_type == STORE:
                self.val = self.input_ops[0].val
        except:
            if self.node_type in [ADD, SUB]:
                print (self.input_ops)
                self.input_ops[0].debug()
                self.input_ops[1].debug()
            elif self.node_type == STORE:
                self.input_ops[0].debug()

    def debug(self):
        print ("UID = %d" %self.uid)
        print ("VAL = %s" %self.val)
        print ("TYPE = %s" %self.node_type)


root = Node(STORE)
root.random_gen()

# Compute how many load node
output_content = dict()
store_nodes = []

def func(node):
    global store_nodes
    if node.node_type == STORE:
        store_nodes.append(node)
        output_content[node.uid] = []

root.apply(func)

NUM_DATAS = 63

# Gen random inputs and compute output
for i in range(NUM_DATAS):
    for load in load_nodes:
        load.val = random.randint(0, 0xff)
        input_content[load.uid].append(load.val)

    root.reset_visted()
    root.compute()

    for store in store_nodes:
        output_content[store.uid].append(store.val)
fd = open(filename, "w")
fd.write ("#include <stdlib.h>\n")
fd.write ("#include <stdio.h>\n")
fd.write ("#include <string.h>\n")
fd.write ("#include <riscv_vector.h>\n")
fd.write ("int main(){\n")

for load in load_nodes:
    fd.write ("  const int in%d_data[] = {\n" % load.uid);
    fd.write ("  %s\n" % ", ".join(map(lambda x:str(x), input_content[load.uid])))
    fd.write ("  };\n");
    fd.write ("  const int *in%d = &in%d_data[0];\n" % (load.uid, load.uid));

for store in store_nodes:
    fd.write ("  int out%d_data[%d];\n" % (store.uid, NUM_DATAS));
    fd.write ("  int *out%d = &out%d_data[0];\n" % (store.uid, store.uid));

fd.write ("  for (int n = %d, vl = 0; vl = vsetvl_32m1(n); n -= vl) {\n" % NUM_DATAS);

root.reset_visted()
root.gen_code(fd)

for load in load_nodes:
    fd.write ("    in%d += vl;\n" % load.uid);

for store in store_nodes:
    fd.write ("    out%d += vl;\n" % store.uid);

fd.write ("  }\n")

for store in store_nodes:
    fd.write ("  int golden%d[] = {\n" % store.uid);
    fd.write ("  %s\n" % ", ".join(map(lambda x:str(x), output_content[store.uid])))
    fd.write ("  };\n");

for store in store_nodes:
    fd.write ("  int fail = 0;\n");
    fd.write ("  for (int i = 0; i < %d; ++i)\n" % (NUM_DATAS));
    fd.write ("     if (golden0[i] != out0_data[i]) {\n")
    fd.write ("       printf (\"idx=%d golden=%d out=%d\\n\", i, golden0[i], out0[i]);\n")
    fd.write ("       fail++;\n");
    fd.write ("     }\n");

fd.write ("  if (fail) {\n")
fd.write ("    printf(\"FAIL\\n\");\n")
fd.write ("    return 1;\n")
fd.write ("  } else {\n")
fd.write ("    printf(\"PASS\\n\");\n")
fd.write ("    return 0;\n")
fd.write ("  }\n")
fd.write ("}\n")

root.output_dot(dot_filename)
