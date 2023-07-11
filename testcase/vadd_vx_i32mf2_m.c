/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -839210260, 1227097122, 2134146877, 692244689, -1597059229, -715337949, -1404360776, 1382719540, -209392718, -392148333, 1063656692, 737901358, -530841035, 1373092106, -1152295501, 2011219520
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -736903092, -201364552, -327998854, -31287326, -836019427, -997427181, -495382223, -378901351, -266896557, -2023305820, -1463650874, 2106026713, 506096426, 1313686773, -1597998202, 549067266
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0
    };
    const int32_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0
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
    2718853944, 0, 1, 1, 1, 1, 2395224297, 1003818189, 3818678021, 1, 0, 1, 0, 1, 1544673593, 0
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
