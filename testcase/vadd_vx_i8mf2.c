/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    207, 61, 64, 22, 205, 251, 61, 24, 36, 154, 163, 56, 200, 52, 190, 67, 186, 6, 188, 243, 3, 245, 46, 210, 47, 133, 31, 72, 12, 77, 41, 116, 230, 152, 33, 211, 48, 27, 187, 164, 72, 57, 166, 65, 206, 28, 253, 181, 137, 214, 84, 117, 42, 160, 147, 210, 162, 127, 81, 28, 62, 212, 212, 2
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    37, 92, 152, 117, 24, 66, 163, 121, 106, 134, 128, 77, 12, 69, 17, 7, 45, 198, 210, 228, 125, 81, 186, 128, 151, 64, 150, 182, 20, 135, 237, 183, 181, 96, 176, 210, 149, 73, 105, 55, 177, 63, 6, 223, 236, 203, 141, 125, 228, 116, 25, 151, 174, 131, 182, 164, 107, 185, 252, 219, 171, 122, 142, 171
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[64];
    vint8mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vx_i8mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf2_t golden[] = {
    244, 153, 216, 139, 229, 317, 224, 145, 142, 288, 291, 133, 212, 121, 207, 74, 231, 204, 398, 471, 128, 326, 232, 338, 198, 197, 181, 254, 32, 212, 278, 299, 411, 248, 209, 421, 197, 100, 292, 219, 249, 120, 172, 288, 442, 231, 394, 306, 365, 330, 109, 268, 216, 291, 329, 374, 269, 312, 333, 247, 233, 334, 354, 173
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
