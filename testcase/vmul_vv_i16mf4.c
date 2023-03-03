/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27881, 355, 5762, 56709, 16540, 49662, 16799, 46565, 43079, 17577, 49255, 31571, 15075, 13330, 46011, 37072
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    17429, 37815, 38529, 48718, 13919, 35901, 61116, 32661, 320, 22699, 49976, 43191, 46295, 29437, 53191, 45255
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    485937949, 13424325, 222004098, 2762749062, 230220260, 1782915462, 1026687684, 1520859465, 13785280, 398980323, 2461567880, 1363583061, 697897125, 392395210, 2447371101, 1677693360
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
