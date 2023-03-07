/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    759041785, -1268560710, 170893501, -1848757305, -1222196533, 1621843408, -2001181044, 2063564747, -902551721, 1635014961, -1140328861, 1397785687, 709640391, 409838393, -716058476, 1080933308
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -386922844, 1707437049, 1343588, 1624494070, 184452516, -623032743, 682620694, 684363578, -335527078, -1462002608, 328708824, 884012942, 1456832872, 311265026, -2075331650, 1586894256
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    110369726, -1713327011, 1860449492, 2109203611, 1652197542, 1489018904, -1649428703, -695780863, 382291980, -224599512, -136064975, -938174398, 1224569071, 1509498880, 838346979, 248810546
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    110369727, -1713327010, 1860449493, 2109203612, 1652197542, 1489018904, -1649428702, -695780862, 382291980, -224599512, -136064975, -938174398, 1224569072, 1509498880, 838346980, 248810547
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
