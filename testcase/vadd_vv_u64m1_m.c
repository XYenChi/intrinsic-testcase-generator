/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    11548801622194408619, 13602980036179478279, 6277276712346984801, 12900542842638196558, 14670067146379014522, 11106050306102838921, 16650605228182842178, 13792658266820263170, 6855496626866958822, 8775615430621070210, 6813867527480637399, 146433528593659675, 357347513488193128, 1106968765497771972, 13245465414128283295, 866843899438748953
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    11072272861647299837, 9627748205943636977, 10629409421301301781, 3783292380595951853, 14041670856463109453, 2812922512054572352, 17941858052117641644, 10356125734142043056, 15693175933640652454, 4429819412052393886, 13855818739208084157, 4597490755850176336, 15343531185435956685, 9908853066885667172, 5819290258068870874, 12509037570286520745
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1 (in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    4174330410132156840, 4783984168413563640, 16906686133648286582, 16683835223234148411, 1, 0, 0, 0, 1, 13205434842673464096, 2222942192979169940, 1, 1, 1, 618011598487602553, 1
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
