/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3600299796, 3766959073, 296596526, 3936531311, 3395869111, 913900908, 3370975716, 385225655, 619694720, 3975859133, 3925582863, 1469685182, 729632958, 2189684129, 3150066890, 1375621606
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1077310962, 3309842533, 2505118803, 789160461, 3329439237, 1826641303, 3148169244, 1036313951, 2440011512, 1533528011, 1590826446, 2640371534, 1505587404, 260452254, 2121779881, 3067852427
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, size_t vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1077310962, 3309842533, 2505118803, 789160461, 3329439237, 1826641303, 3148169244, 1036313951, 2440011512, 1533528011, 1590826446, 2640371534, 1505587404, 260452254, 2121779881, 3067852427
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
