/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -1158942167383326282, 5394507765025565839, 5637531536551976650, 2981236226142184099, 278338300458781899, -8968039044769213996, -5640943126277670536, 7315189345750833335, 7980973236322909457, -188686907454732020, 2533820261055192176, -6680517833081838807, -625784716703764826, 1898887489226717600, -4787120557110879155, 365273881887528469
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_i64m8 (src, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -1158942167383326282, 5394507765025565839, 5637531536551976650, 2981236226142184099, 278338300458781899, -8968039044769213996, -5640943126277670536, 7315189345750833335, 7980973236322909457, -188686907454732020, 2533820261055192176, -6680517833081838807, -625784716703764826, 1898887489226717600, -4787120557110879155, 365273881887528469
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
