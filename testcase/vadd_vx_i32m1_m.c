/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1663478849, -1659085865, -326075274, 946654513, 1656570451, -756467975, 463466733, -136007151, 14723962, 426276200, 644008773, -234828996, -1349800225, -1781116094, -1349265214, -407118416
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1579762546, 1563067117, 1835835400, 1137890154, 233487511, -806804070, -1699430300, -863734527, 1174200714, -1209974977, -1295269659, -1114495611, -2081522421, -1706102363, -1041102038, 1234302324
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    1977233365, -429908251, 1652374299, 1111339225, -525808625, -2016628053, 1199434296, -656373549, -647660332, 2122107646, -792074817, -952454853, 1735316866, -1441992420, 1396429296, 1318502474
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1977233366, -429908250, 1652374299, 1111339225, -525808625, -2016628052, 1199434297, -656373549, -647660331, 2122107647, -792074817, -952454853, 1735316866, -1441992419, 1396429296, 1318502475
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
