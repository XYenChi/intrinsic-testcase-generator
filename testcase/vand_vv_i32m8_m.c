/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3579263075, 974212428, 2913562655, 1645122570, 127394050, 3070714458, 103119126, 1065346765, 849499302, 3341605628, 1584355421, 944099112, 2415254138, 1620087817, 2514324428, 2368716643
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2071350534, 1970611482, 2823363904, 3866519443, 2760834832, 3465954383, 742484166, 1796272585, 3489232313, 3867839455, 363509387, 372457309, 1742000182, 188759344, 4007324017, 3612718305
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    514089323, 486044441, 3640165381, 3498091795, 1119474591, 3812673683, 1520059224, 2917397007, 15251570, 1573338262, 1211777618, 1576798803, 2235176861, 2840770901, 4178256745, 686040224
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    514089323, 1970611482, 3640165381, 3498091795, 1119474591, 3812673683, 1520059224, 1796272585, 3489232313, 3867839455, 1211777618, 372457309, 1742000182, 188759344, 4007324017, 686040224
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
