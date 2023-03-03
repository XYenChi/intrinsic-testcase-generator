/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2997938734, 3728451788, 3425884953, 4033758157, 217637002, 2968839277, 987647553, 165712428, 1473054072, 1284840072, 2894087403, 2565057188, 920249476, 3985766887, 3317406275, 2234088455
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3036846432, 3033898351, 1610469898, 3372174192, 1710166010, 3448587817, 2884684581, 2701557002, 1126992534, 3846100646, 1770835736, 3154642836, 1955331598, 385150608, 725352173, 2361725452
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
        out_v = __riscv_vrem_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    38907698, 3033898351, 1610469898, 3372174192, 186706996, 479748540, 909389475, 50158154, 1126992534, 1276420502, 1770835736, 589585648, 114832646, 385150608, 725352173, 127636997
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
