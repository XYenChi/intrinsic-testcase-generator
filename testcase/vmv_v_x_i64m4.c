/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7976560518833647712, -4726297191381720619, 402246351463222068, 1588060819851640133, 1065506960166598789, -913025303866883268, 6422365397779570367, -6664170115452373519, -4806042127066642569, 8756926293758082066, 5588639970082140636, -6675259410287068780, 9106755729884018753, 6429696629780550616, -3230762450655203346, -2797814508266235347
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_i64m4 (src, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -7976560518833647712, -4726297191381720619, 402246351463222068, 1588060819851640133, 1065506960166598789, -913025303866883268, 6422365397779570367, -6664170115452373519, -4806042127066642569, 8756926293758082066, 5588639970082140636, -6675259410287068780, 9106755729884018753, 6429696629780550616, -3230762450655203346, -2797814508266235347
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
