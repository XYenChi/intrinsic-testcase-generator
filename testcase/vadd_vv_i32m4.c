/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1827628078, 686300093, 3424623284, 1149581515, 3752342646, 3083304064, 4225085539, 668175159, 4207232579, 3150593273, 2371215034, 2392577491, 3213043628, 3710558136, 2332950050, 773419732
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3862572679, 2583543489, 1381803222, 1770790687, 1777629103, 4278901670, 2917047328, 2768548659, 4102835690, 1254143339, 3671572120, 2027713275, 3010929983, 3708106187, 3896335624, 3021594136
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5690200757, 3269843582, 4806426506, 2920372202, 5529971749, 7362205734, 7142132867, 3436723818, 8310068269, 4404736612, 6042787154, 4420290766, 6223973611, 7418664323, 6229285674, 3795013868
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
