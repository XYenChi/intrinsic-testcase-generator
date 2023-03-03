/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58126, 23090, 31379, 63612, 19190, 61122, 31962, 46315, 36843, 50838, 43171, 4728, 6034, 22988, 31961, 59546
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    46662, 41537, 26293, 56588, 10003, 25997, 10477, 53544, 45592, 5716, 14072, 43200, 19945, 14493, 35043, 22092
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    9856, 61613, 44815, 35076, 27427, 49259, 26867, 820, 51087, 10667, 61623, 8473, 18995, 56532, 43584, 47232
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9856, 61613, 44815, 35076, 9187, 49259, 26867, -7229, -8749, 10667, 29099, -38472, -13911, 8495, -3082, 47232
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
