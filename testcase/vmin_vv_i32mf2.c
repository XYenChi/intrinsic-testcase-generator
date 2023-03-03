/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    200912578, 3583957271, 3574573761, 3440562505, 655997169, 2150196508, 2974902483, 3407445859, 2069098045, 1353964332, 3522591808, 269753512, 986032023, 3182202585, 2933690957, 3629918138
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1427058217, 2327701520, 2366695024, 1871358247, 3190557504, 1289223496, 626661302, 4055467717, 3773261065, 3764815168, 4058109442, 506443746, 3883948233, 505085507, 836276233, 1733245819
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1427058217, 3583957271, 3574573761, 3440562505, 3190557504, 2150196508, 2974902483, 4055467717, 3773261065, 3764815168, 4058109442, 506443746, 3883948233, 3182202585, 2933690957, 3629918138
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
