/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2464585102, 3899452017, 716175868, 523946679, 374461605, 3046823974, 65170063, 3563127727, 3468909405, 1681470884, 3660284014, 1183559394, 4031299682, 3708853259, 1792423097, 3623805162
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2733758566, 430928723, 1196399020, 876586556, 3808302328, 48607927, 629146671, 3959784143, 536647268, 4044172383, 2347470645, 2223615638, 103368152, 4146993389, 574355415, 3091496942
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    4140865971, 2554720100, 2230987514, 683859700, 2934398819, 1345213572, 946994302, 1878768472, 1374671857, 3215217538, 3481588956, 3664005765, 1628694520, 401906547, 4277599133, 2784428262
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    6737580634228483732, 1680385878085584291, 2230987514, 683859700, 2934398819, 148099797310041898, 946994302, 1878768472, 1861580755132755540, 6800158111891396572, 8592409275227769030, 3664005765, 416707998286527664, 401906547, 1029487911733020255, 2784428262
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
