/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    64, 205, 99, 9, 45, 79, 18, 158, 62, 97, 80, 92, 248, 221, 72, 138
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    206, 190, 236, 198, 223, 226, 235, 148, 68, 115, 131, 166, 27, 214, 45, 217
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (*in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (*in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8mf4 (data1_v, data2_v, vl);
        void vint8mf4_t __riscv_vse8_v_i8 (int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    13184, 38950, 23364, 1782, 10035, 17854, 4230, 23384, 4216, 11155, 10480, 15272, 6696, 47294, 3240, 29946
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
