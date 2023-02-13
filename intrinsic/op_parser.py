#!/usr/bin/env python3

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/04_vector_integer_arithmetic_functions.md') as f:
    integer_op_lists = set()
    for line in f:
        if '__riscv_' not in line:
            continue
        op1 = line.split('__riscv_')
        op2 = op1[1].split('_')
        integer_op_lists.add(op2[0])
    print(sorted(integer_op_lists))

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/05_vector_fixed-point_arithmetic_functions.md') as f:
    fixed_point_op_lists = set()                                                                                                                           
    for line in f:                                                                                                                                     
        if '__riscv_' not in line:                                                                                                                     
            continue                                                                                                                                   
        op1 = line.split('__riscv_')                                                                                                                   
        op2 = op1[1].split('_')                                                                                                                        
        fixed_point_op_lists.add(op2[0])
    print(sorted(fixed_point_op_lists))

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/06_vector_floating-point_functions.md') as f:
    floating_point_op_lists = set()                                                                                                                            
    for line in f:                                                                                                                                          
        if '__riscv_' not in line:                                                                                                                          
            continue                                                                                                                                        
        op1 = line.split('__riscv_')                                                                                                                        
        op2 = op1[1].split('_')                                                                                                                             
        floating_point_op_lists.add(op2[0])                                                                                                                    
    print(sorted(floating_point_op_lists))

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/07_vector_reduction_functions.md') as f: 
    reduction_op_lists = set()                                                                                                                 
    for line in f:                                                                                                                                  
        if '__riscv_' not in line:                                                                                                                  
            continue                                                                                                                                
        op1 = line.split('__riscv_')                                                                                                                
        op2 = op1[1].split('_')                                                                                                                     
        reduction_op_lists.add(op2[0])                                                                                                         
    print(sorted(reduction_op_lists))

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/08_vector_mask_functions.md') as f:
    mask_op_lists = set()                                                                                                                
    for line in f:                                                                                                                            
        if '__riscv_' not in line:                                                                                                            
            continue                                                                                                                          
        op1 = line.split('__riscv_')                                                                                                          
        op2 = op1[1].split('_')                                                                                                               
        mask_op_lists.add(op2[0])                                                                                                        
    print(sorted(mask_op_lists))

with open('/home/xyenchi/projects/gnu-gcc-team/RVV intrinsic test generator/intrinsic/intrinsic_funcs/09_vector_permutation_functions.md') as f:
    permutation_op_lists = set()                                                                                                                
    for line in f:                                                                                                                       
        if '__riscv_' not in line:                                                                                                       
            continue                                                                                                                     
        op1 = line.split('__riscv_')                                                                                                     
        op2 = op1[1].split('_')                                                                                                          
        permutation_op_lists.add(op2[0])                                                                                                        
    print(sorted(permutation_op_lists))
