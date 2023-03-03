/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2210797810, 378655256, 4185026059, 1257845250, 2723368274, 3108858116, 1803983519, 2368184517, 2959758240, 1693929194, 4273338358, 4265588451, 1619632892, 1069038515, 3672003971, 510837299
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    595252595, 3362121666, 2491956464, 1299463143, 359166233, 3683200486, 1828568623, 3000530387, 145961743, 2597719292, 1068547668, 2496306470, 320167610, 1420995767, 2031843830, 327694087
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    77550379, 1407753622, 2462670366, 3718376472, 2442586376, 458566395, 3852592207, 1218888551, 2155595782, 2947990722, 3269302466, 1162800115, 1889411776, 4051225643, 4154057857, 2428968085
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    595252595, 332879618, 2491956464, 41617893, 2442586376, 458566395, 24585104, 632345870, 2155595782, 903790098, 3269302466, 1162800115, 1889411776, 351957252, 2031843830, 327694087
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
