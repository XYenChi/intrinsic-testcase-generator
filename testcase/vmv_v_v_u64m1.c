/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1900443229921575358, 9788349324490847212, 16111985273828957112, 327451567834740294, 9275982530005639509, 18066466528746197203, 16639459457695551825, 10495206826121305593, 5934190082950620820, 452000724172854834, 1895149775410540294, 967388653784860010, 390467908187702786, 10187198670106065168, 4779857798004540633, 5299437599863642650
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_u64m1 (src, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    1900443229921575358, 9788349324490847212, 16111985273828957112, 327451567834740294, 9275982530005639509, 18066466528746197203, 16639459457695551825, 10495206826121305593, 5934190082950620820, 452000724172854834, 1895149775410540294, 967388653784860010, 390467908187702786, 10187198670106065168, 4779857798004540633, 5299437599863642650
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
