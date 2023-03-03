/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    518789011, 1258977729, 710366561, 58224646, 4027973247, 1321434068, 43331060, 2730251188, 3561704624, 3947973818, 3355146741, 3480933910, 2086153051, 1093963346, 3327779470, 3378714024
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3953294605, 3672130360, 2528413571, 187227612, 4163008492, 114530882, 3583486836, 483750551, 1676091642, 644634374, 3696259830, 1928052740, 2645674929, 2405119868, 2238423247, 1932497400
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    1243944714, 2553984944, 1420071156, 239188773, 995540155, 3439213040, 1205577931, 3302906387, 267121228, 166278251, 1897486804, 3229394212, 2800424507, 1730773914, 1385727636, 2368021600
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4472083616, 4931108089, 1420071156, 245452258, 8190981739, 1435964950, 1205577931, 3214001739, 267121228, 4592608192, 7051406571, 5408986650, 4731827980, 1730773914, 5566202717, 2368021600
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
