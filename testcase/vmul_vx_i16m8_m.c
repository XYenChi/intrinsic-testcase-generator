/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    36342, 49277, 20807, 33736, 54978, 10110, 692, 57719, 2194, 31456, 29847, 51863, 61649, 38005, 63104, 56157
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    60835, 51721, 21481, 56759, 7165, 51954, 52294, 51955, 51438, 28670, 13013, 41362, 34512, 50166, 39985, 50439
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    34622, 9190, 37976, 49044, 41063, 39421, 48153, 3433, 20767, 19254, 8923, 41963, 33090, 31897, 59564, 55088
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    34622, 9190, 37976, 1914821624, 393917370, 39421, 48153, 2998790645, 20767, 901843520, 8923, 41963, 33090, 31897, 59564, 55088
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
