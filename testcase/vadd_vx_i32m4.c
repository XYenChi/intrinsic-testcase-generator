/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    238, 220, 223, 121, 164, 54, 203, 45, 38, 65, 10, 4, 200, 112, 184, 65, 196, 218, 109, 43, 188, 204, 51, 22, 104, 211, 101, 251, 200, 167, 94, 172, 114, 108, 148, 50, 214, 188, 37, 155, 151, 48, 48, 248, 38, 36, 27, 217, 96, 165, 97, 211, 87, 135, 168, 112, 57, 45, 96, 154, 30, 232, 106, 41
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    87, 206, 84, 115, 160, 197, 0, 15, 185, 235, 22, 74, 44, 1, 126, 99, 195, 107, 143, 224, 218, 67, 14, 126, 118, 129, 105, 12, 86, 49, 240, 192, 166, 2, 214, 191, 244, 234, 42, 8, 38, 37, 250, 229, 99, 104, 136, 73, 245, 33, 232, 14, 75, 140, 234, 33, 248, 94, 218, 240, 210, 163, 155, 29
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[64];
    vint32m4_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vx_i32m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m4_t golden[] = {
    325, 426, 307, 236, 324, 251, 203, 60, 223, 300, 32, 78, 244, 113, 310, 164, 391, 325, 252, 267, 406, 271, 65, 148, 222, 340, 206, 263, 286, 216, 334, 364, 280, 110, 362, 241, 458, 422, 79, 163, 189, 85, 298, 477, 137, 140, 163, 290, 341, 198, 329, 225, 162, 275, 402, 145, 305, 139, 314, 394, 240, 395, 261, 70
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
