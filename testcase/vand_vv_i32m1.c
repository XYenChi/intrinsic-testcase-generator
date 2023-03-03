/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2891218064, 1785285762, 1361363378, 3578695085, 3025200970, 3804638778, 4095151628, 922037409, 4222578370, 1457243422, 145548372, 3635025210, 2482450719, 831423384, 2788227298, 2404019156
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3706038366, 3668164480, 824059213, 430733471, 1587290526, 1979095305, 1930832613, 3099659955, 319720789, 886985788, 2399573152, 309443058, 1318244994, 3090454586, 1402488283, 504912180
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, size_t vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3706038366, 3668164480, 824059213, 430733471, 1587290526, 1979095305, 1930832613, 3099659955, 319720789, 886985788, 2399573152, 309443058, 1318244994, 3090454586, 1402488283, 504912180
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
