/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1542372910, 469160272, -868971387, 563233089, 1801437038, -718940720, 1591132319, 1246087839, 1528201867, 1303474536, -441312849, 1410081413, 1930314240, -1688924161, -1785011534, 20317008
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -2076535510, -1080253440, 286582584, 2021856290, 1832025838, -1380807797, -147548381, -911506791, 1470890203, 1070937958, -706087898, 1494584066, -2080986276, -237790573, 1049503402, 2041582249
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    -672316457, -1150372249, -1121408108, 320201554, -843607722, 1332701613, 1702339608, 926284712, 1345815818, 76514697, 57637882, -1094551804, 1351282336, -1661659948, 1679845549, -1184940807
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -672316457, -1150372248, -1121408107, 320201554, -843607722, 1332701614, 1702339608, 926284712, 1345815819, 76514697, 57637883, -1094551803, 1351282337, -1661659948, 1679845550, -1184940806
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
