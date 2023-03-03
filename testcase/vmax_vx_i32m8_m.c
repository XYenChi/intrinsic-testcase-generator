/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3060409742, 3228780598, 2650545874, 4175503268, 805958970, 104250366, 70856866, 4211568929, 1200358189, 2588804223, 64865873, 428737530, 3880387600, 1733009234, 350636053, 1496262983
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3353981370, 1890067530, 1111908481, 2463517368, 2427966374, 1598359808, 2603368003, 4006931051, 874818689, 1187875233, 3218503309, 28052376, 2884284741, 1762407533, 2336941827, 510391648
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    2524472070, 693439134, 1014878699, 4087434842, 2626450087, 2173545585, 643626312, 962913594, 4286001005, 3096074377, 559758992, 1297738494, 4214835006, 1442234065, 3259803540, 3028392081
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2524472070, 3228780598, 1014878699, 4175503268, 2427966374, 1598359808, 2603368003, 962913594, 4286001005, 2588804223, 3218503309, 1297738494, 4214835006, 1762407533, 2336941827, 1496262983
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
