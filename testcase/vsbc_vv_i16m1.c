/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    28765, 4287, 27966, 25174, 24328, 64193, 44444, 33440, 41557, 31592, 18339, 26757, 12660, 28561, 59398, 40722
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    5098, 5795, 51873, 14444, 25293, 42026, 12247, 14857, 41986, 14452, 48893, 22430, 7713, 26093, 2831, 65296
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16m1 (data1_v, data2_v, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    23667, -1508, -23907, 10730, -965, 22167, 32197, 18583, -429, 17140, -30554, 4327, 4947, 2468, 56567, -24574
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
