/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2225402932, 827180001, 2018188771, 953367088, 1917372153, 2813164881, 3078646646, 2012257077, 1563872048, 3671114084, 4212680881, 2079013219, 1840490967, 3866951900, 3428122792, 1839804620
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1758222020, 2833489016, 2675848349, 3401151454, 2562795786, 4174019502, 1722090534, 2182326862, 1436177989, 232062433, 4163217589, 2798332425, 3206161758, 1885763605, 799136726, 1065980938
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    bool64_t masked[] = {
    0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i32mf2 (data1_v, data2_v, size_t vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2225402932, 2833489016, 2018188771, 3401151454, 1917372153, 4174019502, 1722090534, 2012257077, 1563872048, 232062433, 4212680881, 2079013219, 3206161758, 3866951900, 3428122792, 1839804620
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
