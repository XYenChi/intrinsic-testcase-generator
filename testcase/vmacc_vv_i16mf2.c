/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    44201, 49000, 31860, 27852, 62885, 27870, 47935, 30563, 13583, 25287, 45465, 47458, 27129, 60825, 61386, 59707
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    30976, 25574, 49733, 1929, 602, 25640, 8558, 40577, 59109, 10503, 1842, 26513, 1379, 18289, 30002, 20529
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    const int out_data[] = {
    40425, 57946, 52760, 8153, 36698, 24843, 36303, 35345, 21094, 6607, 7599, 10145, 40051, 15510, 9009, 26556
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16mf2 (data1_v, data2_v, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1369210601, 1253183946, 1584546140, 53734661, 37893468, 714611643, 410264033, 1240190196, 802898641, 265595968, 83754129, 1258264099, 37450942, 1112443935, 1841711781, 1225751559
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
