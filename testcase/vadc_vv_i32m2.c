/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3372325346, 1929028092, 1693454079, 2205461580, 2350550799, 3283891173, 624840734, 1999013586, 2000908860, 395585337, 2046197584, 2494012774, 2880186098, 2474483859, 560321386, 1393242173
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2665313201, 537439243, 3880134513, 807285960, 2255830723, 2048490025, 2780953814, 3823548513, 1464065129, 339854776, 3061573227, 2401370264, 177042198, 2959387846, 991873791, 2257718073
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i32m2 (data1_v, data2_v, mask, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    6037638547, 2466467335, 5573588592, 3012747540, 4606381522, 5332381198, 3405794548, 5822562099, 3464973989, 735440113, 5107770811, 4895383038, 3057228296, 5433871705, 1552195177, 3650960246
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
