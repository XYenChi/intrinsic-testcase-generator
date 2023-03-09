/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -622181933, 1930331105, -1529454355, -2051861366, 1505977470, -1322517600, 1430829464, -468429732, -1116922949, 591917200, 544201819, -2080316380, 709517981, 2008254937, -647061797, 1282576334
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    1478522345, -893615585, -1283615606, -288246440, -753883791, -666585357, 1669211133, 214958218, 2033820792, 1953283516, -1369132128, -1310299059, -788264214, -2019197377, -1698562707, -1088620329
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, in1, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32m8 (mask, data1_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    622181933, -1930331105, 1529454355, 2051861366, -1505977470, 1322517600, -1430829464, 468429732, 1116922949, -591917200, -544201819, 2080316380, -709517981, -2008254937, 647061797, -1282576334
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
