/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1779021436, 1017243321, 2653249566, 2347065065, 3178956878, 2638581235, 2027243783, 4191342587, 2414091136, 2440001415, 964291580, 3163654066, 1678203951, 3086584073, 3743283401, 2153022915
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    49559536, 2159153242, 2865257060, 458739578, 827022860, 548885873, 656866485, 2293027852, 2400855335, 905692976, 2382830340, 3525959865, 1596729722, 1004508734, 4280849547, 3424795318
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    49559536, 124666600, 212007494, 458739578, 827022860, 548885873, 656866485, 2293027852, 2400855335, 905692976, 454247180, 362305799, 1596729722, 1004508734, 537566146, 1271772403
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
