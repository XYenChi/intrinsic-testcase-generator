/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    39437, 33881, 58043, 35967, 18264, 23034, 3239, 60059, 10123, 58689, 26627, 36906, 22570, 45799, 53725, 55757
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    39129, 57118, 17132, 23721, 46621, 5687, 52385, 60601, 17352, 64350, 51191, 26064, 56317, 54949, 11116, 3470
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    55551, 36673, 55274, 55226, 47649, 41111, 55970, 22078, 7783, 36494, 24215, 64837, 62409, 50302, 4028, 49894
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    55551, 90999, 75175, 59688, 47649, 28721, 55624, 22078, 27475, 36494, 77818, 64837, 62409, 100748, 64841, 59227
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
