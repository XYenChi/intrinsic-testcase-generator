/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -2121033156, 996273537, -210921234, -1568030960, -1876113938, -858145560, -1953365, 1315315480, -718947725, -1492872927, 463509934, 859881216, 44124968, 299871118, 1628116256, -1746643235
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    489950227, 1861385741, 1977979787, 95865195, -1676392665, 490269249, 419258226, 190451931, 261720093, 698498336, -1475156742, 117999461, 1431529259, 1488748529, 507397764, -1832864995
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    -1612364554, 943247355, -1049134006, -833066530, 2005869605, 1108262870, -1384893033, 1907462858, 1672834147, 931121962, -1608912751, 66504138, -1111429995, 1944958343, -1920750366, 1826001886
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1612364553, 943247356, -1049134006, -833066530, 2005869606, 1108262870, -1384893033, 1907462859, 1672834148, 931121963, -1608912751, 66504139, -1111429995, 1944958344, -1920750366, 1826001886
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
