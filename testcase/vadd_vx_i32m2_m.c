/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1693786069, -981839040, 1493702063, -1795433935, 921704329, -1119079565, -2071317808, -275757809, 1426961828, 408645250, -429426296, -372528626, 118940649, 880420094, -479310403, 1734899382
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -299521491, -2092334327, 505468022, -1774557108, -1944666275, -1451876846, -368042247, -445798888, 2093881000, -1068623295, 1271534834, 1276200020, 598511721, 200272126, -206686174, 106084778
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 1220793929, 1999170085, 1, 3272005350, 1724010885, 1855607241, 1, 1, 0, 0, 903671394, 717452370, 1, 3608970719, 1840984160
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
