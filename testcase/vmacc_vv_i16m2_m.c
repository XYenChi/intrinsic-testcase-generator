/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    7334, 21501, 55885, 62265, 25358, 5391, 3056, 20664, 58091, 59649, 32180, 37576, 11859, 18907, 32138, 58878
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    19918, 20383, 2315, 52472, 53200, 54541, 39316, 50551, 25377, 14886, 39813, 4134, 16971, 52436, 32318, 28327
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    32463, 40250, 50010, 38841, 5698, 25335, 52655, 19701, 8431, 13477, 48015, 33985, 47201, 8116, 65347, 32972
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    238083643, 865415250, 2794808850, 2418434865, 144489885, 136580985, 160913681, 407101465, 489765221, 803889574, 1545122701, 1277020361, 559756659, 153449213, 2100121886, 1941325416
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
