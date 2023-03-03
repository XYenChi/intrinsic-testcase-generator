/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2703572152, 4098173528, 1990900961, 1441329931, 4032249330, 2292267536, 3169891566, 1672911229, 379329630, 3487366993, 216833829, 3735116319, 264709901, 266499650, 2754912600, 3606530951
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    392701634, 998382953, 911192899, 867536439, 436387302, 3576883774, 912987037, 1366377171, 2954835472, 3217268854, 2293703559, 3224957784, 195897063, 2590288365, 2606953800, 1036071004
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    const int out_data[] = {
    1723594540, 3104809001, 1042140219, 486207117, 2157559247, 1794047080, 979306775, 3685728274, 19735315, 1463649066, 270723544, 4081632305, 174771009, 1377263181, 4260306674, 2637423383
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1061697203450890908, 4091546591895877185, 1814094819317616158, 1250406236250062826, 1759622408267566907, 8199174556979407944, 2894069909432936717, 2285827716100881433, 1120856646324370675, 11219797210510185088, 497352525559620955, 12045592451186109401, 51855892327691772, 690310944048835431, 7181929875498186674, 3736622145997068187
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
