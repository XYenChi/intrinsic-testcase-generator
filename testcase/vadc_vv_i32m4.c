/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3108060785, 3702737659, 2444797716, 2289336790, 505562229, 483378028, 1544683474, 4077968061, 3870790822, 1996567703, 2358029672, 4145902877, 2612779757, 3904138760, 3914276546, 1528392587
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1888279935, 3782584326, 3616770939, 1583759831, 2328186594, 913448880, 1561660168, 1656148522, 3620639949, 2992404497, 3364687972, 1487559729, 3851277899, 928900242, 3451155983, 3289938417
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i32m4 (data1_v, data2_v, mask, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4996340720, 7485321985, 6061568655, 3873096621, 2833748823, 1396826908, 3106343642, 5734116583, 7491430771, 4988972200, 5722717644, 5633462606, 6464057656, 4833039002, 7365432529, 4818331004
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
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
}
