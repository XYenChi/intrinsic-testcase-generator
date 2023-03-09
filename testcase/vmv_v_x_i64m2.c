/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -4325738505718066200, 4336641554789358674, -7835139959342229723, 3998083922446852244, -6516316664445695707, -7049775154525261482, 791157193979317949, -7922309302327516602, 1878567997798194462, -4433581539469604219, -7763445309679279828, 817920627877068933, 6251532815410420657, -3135964777896913112, -6894019409885008860, 7807072558261743013
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_i64m2 (src, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -4325738505718066200, 4336641554789358674, -7835139959342229723, 3998083922446852244, -6516316664445695707, -7049775154525261482, 791157193979317949, -7922309302327516602, 1878567997798194462, -4433581539469604219, -7763445309679279828, 817920627877068933, 6251532815410420657, -3135964777896913112, -6894019409885008860, 7807072558261743013
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
