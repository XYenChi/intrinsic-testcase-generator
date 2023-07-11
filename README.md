### Introdution   
Test case generator   
1. to generate executable C program.
2. to test Riscv V extension intrinsic function  
3. execute with gcc and action will be same with LLVM as expected.
### Program brief
#### Step1: Generate array randomly
##### Declare type int with SEW width array  that contain 10 elements:   
vs2 : in_data1   
vs1 : in_data2   
vd : out_data    
   
Although this generator contain mask related instruction, don't have method to load vbool type.   
Means that test cases that have masked data couldn't be used.
   
##### Declare pointer to the first array element
in1 -> in_data1   
in2 -> in_data2   
out -> out_data   

#### Step2: Load the to vector   
vle():   
data1_v <- in1   
data2_v <- in2   
out_v <- out   

#### Step3: Calculate vl with vsetvl and SEW
avl = 64   
for SEW = 32, LMUL = 1:   
vl = vsetvl_e32m1(avl)  

#### Step4: initiate n = 0, loop with pointer+=sew/8, util n = vl
pass the pointer to vector operator   
pointer move to the next element   

#### Step5: store result to array for comparing
vse():   
out -> out_data   
#### Step6: compare out_data with result calculate by python   
out_data == golden
   
### Golden data calculate   
vs2 means vs2   
vs1 means vs1   
vd means vd_default
sew means sew
xrm means vxrm
m means mask

### How to use
The generator have not been finished, but the brain storge of author have been used up.
Let me note the file usage.
#### collector.py :    
`python3 collector.py {intrinsic function file serial number}`   
For example, if you want to parse the [05_vector_integer_arithmetic_functions.md](rvv-intrinsic-doc%2Fauto-generated%2Fintrinsic_funcs%2F05_vector_integer_arithmetic_functions.md) ,just `python3 collector.py 05`   
the script parse all the intrinsic functions in the file and sort out them by factors that need to iterate, then save them in [intrinsic_function_type_1.py](intrinsic_function_type_1.py).
Now here are only 05~07 files can be parsed and sorted.   
#### CSRs_random_generator.py :
This file deal with the fix-point instruction that need CSR and rounding. Now need to write C program to read and write.   
#### exe_op_generator.py:
The main program to generate testcases.   
`python3 exe_op_generator.py {what instruction}`    
like `vadd`. Iterate all the situation could be used. I really hope that I could optimize this program to generate randomly eventually.   
#### spike_header_file_transformer.py:   
Collect all the spike head file that start with "v". Generally it is one-time.
#### transformed_op_function.py:   
Product of spike_header_file_transformer.py. Maintained manually to take the place of operator_py_function.py.   
#### operator_py_function.py:
Functions called by exe_op_generator.py to calculate golden data.   

### nouns
#### SEW
standard element width    
#### LMUL   
length multipler, regard as how many element would be used.   
1   
2   
4   
8   
f2 = 1/2   
f4 = 1/4   
f8 = 1/8   
