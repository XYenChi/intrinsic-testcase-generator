/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m1_t data1[] = {
    83, 82, 69, 211, 82, 172, 112, 245, 172, 18, 33, 179, 49, 72, 57, 226, 62, 166, 53, 126, 243, 107, 121, 116, 200, 226, 55, 195, 24, 110, 225, 67, 84, 183, 19, 24, 211, 234, 240, 153, 205, 139, 197, 219, 134, 92, 40, 117, 124, 117, 92, 240, 224, 183, 238, 74, 56, 91, 243, 70, 61, 44, 94, 121
    };
    const vint16m1_t *in1 = &data1[0];
    vint16m1_t data2[] = {
    64, 12, 24, 179, 199, 95, 146, 82, 83, 77, 80, 148, 137, 53, 82, 66, 181, 172, 143, 43, 202, 175, 96, 36, 195, 165, 238, 74, 138, 161, 216, 136, 203, 67, 103, 101, 155, 247, 108, 16, 53, 120, 160, 56, 201, 136, 253, 183, 87, 209, 154, 28, 82, 51, 247, 165, 85, 103, 80, 87, 75, 44, 57, 153
    };
    const vint16m1_t *in2 = &data2[0];
    vint16m1_t out_data[] = {
    145, 47, 39, 123, 79, 207, 214, 224, 96, 148, 0, 189, 8, 55, 218, 179, 6, 174, 155, 17, 192, 156, 44, 195, 63, 219, 53, 46, 19, 57, 46, 143, 197, 164, 189, 146, 41, 197, 213, 226, 17, 84, 222, 30, 118, 22, 7, 217, 33, 226, 232, 130, 155, 55, 219, 151, 111, 32, 219, 146, 192, 92, 182, 62
    };
    vint16m1_t *out = &out_data[0];
    int masked[] = {
    1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16m1_t out = __riscv_vadd_vv_i16m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint16m1_t golden[] = {
    147, 94, 93, 390, 281, 267, 214, 224, 96, 95, 0, 189, 186, 125, 218, 179, 243, 174, 196, 17, 192, 282, 217, 152, 63, 219, 293, 46, 19, 271, 441, 143, 197, 250, 122, 146, 366, 197, 213, 169, 258, 84, 357, 275, 118, 228, 7, 217, 33, 226, 232, 268, 306, 55, 219, 239, 141, 32, 219, 157, 192, 92, 182, 62
    };
    int fail = 0;
    for (int i = 0; i < 64; i++){
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