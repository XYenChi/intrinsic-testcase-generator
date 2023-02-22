/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf8_t data1[] = {
    53, 249, 92, 236, 51, 92, 205, 74, 162, 30, 124, 109, 42, 221, 127, 45, 93, 225, 203, 159, 237, 7, 251, 239, 70, 17, 142, 45, 119, 152, 75, 118, 70, 214, 23, 171, 244, 190, 77, 213, 70, 200, 8, 158, 79, 194, 133, 164, 161, 53, 152, 77, 196, 113, 65, 186, 22, 66, 149, 79, 141, 8, 183, 182
    };
    const vint8mf8_t *in1 = &data1[0];
    vint8mf8_t data2[] = {
    194, 120, 11, 72, 179, 33, 180, 116, 196, 144, 210, 0, 149, 173, 5, 183, 65, 108, 121, 218, 146, 177, 210, 77, 156, 34, 49, 236, 80, 31, 196, 129, 32, 67, 51, 127, 61, 65, 189, 169, 60, 139, 51, 139, 58, 156, 158, 182, 117, 44, 158, 66, 140, 175, 180, 9, 175, 26, 18, 241, 16, 124, 111, 17
    };
    const vint8mf8_t *in2 = &data2[0];
    vint8mf8_t out_data[] = {
    228, 49, 50, 177, 56, 16, 153, 104, 222, 168, 134, 181, 91, 4, 215, 139, 245, 103, 134, 30, 208, 213, 48, 255, 54, 174, 18, 50, 193, 18, 246, 42, 59, 101, 39, 117, 36, 138, 198, 7, 220, 189, 248, 231, 70, 164, 140, 1, 60, 160, 12, 192, 166, 119, 151, 210, 194, 237, 80, 106, 14, 14, 245, 191
    };
    vint8mf8_t *out = &out_data[0];
    int masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf8_t out = __riscv_vadd_vv_i8mf8_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint8mf8_t golden[] = {
    247, 49, 50, 177, 56, 16, 153, 190, 358, 168, 334, 109, 191, 4, 215, 228, 158, 103, 134, 30, 383, 184, 48, 316, 226, 51, 191, 281, 193, 18, 271, 42, 102, 281, 39, 298, 36, 255, 266, 7, 220, 339, 248, 231, 70, 350, 140, 1, 60, 97, 12, 143, 166, 119, 245, 195, 197, 237, 80, 106, 157, 132, 294, 191
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