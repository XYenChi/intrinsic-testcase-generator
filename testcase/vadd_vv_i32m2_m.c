/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1335072053, 3889736953, 1493887960, 3834114404, 1217282033, 2300785665, 3616609197, 2730500447, 3459625210, 3199727513, 3914660, 2077463346, 872309946, 2486994781, 3988653583, 2898678737
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3412941194, 3554627101, 2575123839, 2714674871, 1954471629, 1506724519, 4095232760, 2569052814, 3866141034, 3579468295, 3808759401, 3205914234, 1488252229, 2602376881, 3275780956, 3863094753
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    4048765807, 1060797865, 3735731961, 3778203799, 3575056458, 1090891936, 2746545850, 220118368, 3586963564, 282187485, 1908759026, 1787272266, 3935824894, 1093418105, 4121874892, 290784658
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4048765807, 1060797865, 4069011799, 6548789275, 3575056458, 3807510184, 2746545850, 5299553261, 3586963564, 6779195808, 1908759026, 5283377580, 2360562175, 5089371662, 7264434539, 6761773490
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
