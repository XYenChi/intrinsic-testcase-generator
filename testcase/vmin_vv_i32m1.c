/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2572770338, 1255076340, 3456067106, 1273917866, 2723504358, 3255237576, 1659514482, 4096990858, 1222103510, 2587116191, 2391128773, 3641107986, 1609514479, 3514983561, 37420958, 1394795468
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1218373553, 853387945, 2441876827, 3094957213, 3817512828, 23415168, 3771704769, 2498867580, 2210679583, 3488885182, 1916668614, 274433255, 3958314540, 855329291, 4234577551, 2429771114
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2572770338, 1255076340, 3456067106, 3094957213, 3817512828, 3255237576, 3771704769, 4096990858, 2210679583, 3488885182, 2391128773, 3641107986, 3958314540, 3514983561, 4234577551, 2429771114
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
