/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1380341156, 407158041, 1622860004, 3092489318, 2740748842, 2886796539, 862042762, 1059599352, 2011488564, 2492787076, 3669271532, 1185520923, 931549425, 318901491, 3662739513, 1210796966
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3348046624, 275728383, 2420488721, 3598269140, 3957469732, 1415425532, 34505534, 103086882, 3835146886, 30553893, 464673360, 1510503134, 1888163617, 2217407085, 1044112752, 2067421822
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    bool32_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i32m1 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3348046624, 275728383, 2420488721, 3598269140, 2740748842, 2886796539, 862042762, 103086882, 3835146886, 30553893, 464673360, 1510503134, 931549425, 318901491, 1044112752, 2067421822
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
