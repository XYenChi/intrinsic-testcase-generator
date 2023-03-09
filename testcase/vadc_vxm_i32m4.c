/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    973897397, 1615837443, -1858745105, -2990990, -936878942, 490452605, 975309168, -435667614, -1490332262, -1303213688, -1346820330, -763557986, -2063155552, -10243288, 800767225, -580557472
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1797726561, 1108176227, -712345061, 1673617112, 1886014432, -2004876198, -1005297343, 394064665, 902900606, 1733539609, -1666344612, 1139767123, 2057466672, 1202544901, -395957216, 392584768
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1
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
    -823829163, 2724013671, -2571090166, 1670626123, 949135490, -1514423593, -29988175, -41602948, -587431655, 430325922, -3013164942, 376209138, -5688879, 1192301613, 404810010, -187972703
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
