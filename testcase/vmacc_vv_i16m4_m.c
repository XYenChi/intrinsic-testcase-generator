/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    14423, 57029, 2232, 63347, 13480, 38488, 9165, 60968, 29048, 24850, 25439, 12418, 19592, 39987, 6730, 43296
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    62433, 20701, 15185, 51186, 35161, 31184, 40100, 16848, 56155, 15379, 53462, 29906, 63217, 21285, 22250, 5759
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    30316, 4344, 27210, 45278, 15910, 37063, 27872, 59815, 19927, 19196, 45167, 33413, 7579, 42588, 44164, 57834
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    437247669, 247733976, 60732721, 2868225467, 214466800, 1426480744, 255446881, 3646800920, 578839497, 477020601, 1149003313, 414922635, 148487768, 1702966357, 297223721, 2503980864
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
