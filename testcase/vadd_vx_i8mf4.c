/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf4_t data1[] = {
    213, 195, 161, 245, 16, 74, 153, 151, 87, 197, 175, 83, 167, 235, 177, 137, 250, 1, 55, 249, 132, 155, 215, 12, 229, 122, 250, 73, 253, 220, 9, 150, 121, 14, 194, 62, 87, 181, 140, 158, 210, 109, 84, 127, 144, 105, 38, 91, 208, 191, 172, 182, 135, 112, 240, 148, 75, 191, 136, 45, 59, 70, 15, 238
    };
    const vint8mf4_t *in1 = &data1[0];
    vint8mf4_t data2[] = {
    233, 78, 115, 82, 237, 76, 61, 113, 53, 229, 27, 213, 244, 57, 92, 171, 224, 242, 85, 98, 54, 154, 238, 126, 185, 229, 218, 16, 254, 152, 236, 207, 85, 63, 1, 124, 243, 214, 22, 255, 60, 48, 37, 236, 201, 232, 133, 221, 22, 101, 7, 26, 68, 91, 70, 215, 97, 116, 198, 219, 151, 117, 74, 34
    };
    const vint8mf4_t *in2 = &data2[0];
    vint8mf4_t out_data[64];
    vint8mf4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf4_t out = __riscv_vadd_vx_i8mf4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf4_t golden[] = {
    446, 273, 276, 327, 253, 150, 214, 264, 140, 426, 202, 296, 411, 292, 269, 308, 474, 243, 140, 347, 186, 309, 453, 138, 414, 351, 468, 89, 507, 372, 245, 357, 206, 77, 195, 186, 330, 395, 162, 413, 270, 157, 121, 363, 345, 337, 171, 312, 230, 292, 179, 208, 203, 203, 310, 363, 172, 307, 334, 264, 210, 187, 89, 272
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
