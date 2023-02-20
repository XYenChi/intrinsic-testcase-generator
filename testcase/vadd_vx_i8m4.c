/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8m4_t data1[] = {
    159, 185, 207, 87, 200, 72, 45, 226, 87, 232, 193, 181, 155, 45, 237, 153, 114, 23, 80, 231, 67, 201, 144, 115, 48, 115, 209, 65, 104, 176, 91, 7, 4, 143, 67, 119, 43, 102, 126, 251, 41, 15, 48, 147, 72, 111, 220, 161, 237, 30, 229, 236, 121, 176, 223, 164, 241, 248, 142, 231, 149, 85, 101, 89
    };
    const vint8m4_t *in1 = &data1[0];
    vint8m4_t data2[] = {
    197, 194, 72, 82, 107, 91, 187, 24, 167, 206, 92, 12, 233, 228, 7, 168, 129, 25, 62, 42, 218, 114, 133, 41, 87, 28, 80, 48, 178, 106, 172, 69, 162, 191, 194, 101, 153, 246, 126, 42, 145, 63, 80, 128, 32, 131, 52, 39, 251, 76, 229, 97, 31, 130, 151, 65, 81, 126, 178, 110, 24, 25, 156, 169
    };
    const vint8m4_t *in2 = &data2[0];
    vint8m4_t out_data[64];
    vint8m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8m4_t out = __riscv_vadd_vx_i8m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8m4_t golden[] = {
    356, 379, 279, 169, 307, 163, 232, 250, 254, 438, 285, 193, 388, 273, 244, 321, 243, 48, 142, 273, 285, 315, 277, 156, 135, 143, 289, 113, 282, 282, 263, 76, 166, 334, 261, 220, 196, 348, 252, 293, 186, 78, 128, 275, 104, 242, 272, 200, 488, 106, 458, 333, 152, 306, 374, 229, 322, 374, 320, 341, 173, 110, 257, 258
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
