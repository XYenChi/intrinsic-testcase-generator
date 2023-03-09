/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    15329041784210958671, 9406385804749789131, 13090205922307979306, 9574213499402898089, 15360733239264585280, 13554891764924549716, 7234147914066702878, 8074149014700156113, 9655187922169604916, 5009204202594280481, 10303665893818124287, 3928300638434390393, 8857414500070061452, 601475563042039007, 10410207381566375376, 2749887403599084488
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_u64m4 (src, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    15329041784210958671, 9406385804749789131, 13090205922307979306, 9574213499402898089, 15360733239264585280, 13554891764924549716, 7234147914066702878, 8074149014700156113, 9655187922169604916, 5009204202594280481, 10303665893818124287, 3928300638434390393, 8857414500070061452, 601475563042039007, 10410207381566375376, 2749887403599084488
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
