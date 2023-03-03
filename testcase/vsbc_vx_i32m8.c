/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2796796162, 2714856101, 2510942259, 2324089952, 533988047, 4132297943, 3939953255, 2242622303, 3815767003, 3663159620, 2415978588, 2111176238, 1899858812, 818166647, 1816610178, 2182272661
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    109917516, 2098082646, 888904163, 1787279863, 165987578, 293703771, 4101187040, 3899069476, 1462159481, 1284362252, 3011338268, 2825511826, 3527922573, 3001939901, 1023186536, 1104569097
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2686878646, 616773455, 1622038096, 536810089, 368000469, 3838594172, -161233785, -1656447173, 2353607522, 2378797368, -595359680, -714335588, -1628063761, -2183773254, 793423642, 1077703564
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
