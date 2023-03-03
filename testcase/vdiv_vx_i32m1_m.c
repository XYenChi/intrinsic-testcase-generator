/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2588747067, 238169786, 843090917, 2729293858, 2717774132, 4234268108, 2357654451, 2088228569, 3368861630, 2369312595, 2416548853, 3739324775, 2961774853, 1075216822, 2133118255, 244188547
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    516973784, 1667973022, 2373824986, 2966497455, 1770025095, 1984758997, 2732008383, 2023115110, 3380416836, 2885959261, 673967947, 2205033293, 3009526538, 1906916899, 364205400, 142368067
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    2758903297, 1484406201, 1477193877, 1784630165, 3115974193, 1183918835, 2909947360, 2218018744, 1202709789, 3571808049, 3424845388, 1401900342, 1630286762, 94274045, 1928966037, 2663561839
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2758903297, 7, 2, 1, 0, 1183918835, 1, 2218018744, 1202709789, 1, 3424845388, 1401900342, 1, 94274045, 1928966037, 0
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
