/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    2703015681896956569, 6598582196895962861, 16570215300563894273, 6680331829789735127, 13024881843877958261, 9396555596519320962, 14603997209093320181, 17057638635407796725, 8215762859929581014, 10185601701413621547, 12226042128003919381, 16251447143900650077, 8622347676484561769, 18254179898860740894, 15514403893562242442, 1862147506036341402
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    10994259338065618667, 3316460800443879513, 15263117807022080720, 16812975222228909851, 9765307145363818927, 12943384902675128982, 389652438044257183, 3496995578866705689, 11381331808188196268, 2928689975137649061, 12615426155740579760, 16924231160807545171, 2429845777926133490, 15987091696162238620, 3865225563744729366, 12257540629703678739
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i64m2 (data1_v, data2_v, mask, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    13697275019962575236, 9915042997339842374, 31833333107585974993, 23493307052018644978, 22790188989241777188, 22339940499194449944, 14993649647137577364, 20554634214274502414, 19597094668117777282, 13114291676551270608, 24841468283744499141, 33175678304708195248, 11052193454410695259, 34241271595022979514, 19379629457306971808, 14119688135740020141
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
