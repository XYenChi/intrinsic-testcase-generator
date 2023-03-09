/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4150253190, 2074119510, 2355177170, 3173729727, 1455150203, 558197101, 946273423, 1618037368, 4293758654, 4040170131, 363544000, 818035734, 894827406, 319725353, 2189793222, 2253459296
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2227515247, 2087373780, 2363913214, 439117854, 1674254025, 773824956, 661891505, 313688010, 2719860468, 191751286, 1769373844, 1032997289, 2862449326, 4069086164, 1487238367, 1707963198
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4150253190, 2074119510, 2363913214, 3173729727, 1455150203, 773824956, 946273423, 1618037368, 4293758654, 191751286, 1769373844, 1032997289, 2862449326, 4069086164, 1487238367, 1707963198
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
