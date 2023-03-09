/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1324824747, 1769890846, -1801153300, -1753370920, -1133545337, 651544499, -2124830863, 1241490004, 1057735796, -261338395, -1495058465, -617515655, -128851964, -984954289, -1690118878, 268359589
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    276866148, 1569265991, -262032487, -89508370, -1276775627, -75212439, -2104760400, 1031873057, -1380585625, 668796959, -1988129808, 150398524, -873733879, -1522804290, -508867110, 1392367095
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    276866148, 1769890846, -1801153300, -1753370920, -1276775627, 651544499, -2104760400, 1031873057, -1380585625, 668796959, -1495058465, -617515655, -128851964, -1522804290, -1690118878, 268359589
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
