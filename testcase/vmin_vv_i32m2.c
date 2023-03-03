/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    778666366, 2078404300, 247703884, 2925259153, 1133338045, 160392372, 3152342876, 3656222421, 85618323, 3236381063, 649892864, 2184348646, 1305511256, 511266362, 42300463, 3297511469
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1593912388, 2583246367, 4087961433, 2909837169, 2108935904, 2873381730, 1398349583, 2408063037, 930246001, 2320774410, 2179397499, 4289902898, 3767485782, 4130201048, 2558052057, 1241124862
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1593912388, 2583246367, 4087961433, 2925259153, 2108935904, 2873381730, 3152342876, 3656222421, 930246001, 3236381063, 2179397499, 4289902898, 3767485782, 4130201048, 2558052057, 3297511469
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
