/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    193, 1, 32, 82, 215, 190, 38, 149, 33, 144, 127, 111, 56, 29, 237, 9
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    82, 220, 70, 41, 114, 197, 248, 18, 51, 197, 152, 138, 115, 73, 245, 40
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int out_data[] = {
    160, 227, 93, 102, 114, 121, 113, 182, 184, 95, 143, 143, 58, 45, 142, 221
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8mf8_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    30881, 227, 2976, 8364, 24511, 22991, 4295, 27118, 6072, 13681, 18161, 15873, 3248, 1306, 33654, 1989
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
