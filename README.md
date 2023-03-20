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
a means vs2   
b means vs1   
c means vd_default   
m means mask

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
