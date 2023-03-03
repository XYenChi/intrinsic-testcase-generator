/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2515582263, 1223492543, 1476971786, 3281364790, 3483252853, 2721164110, 1013194565, 3079231773, 4094213842, 3494344110, 386018257, 2005036464, 869237307, 198213312, 1413062520, 1772148619
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    516734591, 841554450, 2996925224, 698518093, 2749737533, 2701838286, 927979115, 353672384, 773912994, 276081155, 69573305, 2717444352, 4086848734, 3763514405, 661811337, 2421518910
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    221588866, 732220761, 2470398535, 855868002, 4177321629, 3443249904, 2585125679, 700096794, 2959744112, 158348421, 2745806263, 4107308011, 2969062595, 3065357065, 279158320, 334905612
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    221588866, 1029635594103466350, 4426374000599730064, 2292092675548145470, 4177321629, 7352145374887115460, 940223395751509975, 700096794, 3168565292538462948, 964722557856247050, 2745806263, 5448575014650851328, 3552441387658519338, 3065357065, 279158320, 334905612
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
