/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    428504513, 3496990871, 3008513787, 256397037, 2777195734, 2712228522, 2265943460, 1572900096, 3189947950, 2812390223, 3976207947, 112499620, 460554187, 1163071773, 781461724, 3135297578
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2875602304, 1435736675, 173085650, 256275679, 3015587386, 2404491371, 2300311460, 1316212213, 1684294419, 980378161, 3819617525, 2596535504, 2694434321, 3458323141, 2824391291, 92891611
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    2078406176, 1097443507, 2380667957, 1780891199, 2083553902, 2932292965, 533739756, 2088659286, 723034187, 1619643102, 149897152, 1696480103, 3179429174, 3561582877, 1714634408, 3839280468
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2078406176, 1097443507, 520730564356856550, 1780891199, 2083553902, 2932292965, 533739756, 2070270316184072448, 5372811529085491050, 2757205954839119903, 15187593557405471175, 1696480103, 3179429174, 4022278027209798993, 2207153687515445684, 291242842984818158
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
