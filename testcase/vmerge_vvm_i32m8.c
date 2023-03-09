/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    741836502, 1655060101, -2080971229, 1740093901, -772777569, 536468652, 1845306666, -1207360694, -188768933, 1899905086, 1497875477, -1325541791, 1809346520, 2118110229, -898153128, -1932600872
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1022038616, 1346997493, 1561595539, -1347663035, -128405498, 1165896011, 924197366, 2093243115, -1404592259, -1118161410, 1046777612, 1709413531, 1171137408, -1971226585, 958915557, -726181991
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1022038616, 1346997493, -2080971229, 1740093901, -772777569, 1165896011, 1845306666, -1207360694, -188768933, -1118161410, 1046777612, 1709413531, 1171137408, 2118110229, 958915557, -726181991
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
