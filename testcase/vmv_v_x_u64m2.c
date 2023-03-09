/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5779666815387929558, 17341967206655885860, 17685207639395381853, 2213851527541850477, 3732628264538392043, 1734155376615433691, 8150856657238701186, 11656802215469900892, 14610649080109251446, 149917157593176815, 4949666398739323272, 6812652538898446570, 2873053549470593037, 16851272159884215583, 2789645464190199481, 962363915996108517
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_u64m2 (src, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    5779666815387929558, 17341967206655885860, 17685207639395381853, 2213851527541850477, 3732628264538392043, 1734155376615433691, 8150856657238701186, 11656802215469900892, 14610649080109251446, 149917157593176815, 4949666398739323272, 6812652538898446570, 2873053549470593037, 16851272159884215583, 2789645464190199481, 962363915996108517
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
