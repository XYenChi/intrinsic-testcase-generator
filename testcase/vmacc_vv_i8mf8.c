/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    75, 209, 229, 91, 213, 107, 136, 2, 238, 181, 167, 198, 242, 179, 93, 185
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    214, 111, 61, 173, 246, 217, 13, 119, 5, 9, 13, 3, 235, 201, 247, 179
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (*in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (*in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (*out, vl);
    const int out_data[] = {
    189, 165, 216, 115, 157, 223, 187, 107, 227, 109, 44, 191, 112, 58, 173, 198
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8mf8 (data1_v, data2_v, vl);
        void vint8mf8_t __riscv_vse8_v_i8 (int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    16239, 23364, 14185, 15858, 52555, 23442, 1955, 345, 1417, 1738, 2215, 785, 56982, 36037, 23144, 33313
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
