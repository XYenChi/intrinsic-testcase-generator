/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4291294016, 346404617, 4047081814, 878089079, 2175692630, 2071957668, 4280672417, 624711347, 3194366972, 2461832850, 2785750056, 2802814001, 2696538069, 205268785, 1378766608, 2004626637
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    631107569, 3542173499, 4260056158, 3721239786, 2644339973, 3807043565, 1868962758, 392599896, 660368302, 739479988, 3222144581, 2381787556, 850950869, 3621270501, 453335977, 2813690747
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4922401585, 3888578117, 8307137973, 4599328865, 4820032604, 5879001233, 6149635176, 1017311244, 3854735274, 3201312838, 6007894637, 5184601557, 3547488939, 3826539287, 1832102585, 4818317385
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
