/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    38239, 23424, 44393, 49046, 27080, 24643, 33923, 58055, 21390, 51619, 31011, 1296, 6219, 40781, 57090, 46307
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    37665, 30561, 541, 48130, 58753, 2933, 58963, 20271, 25778, 45759, 11041, 43179, 19505, 11679, 40988, 20652
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    bool64_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16mf4 (data1_v, data2_v, size_t vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    38239, 30561, 541, 49046, 58753, 24643, 33923, 58055, 25778, 45759, 11041, 43179, 6219, 11679, 40988, 20652
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
