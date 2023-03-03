/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    70, 193, 85, 82, 78, 122, 35, 67, 210, 40, 227, 250, 232, 94, 196, 41
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    158, 82, 47, 132, 242, 174, 235, 71, 127, 185, 45, 143, 40, 31, 80, 25
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    225, 211, 111, 28, 141, 200, 54, 12, 33, 219, 126, 222, 121, 112, 77, 201
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8m4_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    15750, 40724, 9436, 2297, 10998, 24400, 1890, 805, 6930, 8760, 28603, 55500, 28072, 10529, 15092, 8242
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
