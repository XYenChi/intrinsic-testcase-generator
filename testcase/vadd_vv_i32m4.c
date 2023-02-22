/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    2146419994, 2930332562, 3397984974, 1464310378, 1337565689, 1064534938, 833592385, 2245286060, 220645518, 583916439, 3303484459, 294607644, 2356328000, 3857014867, 1458170261, 3176901891
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    3812370919, 937595438, 1454547472, 372805095, 3507898618, 2727427945, 739605387, 1986131524, 2846884035, 2091933931, 3678362526, 1584547755, 1730618608, 3432446324, 574552765, 349132153
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[64];
    vint32m4_t *out = &out_data[0];
    for (int n = 16, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vv_i32m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m4_t golden[] = {
    5958790913, 3867928000, 4852532446, 1837115473, 4845464307, 3791962883, 1573197772, 4231417584, 3067529553, 2675850370, 6981846985, 1879155399, 4086946608, 7289461191, 2032723026, 3526034044
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
