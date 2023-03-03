/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    64, 212, 82, 207, 181, 22, 102, 115, 205, 66, 75, 201, 162, 110, 143, 104
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    76, 168, 52, 23, 49, 140, 127, 48, 249, 69, 36, 133, 57, 206, 156, 89
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    176, 173, 16, 11, 226, 7, 2, 244, 34, 99, 86, 174, 34, 216, 144, 115
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8mf4_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    11265, 36676, 1313, 2278, 40906, 154, 205, 28060, 6970, 6534, 6450, 34974, 5508, 23760, 20592, 11960
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
