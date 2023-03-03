/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4101775616, 2116243820, 508245964, 253820300, 1720170898, 3533973465, 2596044194, 3129754115, 262852788, 3457403633, 1559624041, 2196061174, 63910344, 2202195859, 2878852352, 396639547
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3793030412, 2181517456, 1780538698, 3915215311, 2170103911, 744796805, 1630301868, 3127402467, 2345943255, 3231693798, 2850773952, 2905847922, 93927214, 3043102955, 1489259778, 879565415
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i32m1 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4101775616, 2116243820, 1780538698, 3915215311, 1720170898, 744796805, 2596044194, 3127402467, 2345943255, 3457403633, 2850773952, 2905847922, 93927214, 3043102955, 1489259778, 879565415
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
