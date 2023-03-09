/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -260498578, -724193452, -218782627, -135994760, 1135737514, -838018974, -2071951120, 1985093572, 911782255, -207685703, -984956421, -1832235624, 802482850, -255880387, 1005315720, 307571142
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1483703414, -689797404, 1613777264, -1136757840, -1952752170, 1523290245, 1294457279, 1887740252, 351071929, -1489692465, -570170068, -1077596832, -115724072, -1126690318, 142922096, 1982517634
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -260498578, -724193452, -218782627, -135994760, -1952752170, -838018974, -2071951120, 1887740252, 351071929, -1489692465, -984956421, -1832235624, 802482850, -255880387, 142922096, 307571142
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
