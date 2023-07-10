/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1695607379, 1044644330, -1574058376, 1280722501, 229573073, -810506540, 1040204211, 90101190, -1354083588, 2129187678, 1477079311, 528247003, 742527196, -1595804486, 1463658740, 1650787239
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1288419432, 451839326, 1387021492, 1710070070, -284060486, 1026311416, 144750178, -1092690275, -1565638685, -1874257892, -1741057104, 1587301607, 1536430813, 879853260, -257619964, 1940463094
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1
    };
    const uint64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 1, 4107930412, 0, 4240479883, 215804876, 0, 0, 1375245023, 254929786, 1, 2115548610, 1, 3579016070, 1206038776, 3591250333
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
