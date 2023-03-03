/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2414000533, 1593005641, 989529576, 3340931090, 1986666112, 1987367280, 1051244799, 3262610770, 507424207, 1677754745, 3131017318, 2153560509, 3907772696, 2620273926, 3509190659, 295920808
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1932220306, 2671646454, 2653210901, 1656953726, 905160381, 1017762844, 1635208895, 1954373889, 3525383657, 2334880995, 3176921127, 2222295386, 4215830581, 1583033098, 1844751181, 3602744859
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3937555828, 3832184296, 2125331791, 1300862670, 4275381248, 1525223590, 1176885500, 1637825694, 1981949742, 2760932918, 3769011595, 1588538524, 3787494665, 2985668204, 72713422, 1150949252
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4346220839, 4264652096, 3642740477, 4997884816, 2891826494, 3005130124, 2686453694, 5216984660, 4032807865, 4012635740, 6307938445, 4375855895, 8123603278, 4203307025, 5353941840, 3898665668
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
