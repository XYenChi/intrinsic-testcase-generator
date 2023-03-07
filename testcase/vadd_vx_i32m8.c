/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1770229781, 339619761, -1893931361, -1807479341, -1483745739, -64820613, 894252608, 1401267418, 1717622903, 971342582, 1901580188, 840439649, 2031774194, 2126810363, -1347235424, -1364243935
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1800797956, -294566272, -1679166844, -1935378535, -760656324, -1278188525, -97646841, 1676185832, 787695268, 1831491491, 2112897694, 858544557, -1994418105, 40543169, -598417115, -1602041218
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2998397727, 2146665575, -2973518457, -3364495512, -1315499925, 1159690272, 286767856, 663569076, 2731481609, 2059607994, 2653427629, 1436714105, 1489381179, 3161996391, -2550912556, -3206173471
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
