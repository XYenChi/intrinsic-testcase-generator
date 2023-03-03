/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    951378102, 486928562, 428762518, 850546316, 3515548047, 2988800091, 1063699785, 1398244551, 2986483753, 1292178274, 707167767, 94487261, 589948634, 3628726543, 1261813271, 2227657641
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    239715137, 2483009662, 1329428549, 3053035399, 2328065466, 3995580185, 1320361567, 3952240362, 1702806246, 3564879823, 993845879, 3566279963, 1496966030, 2338249364, 3719827033, 4173595966
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    711662965, -1996081100, -900666031, -2202489083, 1187482581, -1006780094, -256661782, -2553995811, 1283677507, -2272701549, -286678112, -3471792702, -907017396, 1290477179, -2458013762, -1945938325
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
