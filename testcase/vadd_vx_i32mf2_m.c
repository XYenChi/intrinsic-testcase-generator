/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3235682935, 370179289, 2374029274, 3231032098, 297668464, 2479741648, 3585511994, 848802370, 1011256445, 2568174087, 747557375, 2197177157, 87854520, 3384387727, 4051886165, 1442574075
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    219372177, 1915268723, 2690235667, 56055338, 3108031242, 1158309495, 864980509, 1577171704, 2285411406, 3818859684, 1598428330, 1112738992, 2389824377, 509764623, 2088578593, 2791204081
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    2478596176, 518418544, 135358856, 472131427, 1855868356, 2659031821, 3532995912, 1281107561, 2477300001, 3133654655, 4181132394, 1455843856, 562127365, 1256061419, 1656204407, 4059957653
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3455055112, 2285448012, 5064264941, 3287087436, 3405699706, 3638051143, 3532995912, 1281107561, 3296667851, 3133654655, 2345985705, 3309916149, 562127365, 1256061419, 1656204407, 4059957653
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
