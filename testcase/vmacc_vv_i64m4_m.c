/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    12306249183804592812, 13091340388817051804, 6833270359024990718, 1333326431113467159, 13650078398282683119, 10958998162021589172, 4760874730774586823, 13197810092387726446, 11372589320839995049, 11000935660955711575, 15059577635067320948, 3407284521151115070, 13863675816177279617, 12259420557216143832, 6100024199393058264, 4833909698383327993
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    16549105207515899057, 4504331237948497907, 3770900221576729244, 15855022678399645391, 9375640464281448250, 80990145651846779, 13733275957055690369, 2502996804910977518, 15499021770435070357, 8096163780629881849, 10490688073015785442, 7260425151372881299, 13817865747416038594, 17086549536196951225, 16453610498104398272, 12699896951077672501
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int out_data[] = {
    10362354110353489497, 11269011299551519643, 14202826485346282919, 7471212227057619108, 6622372374285238785, 11687761353413420415, 8441253508161276369, 15620442572153832369, 11326145368946071880, 2777496967667883202, 8103144426748387631, 6257119953799638345, 13122115608251083997, 7006530697674769154, 10489067865523787790, 16052352348556922110
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, *in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i64m4_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse64m4_v_i64 (vbool64_t mask, int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    127521711812831797596244403379403695565, 147526462767854541400776194999254585973, 97051753236691841752728918009776945842, 9961564734794034142317334517488874172, 90395902091614941507342653125403570416, 128086155190204635844272072350447746380, 40187750523067353166742503004288685687, 206155634626334745699512771937712130574, 128807599869157462752609300327198122120, 30555065439813969355124380051899463150, 122029932582780425504707850697790394189, 21319787965567287988133386859479359150, 181920756815192966894253990762822989149, 85896006469840035460798156872660958129, 63983567808771198135341695689441796561, 77595621699555698101260784178683625230
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
