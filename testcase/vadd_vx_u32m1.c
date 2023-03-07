/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -431423203, 1967301114, -752959735, 112411590, 2084916619, 351260284, 610247371, 689109430, -1604996807, -1236888006, -619612835, -1502265851, 1812018593, -2044310096, 1652243354, -89729924
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -32705543, -1935303981, -61337962, -382260205, 1223966534, 496665652, 251900114, 648335722, -631346614, -386375053, -1052377260, -887335712, -1718735894, -47300353, -773147164, -879235993
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -561883389, 1822812201, -2366390744, 1851363458, 2408938552, 1648995953, -954389616, 2178435822, -1750998514, -1704883505, -1593731381, 246881543, 8057182, -2898009940, 3268213797, 1035555856
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
