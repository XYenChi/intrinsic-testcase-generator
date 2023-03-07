/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    479914505, 187920024, 1886390180, -128544749, 765297454, 1042631819, 6866013, 848092884, -514200705, -839152482, 423261802, -322933022, 1982172889, 1896146747, -1676007504, 664522875
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -423394840, 1138826211, 712168422, 332305344, 29004441, -365532972, -1916707640, 839301871, 1803455576, 577867004, 2129698259, -640258295, 1175286481, -993433407, -178080206, 559388658
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    366913617, -398226590, 221883486, 1246098410, 1558514644, -839343601, 805438336, 137276658, 1097012381, 981358303, 2144030318, 1687425224, 3362506906, 575982153, -1603393919, 527218973
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
