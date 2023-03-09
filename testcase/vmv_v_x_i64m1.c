/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5862132767199255893, -3361652643700989709, -5127116410313265698, -6777957052583369540, 6906770569267832093, 7424880320927526718, -5279957732371155400, 2326461172208960469, 8701789404747319694, -8661885405317997231, -9134441962098687222, -8614214312924736501, 5354839270073183286, -5857943349148567907, -8362295494490309586, 5639401253275198817
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_i64m1 (src, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    5862132767199255893, -3361652643700989709, -5127116410313265698, -6777957052583369540, 6906770569267832093, 7424880320927526718, -5279957732371155400, 2326461172208960469, 8701789404747319694, -8661885405317997231, -9134441962098687222, -8614214312924736501, 5354839270073183286, -5857943349148567907, -8362295494490309586, 5639401253275198817
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
