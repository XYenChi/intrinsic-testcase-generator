/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1057012732, 1365261824, 25023575, 1630949034, -827601286, -1162631292, -1633252721, 1076206392, -1291641622, -1941256438, -71531485, -166385928, -1757873135, -1472392267, 957904215, 841866753
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1157808637, 121510571, 1314994203, -2078430756, -864746418, -579750369, -1518079948, -297468679, 845718445, 324155087, -1522720885, 640115660, 2066496787, -1240552624, -1029024065, -115689840
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m4 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    634204942, 2842964595, 1360668730, 2264860901, -1931001434, -1222862891, -2077217271, 657772970, -854246156, -1152131813, -109053633, -2174195711, -1582533000, -1083952872, 101274626, 1560787584
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
