/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3094689362, 415452006, 3074472972, 3593554040, 2055470115, 806941634, 3619668043, 1457548585, 2173831268, 2174467716, 667439772, 1949067909, 1239010008, 1822308364, 2505512985, 3739466898
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1146687947, 2133552241, 872860497, 3425283886, 2827031179, 724756468, 3367220037, 3326576029, 3010792228, 2779724457, 2820555314, 2730686280, 456442890, 4229302496, 2677437073, 1905037281
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4241377310, 2549004247, 3947333469, 7018837926, 4882501295, 1531698103, 6986888081, 4784124615, 5184623497, 4954192174, 3487995087, 4679754189, 1695452899, 6051610861, 5182950059, 5644504179
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
