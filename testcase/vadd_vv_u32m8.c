/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1950032074, 813866738, -649513338, 1790182813, -369065709, -870974256, -2058261138, 426185538, 563161833, -654158565, 1071772242, 1887928781, 356382262, -556650810, -1753838658, -2021595484
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -33799698, -190961520, -198265993, 1119400766, 1024798894, -1056977489, -1365899281, 299783093, 26735163, 922993687, -732395559, -1683183848, -637623737, -1103647362, -746617965, 1715887308
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3954177046, 1336766266, 427571685, 317417024, 164706096, -456939030, -2210910195, -1231087806, 502888152, 252366195, 748672058, -199813247, -702099763, -1795943824, -543627094, -1721322167
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
