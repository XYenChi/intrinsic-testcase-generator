/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2959188862, 832135468, 3295328624, 2020406530, 549983768, 1749256654, 3800071774, 3413173534, 1791559502, 1378337944, 3874395666, 2239969447, 1198294750, 3284888488, 127247997, 2586657916
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3098010842, 3354923513, 1316716853, 1801081104, 2847041543, 4178508206, 1923215010, 912463499, 3160028808, 3623291781, 791279230, 84967902, 3491200854, 705137122, 1811065365, 1839252280
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
        out_v = __riscv_vmax_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3098010842, 3354923513, 3295328624, 2020406530, 2847041543, 4178508206, 3800071774, 3413173534, 3160028808, 3623291781, 3874395666, 2239969447, 3491200854, 3284888488, 1811065365, 2586657916
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
