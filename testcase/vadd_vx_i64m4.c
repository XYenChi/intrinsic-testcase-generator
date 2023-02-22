/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    67, 209, 56, 46, 140, 166, 166, 181, 1, 148, 238, 206, 155, 92, 208, 240, 142, 150, 40, 174, 230, 143, 208, 60, 143, 226, 21, 126, 169, 22, 130, 133, 210, 78, 165, 234, 94, 119, 44, 177, 234, 145, 191, 49, 145, 150, 160, 231, 19, 199, 157, 219, 144, 25, 247, 139, 73, 88, 218, 104, 174, 39, 117, 209
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    121, 50, 18, 46, 189, 222, 222, 166, 163, 56, 16, 218, 194, 100, 138, 39, 160, 74, 213, 230, 246, 51, 239, 30, 224, 76, 120, 74, 153, 195, 75, 194, 174, 27, 14, 99, 237, 114, 67, 91, 100, 153, 5, 22, 187, 129, 248, 250, 166, 149, 182, 215, 250, 136, 171, 3, 32, 246, 3, 64, 227, 12, 98, 206
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[64];
    vint64m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vx_i64m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m4_t golden[] = {
    188, 259, 74, 92, 329, 388, 388, 347, 164, 204, 254, 424, 349, 192, 346, 279, 302, 224, 253, 404, 476, 194, 447, 90, 367, 302, 141, 200, 322, 217, 205, 327, 384, 105, 179, 333, 331, 233, 111, 268, 334, 298, 196, 71, 332, 279, 408, 481, 185, 348, 339, 434, 394, 161, 418, 142, 105, 334, 221, 168, 401, 51, 215, 415
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