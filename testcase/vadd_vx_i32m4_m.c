/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    1610460234, 2577825761, 1730205743, 3671982025, 3171467090, 3999570761, 2585804286, 2374096577, 144181869, 3523890330, 1057499455, 3038164077, 4016450384, 1557758815, 654492046, 3670213330
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    1543514529, 1924450411, 259304476, 3835121127, 500720463, 2210515601, 1303887033, 1023541430, 2660813707, 2180722036, 3826618717, 1534187103, 740421270, 3101324671, 2856862825, 2005875112
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[] = {
    1136791121, 1913776761, 2842948544, 1760582043, 1617645431, 2228257422, 408518561, 1504538029, 3794923262, 810560291, 3018389606, 3922873861, 1467764260, 3712970464, 2443544969, 423793652
    };
    vint32m4_t *out = &out_data[0];
    int masked[] = {
    0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vx_i32m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m4_t golden[] = {
    1136791121, 4502276172, 1989510219, 1760582043, 3672187553, 6210086362, 3889691319, 3397638007, 3794923262, 810560291, 4884118172, 3922873861, 4756871654, 4659083486, 3511354871, 423793652
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
