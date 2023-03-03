/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1830634190, 2175974700, 1321969685, 1383656448, 3671496989, 1395162781, 449665649, 960343573, 1206193643, 1008964597, 3408303873, 1515970544, 1619888681, 1637371836, 3574788965, 1944585970
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1936149178, 1753044839, 4229111240, 2727616938, 3140095085, 2660593655, 3111713158, 2880028696, 1327090564, 1500622052, 2421948354, 2543206822, 1773300925, 3633830707, 2921332077, 2753020582
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    2759450814, 656052361, 1301453254, 1212160551, 2111661171, 265143182, 4013187202, 1767834408, 270161151, 971520235, 374846652, 3604028608, 3841469728, 2506988188, 3053181316, 2849487539
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2759450814, 1753044839, 4229111240, 1212160551, 2111661171, 2660593655, 4013187202, 1767834408, 270161151, 971520235, 2421948354, 3604028608, 3841469728, 2506988188, 3053181316, 2753020582
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
