/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    212, 205, 189, 251, 237, 193, 33, 172, 224, 33, 103, 101, 82, 173, 93, 198
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    161, 178, 124, 65, 54, 189, 167, 190, 188, 184, 253, 226, 195, 169, 76, 235
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (*out, vl);
    const int out_data[] = {
    110, 243, 29, 145, 255, 103, 174, 139, 102, 253, 57, 42, 203, 216, 49, 4
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8m8 (data1_v, data2_v, vl);
        void vint8m8_t __riscv_vse8_v_i8 (int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    34242, 36733, 23465, 16460, 13053, 36580, 5685, 32819, 42214, 6325, 26116, 22868, 16193, 29453, 7117, 46534
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
