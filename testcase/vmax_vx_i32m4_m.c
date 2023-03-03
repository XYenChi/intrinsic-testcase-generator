/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3448083003, 1910455371, 1765232137, 2016920501, 2332922237, 3642981438, 2515447199, 3385897007, 1758012828, 1490278730, 2852120688, 1832026747, 3556836418, 4047971591, 142856433, 1432628322
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    491078605, 1376459179, 169794821, 1637962384, 4142915625, 784577946, 2877447513, 3521081869, 2903084053, 2943983860, 1204032794, 4157514175, 1753713114, 2176066417, 2620978865, 3524273175
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1855290604, 3667507039, 2021212392, 2905075870, 1359384125, 1876772971, 1524140895, 325572744, 399669771, 3285383298, 2454579013, 3267181022, 500721389, 2162599793, 814675655, 1273535264
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3448083003, 3667507039, 1765232137, 2905075870, 4142915625, 1876772971, 1524140895, 325572744, 399669771, 2943983860, 2852120688, 4157514175, 500721389, 2162599793, 814675655, 1273535264
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
