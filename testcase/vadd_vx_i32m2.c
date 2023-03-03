/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4231599040, 1487854988, 66325318, 1044958998, 331813740, 2325249661, 1729632162, 2056749948, 3179075657, 828033972, 1106666104, 3798699001, 1069117992, 3508812410, 563840416, 576660089
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    75506516, 2662114377, 830501057, 1026374309, 1907338494, 2893170127, 2805723894, 1152660661, 3710073212, 567062864, 3703598973, 69581016, 1534080275, 2177348827, 2509156614, 506052665
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
        out_v = __riscv_vadd_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4307105556, 4149969365, 896826375, 2071333307, 2239152234, 5218419788, 4535356056, 3209410609, 6889148869, 1395096836, 4810265077, 3868280017, 2603198267, 5686161237, 3072997030, 1082712754
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
