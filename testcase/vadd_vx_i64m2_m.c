/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1132570901057810786, 57821964885869897, -6008944102728276646, -1296520484831681513, -4752272790827983995, -3185094832227439872, 9108286815731787513, -2779071198689041943, 1095368123670514081, -7312391353491719033, 6601523181608634868, 2661562255501516087, -1356889325832876014, -2042631550511303096, 213663575441144825, 4009867510710052362
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -6645470611706258838, -6481494391234023193, 2833958014691090437, 434889127563629443, 2221750999358530397, -1164626179298486118, -2301300440005189485, -3434947514829040856, 3071864643385015696, -1278015704939897063, -4049089718506874229, -4848111778947497418, 7627018055786905742, -3163039457723489955, 1200645564431607948, 1408505100069386771
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0
    };
    const int64_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    12933844363061103564, 12023071647361398320, 0, 17585112716441499546, 0, 0, 6806986375726598028, 1, 4167232767055529777, 9856337015277935520, 1, 1, 0, 13241073065474758565, 1414309139872752773, 0
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
