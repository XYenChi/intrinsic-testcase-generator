/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -1166249911865354817, 1687131610769877595, 493927735648393577, -7825520189032916884, 3923858427233688132, -1042538902255511173, 6628638429931310581, -7617416811902158632, 3813002882418144428, -1416146393574974717, 6335430251119245886, -2262228899755708311, -6661743460204572233, -70782797695029273, 466911197972546736, -747724064664927574
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m8 (data1_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    1166249911865354817, -1687131610769877595, -493927735648393577, 7825520189032916884, -3923858427233688132, 1042538902255511173, -6628638429931310581, 7617416811902158632, -3813002882418144428, 1416146393574974717, -6335430251119245886, 2262228899755708311, 6661743460204572233, 70782797695029273, -466911197972546736, 747724064664927574
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
