/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1977086994, 3443502027, 3916388377, 3706167927, 1837424018, 1614401977, 1795286499, 411940635, 3313873119, 2685603757, 3268405352, 3273632622, 3152563707, 1050190206, 1819508178, 2263785417
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1109415257, 979033944, 3795313907, 2324447168, 2619588588, 1419006183, 1176264797, 3571307925, 2636965905, 2569956008, 3579180828, 1997239125, 1692595805, 3221171497, 4266502029, 3585288243
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    846014557, 3655172271, 603837536, 10914468, 455517275, 3108285997, 3669894155, 2023172311, 2823992959, 2825380771, 2410563758, 78789904, 1068446397, 2434507382, 3729909128, 3967392148
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    867671737, 2464468082, 121074470, 1381720758, -782164571, 195395794, 619021702, -3159367291, 676907213, 115647749, -310775476, 1276393497, 1459967902, -2170981291, -2446993851, -1321502826
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
