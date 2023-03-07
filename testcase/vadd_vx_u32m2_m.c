/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -742123477, -789955956, -928245698, -1938832475, -217742317, -740014706, -1001480663, 200322977, -43829223, 1811536038, -1748596119, 629707475, 86829554, -752856000, 2000940044, 1991150159
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    664186243, 1493096000, -2059438875, 768834021, 477879493, 826561910, 664536297, 677167924, -2107027569, -910454732, 823320480, -309543917, 808088034, 1444902127, 1600045329, -1736609026
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    1700316211, 337625541, -1474058300, 145696806, 1754414099, 1982476227, -1477225894, -819544719, -605366228, 51766212, -799871800, -1881676241, 217395282, -1395759257, 865892269, -1678373796
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1700316211, 337625542, -1474058299, 145696807, 1754414099, 1982476227, -1477225894, -819544718, -605366228, 51766212, -799871799, -1881676241, 217395282, -1395759257, 865892269, -1678373796
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
