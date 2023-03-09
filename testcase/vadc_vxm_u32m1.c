/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3330733272, 3371154347, 3503147868, 1887017750, 4084915731, 852491562, 3662635016, 4189416751, 1031686696, 2448690362, 469160189, 232134459, 3106500215, 653863936, 1420515743, 153481109
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1981210951, 1730441257, 1935086483, 4086665013, 3392855918, 607106947, 2123553956, 1780039857, 2665030060, 2687849668, 171967996, 2031040215, 2995285689, 3839670267, 1552223428, 1126090701
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5311944223, 5101595605, 5438234351, 5973682763, 7477771650, 1459598509, 5786188973, 5969456608, 3696716757, 5136540030, 641128186, 2263174674, 6101785904, 4493534204, 2972739171, 1279571811
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
