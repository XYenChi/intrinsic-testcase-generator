/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1415794974, 1968285174, 1932304089, 2032133026, 2254995943, 855014809, 1856712384, 1235829192, 747081026, 1549876995, 2353957416, 416122219, 427502656, 3132753357, 3859626802, 731472534
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1187932501, 89782025, 4136671909, 3865917402, 2902419317, 3249970105, 3485873210, 502902094, 752702929, 617905339, 1447434975, 4145530843, 3321043708, 2907791190, 657645177, 623824488
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    2473537149, 835471612, 1257041276, 2965236443, 3731621160, 225897340, 776453265, 2524168262, 376356011, 3188306210, 695384253, 103427916, 4141697343, 423527888, 1169949031, 839327877
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2473537149, 835471612, 1257041276, 5898050428, 5157415260, 225897340, 5342585594, 1738731286, 376356011, 2167782334, 695384253, 103427916, 3748546364, 423527888, 1169949031, 839327877
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
