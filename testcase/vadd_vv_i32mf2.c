/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32mf2_t data1[] = {
    94, 166, 252, 187, 131, 50, 125, 166, 218, 98, 114, 228, 19, 86, 244, 0, 82, 197, 245, 174, 27, 227, 210, 98, 242, 245, 86, 216, 235, 3, 202, 85, 33, 178, 32, 50, 57, 46, 29, 67, 106, 15, 4, 29, 96, 234, 181, 160, 80, 120, 87, 195, 205, 217, 123, 142, 194, 64, 129, 166, 99, 239, 26, 186
    };
    const vint32mf2_t *in1 = &data1[0];
    vint32mf2_t data2[] = {
    93, 254, 59, 92, 152, 96, 162, 241, 57, 201, 0, 222, 83, 75, 103, 193, 89, 158, 73, 100, 182, 106, 2, 191, 215, 136, 18, 222, 93, 183, 209, 125, 15, 207, 130, 52, 117, 130, 25, 145, 34, 64, 132, 62, 67, 95, 231, 25, 190, 126, 63, 37, 152, 151, 51, 196, 105, 208, 192, 214, 71, 77, 83, 228
    };
    const vint32mf2_t *in2 = &data2[0];
    vint32mf2_t out_data[64];
    vint32mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32mf2_t out = __riscv_vadd_vv_i32mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32mf2_t golden[] = {
    187, 420, 311, 279, 283, 146, 287, 407, 275, 299, 114, 450, 102, 161, 347, 193, 171, 355, 318, 274, 209, 333, 212, 289, 457, 381, 104, 438, 328, 186, 411, 210, 48, 385, 162, 102, 174, 176, 54, 212, 140, 79, 136, 91, 163, 329, 412, 185, 270, 246, 150, 232, 357, 368, 174, 338, 299, 272, 321, 380, 170, 316, 109, 414
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
