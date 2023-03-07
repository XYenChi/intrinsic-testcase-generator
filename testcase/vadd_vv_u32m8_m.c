/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    169782135, -281594153, -995173839, -1418974529, -279824435, -1853071635, 47963351, -427075131, -770833946, -147762741, 511105178, 500056906, 2114289405, -6271709, 17816826, 1353525934
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1618541817, -964987986, -216381476, 538540451, -2042537995, -1669763680, 451234405, 1815432065, -682797603, -1941052975, -1768649637, -2068270088, 12538052, -1262811059, 1441017174, -758285576
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    -1403147175, 1847910763, 1366494554, 425689533, 794919700, 1470220039, -1038546834, 557522078, -1247241255, -1963879547, 2071235830, 761170502, -1378875942, -51837647, -663989289, 1707482193
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1403147174, 1847910764, 1366494555, 425689534, 794919700, 1470220040, -1038546834, 557522078, -1247241255, -1963879546, 2071235831, 761170503, -1378875942, -51837646, -663989288, 1707482193
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
