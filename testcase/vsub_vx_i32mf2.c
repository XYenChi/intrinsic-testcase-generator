/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    784026404, 427722351, 2359184414, 276536505, 2549572775, 1998918319, 2083886949, 3897440217, 736079558, 3127808171, 99379837, 1371665305, 2302530828, 3871415910, 3816882084, 1818669740
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4161074423, 1624851235, 1173467752, 107711305, 2686986407, 2664591283, 2253934096, 2308611849, 2762257820, 818131197, 2012093989, 255878438, 4088625112, 3264274747, 196600155, 3717428141
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -3377048019, -1197128884, 1185716662, 168825200, -137413632, -665672964, -170047147, 1588828368, -2026178262, 2309676974, -1912714152, 1115786867, -1786094284, 607141163, 3620281929, -1898758401
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
