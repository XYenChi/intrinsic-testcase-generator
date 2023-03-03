/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    12708723638705514497, 10204238980198745172, 13053344679959516825, 11002070577398105105, 1063096970035421604, 5105110850026342350, 9257310021567134778, 7463026287546499612, 1530961412852658354, 3363517781486438074, 12512085785411118696, 12812976373874184247, 3460771665256987674, 4049306774260997108, 11772453835329603491, 11352814655569803331
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    16264494815931843510, 903313220054810898, 7749532339876841224, 6364750946623725839, 5885781925483768862, 1296511037537205181, 12511545257175495571, 9077761745340004827, 17895543262083531630, 3237064749628654928, 13599338236587670857, 14821686749073926642, 18054227303125035534, 14687229368030580877, 5787089278489766413, 16033193356882345976
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i64m1 (data1_v, data2_v, mask, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    28973218454637358007, 11107552200253556070, 20802877019836358049, 17366821524021830944, 6948878895519190466, 6401621887563547531, 21768855278742630349, 16540788032886504439, 19426504674936189984, 6600582531115093002, 26111424021998789553, 27634663122948110889, 21514998968382023208, 18736536142291577985, 17559543113819369904, 27386008012452149307
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
