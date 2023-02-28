### Introdution   
#### Step1: Generate array randomly
##### Declare type int with SEW width array  that contain 10 elements:   
vs2 : in_data1   
vs1 : in_data2   
vd : out_data (operator with mask)   
mask (operator with mask)
   
##### Declare pointer to the first array element
in1 -> in_data1   
in2 -> in_data2   
out -> out_data   

#### Step2: Load the to vector   
vle():   
data1_v <- in1   
data2_v <- in2   

#### Step3: Calculate vl with vsetvl and SEW
avl = 1024   
for SEW = 32, LMUL = 1:   
vl = vsetvl_e32m1(avl)  

#### Step4: initiate n = 0, loop with pointer+=sew/8, util n = vl
pass the pointer to vector operator   
pointer move to the next element   

#### Step5: store result to array for comparing
vse():   
out -> out_data
   
### nouns
#### SEW
standard element width  
1. the data passed to golden calculate function will be verified or not
2. 
8:   
range:   
signed:   
16   
32   
64   
#### LMUL   
length multipler, regard as how many element would be used.   
1   
2   
4   
8   
f2 = 1/2   
f4 = 1/4   
f8 = 1/8   
