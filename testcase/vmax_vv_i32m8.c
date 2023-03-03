/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    581931278, 606634012, 495709429, 278760038, 1274708379, 3607634456, 4057681714, 827510951, 3799419316, 2156224987, 114541263, 4234867286, 2167759378, 1279335082, 477116067, 4032470544
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    686634488, 4222823872, 763778588, 179895441, 2632098376, 2716298756, 3411140199, 993715500, 312483771, 3260065904, 1262245384, 2377471563, 1250786727, 446827921, 2981412425, 4294435311
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
        out_v = __riscv_vmax_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    686634488, 4222823872, 763778588, 278760038, 2632098376, 3607634456, 4057681714, 993715500, 3799419316, 3260065904, 1262245384, 4234867286, 2167759378, 1279335082, 2981412425, 4294435311
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
