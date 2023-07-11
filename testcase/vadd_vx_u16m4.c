/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    45755, 43996, 36885, 20128, 57167, 42163, 10916, 8913, 62760, 10592, 64246, 3037, 42458, 39195, 18468, 28327
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    14554, 12792, 49590, 3387, 27448, 18318, 16677, 7545, 15877, 2307, 17800, 24522, 64120, 40574, 35137, 14240
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4 (in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4 (in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u16m4(op1, op2, vl);
        void __riscv_vse16_v_u16m4 (uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    60309, 56788, 20939, 23515, 19079, 60481, 27593, 16458, 13101, 12899, 16510, 27559, 41042, 14233, 53605, 42567
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    58680, 38234, 56239, 12646, 51752, 30140, 6355, 32794, 39360, 37072, 60177, 49235, 27977, 6302, 54925, 60968
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    18003, 50105, 21239, 33659, 61417, 33175, 35013, 15680, 22361, 56264, 37597, 55211, 4355, 49438, 26278, 12499
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4 (in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4 (in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m4 (uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    11147, 22803, 11942, 46305, 47633, 63315, 41368, 48474, 61721, 27800, 32238, 38910, 32332, 55740, 15667, 7931
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
