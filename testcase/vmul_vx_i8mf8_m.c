/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    182, 97, 198, 71, 169, 126, 64, 146, 185, 167, 198, 182, 102, 235, 103, 28
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    6, 245, 70, 186, 136, 139, 96, 197, 7, 254, 29, 68, 176, 172, 9, 8
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int out_data[] = {
    24, 39, 81, 124, 208, 11, 63, 93, 126, 194, 188, 92, 61, 125, 70, 242
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8mf8_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1092, 23765, 13860, 124, 22984, 17514, 6144, 93, 126, 42418, 188, 12376, 61, 125, 927, 242
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