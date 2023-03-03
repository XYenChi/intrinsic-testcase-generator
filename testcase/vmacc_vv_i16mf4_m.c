/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    24714, 64394, 62650, 32652, 12565, 252, 1617, 46913, 37813, 10679, 16038, 21846, 20837, 22678, 30292, 33719
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    27701, 15444, 16272, 14677, 395, 34800, 35237, 44356, 1335, 36179, 58839, 58277, 33056, 47899, 63202, 363
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    23530, 51985, 23353, 12718, 17011, 46891, 22691, 20472, 36718, 13941, 44640, 59207, 25139, 26789, 1685, 1525
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    581520420, 3347522090, 1463065450, 415268137, 213743215, 11816532, 36691347, 960402937, 1388417735, 148875939, 715936321, 1293436123, 523821343, 607520943, 51042020, 51421475
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
