/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    16669, 55669, 16261, 42443, 57087, 56403, 60027, 54376, 28083, 45972, 53875, 30112, 52173, 22792, 41798, 61595
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    1806, 21947, 33150, 54729, 51278, 4330, 65058, 52532, 10759, 32010, 28052, 13262, 13958, 39024, 1427, 7380
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m2 (data1_v, data2_v, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    18475, 77616, 49411, 97172, 108365, 60733, 125085, 106908, 38842, 77982, 81927, 43374, 66131, 61816, 43225, 68975
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
