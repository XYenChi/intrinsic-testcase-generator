/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    55569526, 668252849, 2618268377, 2911413944, 137635165, 3068564561, 1006721356, 662141549, 2231580311, 3868982214, 655683151, 2741519771, 371982362, 3397736741, 3583067199, 375148384
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1065360766, 401991731, 3909339863, 1171519259, 3365532973, 307971909, 3404207734, 178546682, 145105320, 271894612, 3173194846, 3008506897, 4048702693, 3355748272, 2490127472, 3598502623
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    9539772, 401991731, 1291071486, 1171519259, 62289013, 307971909, 384043666, 178546682, 145105320, 271894612, 550462242, 266987126, 328879073, 3355748272, 2490127472, 222167167
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
