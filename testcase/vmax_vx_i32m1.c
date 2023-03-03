/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4247947585, 1063830897, 2894175181, 3785377940, 1186171480, 3316226905, 145243479, 1721644920, 415619364, 3917805758, 664905492, 2887546351, 4128333163, 2848106457, 91794169, 1865687994
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2709219659, 3152138611, 3154130038, 1485493957, 2942214127, 4187083952, 1778085198, 4292524595, 309249050, 1668686192, 2598198579, 4148904608, 2957861127, 758250602, 3814628674, 4150365007
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
        out_v = __riscv_vmax_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4247947585, 3152138611, 3154130038, 3785377940, 2942214127, 4187083952, 1778085198, 4292524595, 415619364, 3917805758, 2598198579, 4148904608, 4128333163, 2848106457, 3814628674, 4150365007
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
