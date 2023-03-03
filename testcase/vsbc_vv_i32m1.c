/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2266723609, 1211166943, 3414835207, 1313332512, 3831136601, 331169040, 3525771934, 2717427622, 1487527375, 2412800938, 399868252, 1320561063, 3895959469, 3678130016, 2674252576, 3559362576
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1061603413, 2266588835, 4122080634, 448259180, 1633838260, 1163584485, 4040392943, 1558878105, 2245517068, 1561848584, 1098180326, 3838897831, 239992653, 2381334020, 1201096945, 2847193558
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1205120196, -1055421892, -707245427, 865073332, 2197298341, -832415445, -514621009, 1158549517, -757989693, 850952354, -698312074, -2518336768, 3655966816, 1296795996, 1473155631, 712169018
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
