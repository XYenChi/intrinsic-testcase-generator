/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3168300775, 822712381, 3994060740, 3094683053, 192615311, 2913339366, 4208673522, 3908600965, 1502147556, 524219720, 1451465136, 1771222806, 1077267118, 1326312993, 3362995997, 3954732404
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4176721407, 1672483857, 1897325540, 2507620582, 2991224345, 3314910161, 3354708953, 2798793283, 2938514181, 933085597, 3431045627, 2452154817, 1009718153, 1239993676, 1184083306, 3246373806
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, size_t vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4176721407, 1672483857, 1897325540, 2507620582, 2991224345, 3314910161, 3354708953, 2798793283, 2938514181, 933085597, 3431045627, 2452154817, 1009718153, 1239993676, 1184083306, 3246373806
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
