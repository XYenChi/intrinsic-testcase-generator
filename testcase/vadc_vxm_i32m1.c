/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    620450647, 584844786, 603804410, 283180394, -528897361, 174110626, -1978299851, 183470357, 1913181834, 1666719369, 1147933900, -2113631215, -449363492, 1466547594, -1836273566, -377559099
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1740507519, -723845765, -300291154, -1949421536, 1114851733, 459360936, 223723190, 368884061, 599962170, -1250287022, -1189323022, 436907283, -886162323, -965205293, -818164492, -602516951
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1120056871, -139000978, 303513257, -1666241141, 585954372, 633471563, -1754576661, 552354418, 2513144004, 416432347, -41389121, -1676723931, -1335525815, 501342302, -2654438057, -980076050
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
