/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    8643, 53836, 63611, 7177, 45395, 65300, 36795, 32409, 46553, 46355, 9985, 6253, 33735, 8000, 9821, 16858
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21117, 61197, 6238, 44438, 47859, 1148, 6624, 27517, 9286, 57102, 52645, 36209, 12077, 50837, 11964, 63200
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (*out, vl);
    const int out_data[] = {
    19512, 38043, 2451, 33299, 29095, 49481, 50702, 5029, 34647, 9447, 43907, 25485, 45469, 7760, 24013, 46011
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m4 (data1_v, data2_v, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    182533743, 3294639735, 396807869, 318964825, 2172588400, 75013881, 243780782, 891803482, 432325805, 2646972657, 525704232, 226440362, 407463064, 406703760, 117522457, 1065471611
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
