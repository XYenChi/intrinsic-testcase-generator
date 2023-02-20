/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    172, 165, 201, 133, 74, 225, 29, 176, 97, 114, 236, 129, 204, 241, 106, 209, 89, 233, 120, 86, 163, 125, 16, 124, 50, 140, 147, 116, 237, 17, 40, 205, 100, 223, 104, 174, 215, 189, 74, 170, 231, 170, 93, 250, 91, 117, 53, 85, 113, 209, 56, 169, 133, 236, 38, 14, 141, 9, 156, 126, 159, 176, 228, 15
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    177, 76, 83, 43, 165, 230, 61, 54, 220, 232, 20, 100, 114, 217, 145, 61, 39, 99, 124, 29, 145, 64, 122, 228, 8, 119, 105, 44, 101, 69, 39, 128, 139, 1, 160, 167, 147, 188, 125, 64, 129, 231, 168, 15, 71, 197, 209, 20, 48, 94, 197, 186, 31, 230, 124, 204, 198, 152, 179, 82, 141, 189, 73, 242
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[64];
    vint16mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vx_i16mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf2_t golden[] = {
    349, 241, 284, 176, 239, 455, 90, 230, 317, 346, 256, 229, 318, 458, 251, 270, 128, 332, 244, 115, 308, 189, 138, 352, 58, 259, 252, 160, 338, 86, 79, 333, 239, 224, 264, 341, 362, 377, 199, 234, 360, 401, 261, 265, 162, 314, 262, 105, 161, 303, 253, 355, 164, 466, 162, 218, 339, 161, 335, 208, 300, 365, 301, 257
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
