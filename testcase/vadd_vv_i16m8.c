/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m8_t data1[] = {
    255, 166, 54, 176, 163, 47, 22, 69, 32, 7, 155, 32, 115, 252, 100, 50, 20, 45, 48, 82, 27, 129, 106, 5, 3, 135, 54, 216, 32, 170, 56, 111, 18, 142, 34, 162, 194, 200, 201, 102, 124, 215, 78, 218, 53, 64, 149, 38, 134, 64, 216, 180, 60, 116, 152, 216, 176, 75, 150, 138, 250, 91, 119, 83
    };
    const vint16m8_t *in1 = &data1[0];
    vint16m8_t data2[] = {
    4, 162, 19, 52, 106, 169, 108, 78, 229, 191, 224, 176, 136, 236, 61, 169, 110, 65, 24, 24, 252, 201, 88, 221, 143, 55, 0, 163, 248, 35, 64, 83, 181, 91, 251, 209, 20, 81, 197, 22, 239, 230, 90, 8, 60, 88, 189, 63, 236, 75, 217, 74, 140, 157, 253, 131, 168, 130, 163, 4, 36, 170, 152, 93
    };
    const vint16m8_t *in2 = &data2[0];
    vint16m8_t out_data[64];
    vint16m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m8_t out = __riscv_vadd_vv_i16m8 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m8_t golden[] = {
    259, 328, 73, 228, 269, 216, 130, 147, 261, 198, 379, 208, 251, 488, 161, 219, 130, 110, 72, 106, 279, 330, 194, 226, 146, 190, 54, 379, 280, 205, 120, 194, 199, 233, 285, 371, 214, 281, 398, 124, 363, 445, 168, 226, 113, 152, 338, 101, 370, 139, 433, 254, 200, 273, 405, 347, 344, 205, 313, 142, 286, 261, 271, 176
    };
    int fail = 0;
    for (int i = 0; i < 64; i++)
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
