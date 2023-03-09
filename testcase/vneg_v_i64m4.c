/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -5045773815899264587, -3414385570045612184, -748544131055622161, -4375532609047502149, 37085004357529616, -1711576878539360481, -2807230769237315542, 7911100005734572896, -405710446363115795, 2710476709071672142, -4391956164089049629, 3986929336521667101, -3814011544499815623, -8571746295826025231, -6218399863866071683, 1812364221325939224
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m4 (data1_v, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    5045773815899264587, 3414385570045612184, 748544131055622161, 4375532609047502149, -37085004357529616, 1711576878539360481, 2807230769237315542, -7911100005734572896, 405710446363115795, -2710476709071672142, 4391956164089049629, -3986929336521667101, 3814011544499815623, 8571746295826025231, 6218399863866071683, -1812364221325939224
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
