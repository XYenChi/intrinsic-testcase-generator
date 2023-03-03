/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3858492831, 3014840541, 4006413336, 3385627679, 3198441380, 835504734, 3383959419, 994063747, 742590111, 2009614712, 3365693388, 1754078300, 3388864216, 3170667661, 1331559840, 4144270108
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4202189037, 433159519, 1893587484, 253383925, 1243800715, 1449935680, 342894132, 269350466, 2595595688, 1544546171, 472790877, 3459131472, 135332823, 1658532791, 4167972254, 3579465222
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i32m4 (data1_v, data2_v, size_t vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3858492831, 3014840541, 4006413336, 3385627679, 3198441380, 1449935680, 3383959419, 269350466, 742590111, 1544546171, 472790877, 3459131472, 135332823, 1658532791, 4167972254, 3579465222
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
