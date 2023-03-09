/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7880430725828156180, 5313875370459946162, 483612038972912697, -4279793984449262073, -3357204328641167148, 4499195725891469308, 3509765598365066177, -2512113796609525034, 7063333887959119708, 627405858252781866, -759385695152329956, 753971858952521008, -7731506472396717213, -7755581330297048861, -2330712394929972468, -9106092634815442547
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m1 (data1_v, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    7880430725828156180, -5313875370459946162, -483612038972912697, 4279793984449262073, 3357204328641167148, -4499195725891469308, -3509765598365066177, 2512113796609525034, -7063333887959119708, -627405858252781866, 759385695152329956, -753971858952521008, 7731506472396717213, 7755581330297048861, 2330712394929972468, 9106092634815442547
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
