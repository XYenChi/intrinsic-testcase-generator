/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    2719825845, 3803399946, 667463842, 1705004735, 4276826119, 2256034765, 2067387088, 3491500674, 3828751203, 835045427, 559490023, 2734519288, 3859905694, 70221486, 2889968827, 3701929789
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    2018940962, 2620516724, 1631152087, 1466216965, 236297134, 1083958059, 3770637260, 3328279833, 2087603677, 2181442793, 1662823677, 788314929, 377905857, 2843349752, 4265639212, 2782366311
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[] = {
    1968799211, 2428489628, 1639576382, 991023130, 861469747, 3158987030, 1699757651, 1829731714, 4202211294, 704262706, 520872736, 2365080977, 2067888116, 194177604, 1352339249, 3942572790
    };
    vint32m4_t *out = &out_data[0];
    int masked[] = {
    1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 16, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vv_i32m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m4_t golden[] = {
    4738766807, 2428489628, 2298615929, 3171221700, 861469747, 3158987030, 5838024348, 1829731714, 5916354880, 704262706, 2222313700, 3522834217, 2067888116, 2913571238, 1352339249, 3942572790
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
