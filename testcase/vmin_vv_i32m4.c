/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3691469109, 1848455036, 2324089495, 2496652010, 1965239028, 2155222807, 316432973, 583037787, 2797120083, 3385755822, 1434882876, 2188099080, 3880476650, 2429028233, 2793110567, 3829848419
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1865124596, 3843746890, 1711009934, 2367377006, 914362289, 3464789060, 587369141, 972312820, 3343713465, 985599368, 6159775, 55437740, 570204198, 2206413413, 1829904219, 2246489053
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3691469109, 3843746890, 2324089495, 2496652010, 1965239028, 3464789060, 587369141, 972312820, 3343713465, 3385755822, 1434882876, 2188099080, 3880476650, 2429028233, 2793110567, 3829848419
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
