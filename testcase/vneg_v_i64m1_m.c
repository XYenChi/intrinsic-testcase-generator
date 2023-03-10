/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -5980154020698565398, 1377259077264288687, 2245650463616490090, 4350491344701134192, -7460282584021762879, -3652155131873040630, 4075912331232075280, -7356977097871978044, -2444158064431048464, -1732744847606837100, -9077479795135779645, 2720750292375129398, 6812370901988138408, -6968153576015755681, -1902480997384223434, -6232407375559403918
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    -767329858435365921, 3845349990105752494, 7478674232341734863, 6184482335423853080, 3528293294539215716, 3587407097744617699, 158495351753722503, 6584037596591031841, -3593788691661450675, 8204961190220047774, -1443300822157853707, -674506740512820265, -6937758861611143645, -8861432275276089508, -2859459213762069425, 387005968400545177
    };
    const int64_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, in1, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m1 (mask, data1_v, vl);
        void __riscv_vse64_v_i64m1 (bool64_t mask, int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    5980154020698565398, -1377259077264288687, -2245650463616490090, -4350491344701134192, 7460282584021762879, 3652155131873040630, -4075912331232075280, 7356977097871978044, 2444158064431048464, 1732744847606837100, 9077479795135779645, -2720750292375129398, -6812370901988138408, 6968153576015755681, 1902480997384223434, 6232407375559403918
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
