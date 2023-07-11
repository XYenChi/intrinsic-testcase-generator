/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -1493419290600917414, 2559260547140922187, 2696314222661389108, -8985091591094387847, 1840178772741344189, -1669346685671757463, 2341526578931386827, 3987718921416401652, 5380913081282073329, 6482405735027203709, -3197903111731746656, -1266814772275544440, 8204252350874824447, -7990554504373885971, 6837787940238709399, 6996825720150247356
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -8208277670604465465, -8350344863410983698, 2380094590065925214, 7101521264176734316, 6622260539246045477, -2320513036079736064, 5646499831448153540, -1887977296446804429, 287120029001050375, -732869829520789927, 6695437862392718934, -7993022492228866510, 3807475851027673452, -3385466248408854631, -4319930766488915563, -1484264946779257686
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int out_data[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1
    };
    const int64_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const uint16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    8745047112504168737, 12655659757439490105, 1, 1, 8462439311987389666, 14456884351958058089, 0, 2099741624969597223, 5668033110283123704, 1, 3497534750660972278, 1, 1, 7070723320926811014, 1, 1
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
