/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1691385937, 355685722, 760027247, 233489680, -799889883, -348639508, 1726924870, 1560105228, -877574961, -2119848141, 291593250, -1239121203, 757551076, 398825273, 1892421140, -1554517197
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -367943852, 371704566, 2039289928, 1989540405, 824854056, 222410881, 406185344, 529088654, -304509903, -109042226, -564378650, 656284014, 471195392, 529324647, -118081325, 1760385978
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1691385937, 355685722, 760027247, 233489680, 824854056, 222410881, 1726924870, 1560105228, -304509903, -2119848141, -564378650, 656284014, 757551076, 529324647, 1892421140, -1554517197
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
