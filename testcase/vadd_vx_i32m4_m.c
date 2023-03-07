/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1814345079, -704731612, 1682200736, -1580004052, -1675096001, 1726242264, -1095544875, 944178218, -923138194, 1976948801, 587669073, 274299452, 205345897, 1814822495, 1292693884, -1806060012
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -750431951, -825853488, 1249599208, 1826040121, 97786762, 1947122883, 1640527293, 1586687917, 517975907, -823549997, -1156736393, 1398225372, -1214304971, 1746925470, -1193337368, 429056085
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    -1010162663, 1943555299, 1586607519, -154281020, 1299171146, 856788734, 710375721, -1248076053, -1340253092, 1778433292, -1822364838, -478070074, -1215203274, -940976471, -1475878471, -1269076720
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1010162663, 1943555299, 1586607519, -154281019, 1299171146, 856788735, 710375721, -1248076053, -1340253092, 1778433293, -1822364837, -478070073, -1215203274, -940976470, -1475878471, -1269076719
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
