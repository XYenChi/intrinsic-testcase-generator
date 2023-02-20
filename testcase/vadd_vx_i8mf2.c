/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint8mf2_t data1[] = {
    225, 130, 84, 64, 203, 73, 178, 128, 96, 206, 13, 31, 48, 255, 222, 173, 253, 152, 221, 178, 99, 0, 255, 215, 181, 169, 190, 90, 237, 38, 168, 170, 37, 198, 172, 6, 231, 6, 250, 17, 195, 162, 132, 64, 109, 78, 254, 129, 148, 219, 38, 240, 38, 224, 69, 237, 98, 211, 130, 197, 64, 108, 91, 151
    };
    const vint8mf2_t *in1 = &data1[0];
    vint8mf2_t data2[] = {
    26, 212, 164, 15, 55, 213, 242, 158, 51, 215, 115, 93, 79, 109, 153, 36, 117, 140, 83, 249, 191, 65, 255, 249, 227, 159, 21, 19, 236, 67, 238, 143, 96, 134, 117, 29, 208, 178, 225, 146, 170, 37, 30, 151, 207, 75, 98, 247, 183, 228, 173, 55, 33, 91, 85, 221, 124, 163, 62, 239, 218, 158, 184, 232
    };
    const vint8mf2_t *in2 = &data2[0];
    vint8mf2_t out_data[64];
    vint8mf2_t *out = &out_data[0];
    for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
        vint8mf2_t out = __riscv_vadd_vx_i8mf2 (data1, data2, 64);
)        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint8mf2_t golden[] = {
    251, 342, 248, 79, 258, 286, 420, 286, 147, 421, 128, 124, 127, 364, 375, 209, 370, 292, 304, 427, 290, 65, 510, 464, 408, 328, 211, 109, 473, 105, 406, 313, 133, 332, 289, 35, 439, 184, 475, 163, 365, 199, 162, 215, 316, 153, 352, 376, 331, 447, 211, 295, 71, 315, 154, 458, 222, 374, 192, 436, 282, 266, 275, 383
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
