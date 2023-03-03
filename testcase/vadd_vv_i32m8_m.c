/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3427287998, 1043230202, 62423331, 2552316799, 3279610963, 3278718974, 1789115384, 1523714677, 967884944, 1102880772, 3668173343, 59721148, 1670281724, 2363037512, 2279489440, 3768421315
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    904890740, 2220408946, 1071297439, 1908848330, 3615379598, 1500564623, 558938715, 195262290, 1874466725, 1597250350, 4063435509, 3505999428, 4251664351, 495219477, 2257841610, 465787805
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3184770697, 393987347, 14603928, 2067194110, 3971683425, 43669043, 3098672146, 2695745098, 828315971, 3100863452, 1270279157, 3411182513, 495198280, 3839155231, 2606874198, 126195465
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4332178738, 3263639148, 14603928, 2067194110, 3971683425, 43669043, 2348054099, 2695745098, 2842351669, 2700131122, 1270279157, 3565720576, 5921946075, 2858256989, 2606874198, 126195465
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
