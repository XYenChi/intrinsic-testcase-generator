/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -89909988, 524522299, -21706862, 2078493596, 1839008572, -1540853754, 25332784, 396962214, 617799955, -1705915884, -1250807347, -1273199226, 395294871, 444568249, 1864068628, 804950483
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    213918539, -982179329, -111866068, -877300179, -62318838, 400192847, -1599345157, -1444030552, -1790783132, -79675650, -732812673, 708464212, -1694209764, 438240472, -753777353, -705861942
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, in1, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32m2 (mask, data1_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    89909988, -524522299, 21706862, -2078493596, -1839008572, 1540853754, -25332784, -396962214, -617799955, 1705915884, 1250807347, 1273199226, -395294871, -444568249, -1864068628, -804950483
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
