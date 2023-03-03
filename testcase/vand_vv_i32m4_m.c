/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3940663226, 151511464, 2327441708, 111248179, 1897508424, 2596458994, 912190219, 1418613017, 3998694870, 999530751, 1011013939, 142939092, 3657428895, 526175733, 1945473349, 564564682
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1340389674, 2144931398, 4275339598, 2061242720, 2723700427, 3992347719, 253427030, 1662391130, 115707143, 3358036543, 241005289, 1611741493, 2547403275, 1239741780, 3954586843, 21628252
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    461142563, 3381262202, 1123792256, 3064446058, 3492045403, 1589479070, 1321084064, 3852687549, 1410268181, 2541147532, 1310944628, 2799960688, 594039760, 2142374293, 1514714954, 7770780
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1340389674, 2144931398, 1123792256, 3064446058, 3492045403, 3992347719, 1321084064, 3852687549, 115707143, 2541147532, 241005289, 2799960688, 2547403275, 2142374293, 3954586843, 7770780
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
