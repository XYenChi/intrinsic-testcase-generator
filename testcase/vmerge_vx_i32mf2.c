/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3033821313, 3782153294, 2597645618, 2104522764, 1987183743, 665497646, 644689437, 2500221825, 2177961506, 3917316167, 606239397, 4152111385, 3370281683, 3675470286, 1194787287, 1460256527
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1114280806, 2016840999, 4168064204, 4063161558, 3864719366, 1418786905, 2564708812, 3194098997, 862244015, 86858924, 1222558741, 1680408344, 3275127794, 1507282894, 4287103874, 3534697269
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    bool64_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i32mf2 (data1_v, data2_v, size_t vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3033821313, 2016840999, 4168064204, 2104522764, 3864719366, 665497646, 644689437, 2500221825, 862244015, 86858924, 1222558741, 4152111385, 3275127794, 3675470286, 4287103874, 3534697269
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
