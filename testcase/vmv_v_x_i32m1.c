/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    706604359, 1268688506, -595260036, -46285319, 1229997237, -426285985, 274072263, -867270285, 669256379, 196992130, 968137313, 1902632059, -128582558, 252701126, 1493411822, 505472802
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_i32m1 (src, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
    int32_t golden[] = {
    706604359, 1268688506, -595260036, -46285319, 1229997237, -426285985, 274072263, -867270285, 669256379, 196992130, 968137313, 1902632059, -128582558, 252701126, 1493411822, 505472802
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
