/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m2_t data1[] = {
    74, 2, 121, 82, 151, 157, 151, 48, 219, 163, 126, 24, 79, 11, 80, 82, 100, 210, 89, 15, 230, 37, 242, 83, 158, 21, 12, 152, 242, 128, 215, 157
    };
    const vint8m2_t *in1 = &data1[0];
    vint8m2_t data2[] = {
    94, 36, 104, 247, 80, 32, 54, 109, 200, 75, 52, 103, 231, 53, 163, 239, 32, 87, 201, 236, 163, 1, 83, 165, 182, 75, 151, 179, 99, 153, 54, 252
    };
    const vint8m2_t *in2 = &data2[0];
    vint8m2_t out_data[] = {
    26, 178, 206, 14, 244, 31, 91, 57, 189, 96, 92, 11, 230, 201, 256, 141, 164, 96, 203, 177, 161, 131, 250, 124, 114, 222, 66, 114, 128, 40, 241, 185
    };
    vint8m2_t *out = &out_data[0];
    int masked[] = {
    0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 32, Q_element = 8;n >= 0; n -= Q_element) {
        vint8m2_t out = __riscv_vadd_vv_i8m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8m2_t golden[] = {
    26, 178, 206, 14, 231, 31, 205, 157, 419, 238, 178, 11, 230, 201, 243, 321, 132, 96, 290, 177, 393, 38, 250, 248, 340, 96, 163, 331, 128, 281, 269, 185
    };
    int fail = 0;
    for (int i = 0; i < 32; i++){
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
