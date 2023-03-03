/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    586225868, 709412728, 1601029087, 2071821868, 4057248884, 2250471396, 2181009636, 1025313807, 2381751903, 1967045463, 361769464, 1300965, 1466497712, 3018353916, 3962567531, 3111713381
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    847746128, 497808890, 331158025, 469393055, 1959849991, 2074985213, 4011703078, 3255958696, 877922519, 3869632329, 4250603811, 454609382, 2877794248, 1687916000, 3832267988, 3235161019
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1144446978, 3403536274, 1798646740, 3340762596, 1917628635, 533606812, 3644298778, 2399765570, 2666673804, 333069226, 2339456181, 1301415352, 4238979063, 1324991654, 941883582, 1858781863
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    670904423058026905, 2414511952985295473, 2879685747977726381, 6921465002189249328, 7780296639280193340, 1200866867116749553, 7948250751281024808, 2460512772484224990, 6351355407357249013, 655162309868221638, 846343808651856985, 1693095823414681, 6216453097105403856, 3999293747518217065, 3732277300015176042, 5783996395457208804
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
