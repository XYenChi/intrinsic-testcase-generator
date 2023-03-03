/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    78738740, 2446517128, 1969431203, 2040592640, 2594010342, 3188716313, 1902376053, 996102480, 1014813702, 2745552108, 3786853682, 359587035, 2552127403, 2635026036, 4154487552, 3824657880
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2484321421, 3254504357, 2015266906, 4146757575, 322859533, 3288988030, 3214992353, 919722418, 960826596, 2822882944, 3322245726, 3029509993, 2939589881, 3733448315, 916453987, 3963814729
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    510922123, 2233498874, 1118776330, 3543612310, 3555301112, 3701062413, 2941145736, 1587348101, 4291233297, 1955453045, 3206168945, 4166979441, 3865639503, 750486968, 2375974145, 3499218881
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    43420481, 807987229, 1118776330, 65572295, 322859533, 3701062413, 1312616300, 919722418, 960826596, 1955453045, 3206168945, 4166979441, 3865639503, 1098422279, 2375974145, 139156849
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
