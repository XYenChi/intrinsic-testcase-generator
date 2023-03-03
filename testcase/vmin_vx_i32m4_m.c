/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1605754358, 165581825, 1458913736, 2442594478, 389627517, 2881611227, 2324461032, 2106648206, 370852581, 2488227462, 3680115454, 1142986972, 2865346915, 2793463914, 397574359, 3104397300
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    270629191, 3569913108, 2900105798, 4077806193, 2022051320, 2920281216, 1159523046, 3955173483, 1613995990, 3791218786, 603744531, 1897897316, 217048118, 613788779, 704431782, 3571738017
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    3108090930, 4036572439, 4049831494, 4171578673, 1056430593, 2853616373, 3385712509, 1635992469, 3197524776, 2989562881, 4003745574, 3804231451, 2317934908, 3928598594, 2299967031, 3915392940
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3108090930, 4036572439, 2900105798, 4171578673, 1056430593, 2920281216, 2324461032, 3955173483, 3197524776, 2989562881, 3680115454, 3804231451, 2317934908, 3928598594, 704431782, 3915392940
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
