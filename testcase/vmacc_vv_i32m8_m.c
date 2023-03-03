/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3343050909, 3946240524, 951338593, 1278938357, 3347494432, 1585486899, 160996828, 2055553868, 215209269, 3219189728, 1844006641, 951386119, 1413744583, 3934697663, 2283692137, 3709593206
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2039168035, 4045011694, 3034208815, 3522262409, 2862795978, 3492529534, 1406974882, 1030769197, 2911165644, 3321686342, 2016072790, 698784468, 3681607241, 1026969220, 133693707, 1207991719
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    2886225149, 410820526, 1765032541, 1767747000, 1461064658, 2976864968, 302721058, 1358054333, 4251718359, 386892217, 1109573209, 3997514142, 2913409863, 3182984091, 4204713464, 458178710
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    9648797607943110442, 1621196607792195624, 1679143574154154813, 2260839443771679000, 4890905807446984256, 4719780406856054232, 48737130106804024, 2791553837152310045, 915009200034269571, 1245479450809546977, 2046060366071680969, 3803179465204994899, 4118817411875022129, 12524080064223879333, 9602271076074832569, 1699656629749844260
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
