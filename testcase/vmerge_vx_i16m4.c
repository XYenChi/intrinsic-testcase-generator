/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    3562, 62788, 60798, 29868, 29670, 49805, 54634, 35913, 36143, 38363, 47101, 48363, 29517, 21238, 13408, 39685
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    65463, 11301, 45731, 31532, 38291, 40663, 34830, 12893, 28095, 17870, 49967, 7298, 60325, 26482, 16114, 16911
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    bool4_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16m4 (data1_v, data2_v, size_t vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65463, 11301, 45731, 31532, 38291, 49805, 54634, 35913, 36143, 38363, 47101, 48363, 29517, 21238, 13408, 39685
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
