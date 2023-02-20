/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    252, 19, 57, 216, 131, 155, 1, 97, 47, 108, 152, 171, 254, 247, 83, 222, 176, 132, 45, 158, 182, 29, 109, 78, 143, 223, 132, 212, 7, 219, 163, 120, 197, 219, 168, 52, 128, 5, 45, 22, 237, 175, 189, 245, 244, 210, 115, 160, 46, 196, 51, 190, 123, 132, 193, 234, 194, 221, 1, 174, 161, 217, 126, 126
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    77, 54, 198, 132, 165, 52, 3, 100, 214, 152, 1, 136, 166, 83, 241, 4, 227, 77, 96, 122, 171, 46, 251, 51, 250, 40, 94, 143, 15, 60, 26, 48, 3, 92, 224, 156, 105, 18, 209, 12, 36, 146, 55, 12, 158, 71, 92, 120, 239, 208, 106, 101, 139, 112, 169, 101, 222, 55, 89, 31, 193, 190, 27, 208
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[] = {
    220, 19, 145, 123, 100, 121, 224, 54, 188, 147, 126, 35, 82, 55, 245, 8, 119, 37, 234, 47, 123, 4, 170, 158, 30, 142, 100, 60, 195, 104, 89, 158, 240, 112, 208, 112, 93, 107, 238, 192, 201, 145, 205, 187, 78, 114, 205, 138, 14, 16, 25, 135, 144, 224, 162, 170, 176, 182, 8, 131, 74, 157, 69, 183
    };
    vint64m2_t *out = &out_data[0];
    int masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vv_i64m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m2_t golden[] = {
    220, 73, 255, 123, 100, 207, 224, 54, 261, 260, 126, 35, 82, 55, 324, 226, 403, 209, 234, 280, 123, 75, 360, 158, 30, 142, 100, 60, 22, 104, 89, 168, 240, 311, 208, 208, 233, 107, 238, 192, 201, 321, 244, 187, 78, 281, 205, 138, 14, 404, 157, 135, 144, 244, 362, 335, 416, 276, 8, 131, 354, 157, 153, 183
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
