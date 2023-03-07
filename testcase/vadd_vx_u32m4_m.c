/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -503848507, -1763026794, -928835354, -1314400459, -1410847340, -1159741753, -1750246710, 666834027, 1264578407, 574768738, 1051434577, 824136605, -1064108263, 451186871, -1072651673, -1655193077
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -2053686503, 809522930, -1057367135, -1824156249, -1476146196, 310511760, 2103904060, 1047713443, -1748800115, -52014858, -764180550, 771417668, 160910611, -2052930224, 423724661, 1868496661
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    -895097021, 250433474, -1157399015, 1168009458, 561368089, -1080830229, -1814920995, -937184319, -1489269383, -1813845267, -1973809102, 1063178596, -2068636320, -1998738696, -166663125, 2141339575
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -895097020, 250433475, -1157399015, 1168009458, 561368089, -1080830228, -1814920994, -937184319, -1489269383, -1813845267, -1973809102, 1063178597, -2068636319, -1998738696, -166663125, 2141339575
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
