/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -16028, 1909, -27258, 30236, -6942, 22637, 19417, 25042, 7523, -17449, -9357, 4387, 10186, -23676, -15675, 14735
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -4151, 10829, 29665, -8316, -25006, 9877, 11806, -4775, 1978, -11224, -18052, 31432, 10206, 7466, -31949, 24572
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int out_data[] = {
    14171, -12491, 26973, -18015, -10806, 25759, -5437, 21437, 32504, -23370, -31805, 8775, 7849, -5333, 13999, -17523
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (bool16_t mask, int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    14172, -12491, 26974, -18014, -10805, 25760, -5437, 21437, 32504, -23370, -31804, 8775, 7849, -5333, 13999, -17523
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
