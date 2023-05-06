/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    99, 174, 112, 194, 213, 246, 9, 107, 118, 208, 57, 177, 155, 185, 64, 131
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    94, 166, 223, 102, 116, 167, 50, 168, 26, 35, 98, 175, 186, 179, 57, 144
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u32m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    4294957991, 4294938412, 4294942320, 4294947508, 4294942588, 4294926214, 4294966846, 4294949321, 4294964228, 4294960016, 4294961711, 4294936321, 4294938466, 4294934182, 4294963648, 4294948433
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
