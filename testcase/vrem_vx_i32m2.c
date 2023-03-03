/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1482462116, 907622537, 304186544, 878460628, 3745474386, 1206758751, 211656882, 1549708828, 3667635567, 3778698773, 654778352, 1384662653, 2310454883, 487975175, 436688425, 2676289248
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3655716087, 4247035770, 3070296569, 454732255, 1127032210, 1418863760, 3457870792, 3075101335, 710109261, 2043370170, 3765365165, 1081570315, 4082328084, 1140586635, 875099573, 2143050617
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
        out_v = __riscv_vrem_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    690791855, 616545622, 28431129, 454732255, 1127032210, 212105009, 71360680, 1525392507, 710109261, 2043370170, 491473405, 1081570315, 1771873201, 164636285, 1722723, 2143050617
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
