/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7116073485465755168, 74891353717562461, -6812787846768187790, -1910745256310793025, 7074835808822180329, 9017073951253927919, 739828871984698565, -2216092661095145421, 7620497353804728600, -6806273331908610459, 1484982298589196114, 8385932611581425889, -2059507693627943964, 3422759330189988857, 5566109230340229573, -5342993609519341665
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_i64m8 (src, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -7116073485465755168, 74891353717562461, -6812787846768187790, -1910745256310793025, 7074835808822180329, 9017073951253927919, 739828871984698565, -2216092661095145421, 7620497353804728600, -6806273331908610459, 1484982298589196114, 8385932611581425889, -2059507693627943964, 3422759330189988857, 5566109230340229573, -5342993609519341665
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
