/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4280651276, 1610237839, 2472625495, 3915166169, 4186391126, 2586518673, 3083374091, 4015648377, 729939313, 721170544, 1435412975, 262244285, 258928080, 845172446, 1054915371, 1538393991
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3583680491, 1923297185, 2849759748, 4033909420, 3480873769, 263769018, 2216760060, 1369328289, 3469032233, 2518986087, 4071987530, 568525765, 2120795015, 43815605, 50403026, 2197444282
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    1992610150, 4172051404, 3181197435, 2119814188, 2410242283, 873034598, 500037515, 3688367939, 4033793601, 60218124, 3745296858, 2212655362, 2086003731, 4081859372, 1900015276, 1093497241
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1992610150, 1923297185, 3181197435, 4033909420, 3480873769, 873034598, 500037515, 1369328289, 4033793601, 2518986087, 3745296858, 2212655362, 2086003731, 43815605, 1900015276, 1093497241
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
