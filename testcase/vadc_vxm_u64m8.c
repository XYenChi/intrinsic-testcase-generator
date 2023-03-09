/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    9245230130012672064, 2071076502357927910, 8391886663680343439, 5869314919721991080, 12999369556131582766, 17197205926342160182, 14912631135301257616, 5838816117243517441, 11631742919942914700, 5525922967626669795, 18146175562445621974, 5104822097029797693, 2480337316733918126, 10144668333468516441, 982061698710175055, 3584037563467807975
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4897369671662076650, 7728434970632346825, 15571820077137080457, 9969971975857794052, 4203316797134504782, 3729916038756776564, 4471592272432078877, 4280930776462478787, 7742219671961571771, 12653015161200009404, 4893651268534539556, 11523504335211468828, 15658096039247786027, 15733655000853508873, 12601448608891965291, 12424016251566502411
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    bool8_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    14142599801674748714, 9799511472990274735, 23963706740817423897, 15839286895579785133, 17202686353266087548, 20927121965098936746, 19384223407733336494, 10119746893705996228, 19373962591904486472, 18178938128826679200, 23039826830980161531, 16628326432241266522, 18138433355981704154, 25878323334322025315, 13583510307602140346, 16008053815034310387
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
