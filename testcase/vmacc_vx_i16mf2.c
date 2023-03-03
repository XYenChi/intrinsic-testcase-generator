/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29442, 35175, 31594, 28578, 61767, 62855, 16069, 58817, 29335, 4819, 37280, 43579, 54206, 43887, 43012, 26687
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    59515, 35605, 24003, 38090, 4214, 536, 62010, 50928, 41978, 12429, 39033, 51857, 46036, 13096, 12350, 26451
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    const int out_data[] = {
    62809, 50480, 32987, 17940, 14539, 29295, 36054, 41374, 39696, 62870, 49319, 45023, 36598, 64190, 59848, 20366
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16mf2 (data1_v, data2_v, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1752303439, 1252456355, 758383769, 1088553960, 260300677, 33719575, 996474744, 2995473550, 1231464326, 59958221, 1455199559, 2259921226, 2495464014, 574808342, 531258048, 705918203
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
