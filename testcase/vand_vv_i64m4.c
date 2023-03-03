/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10972973616868882019, 17484414001217261921, 14798167266725132854, 4839865113586614276, 10007033196781565595, 3606071807636859251, 10471358339455043754, 14024056802675001533, 11972027555878721868, 1321844586184567153, 810332648098930039, 3302124625326464136, 7970665805179419932, 1831767230929892031, 2341402669413658058, 5907340046113602449
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    12231369354510055460, 11092451434260830113, 6055798483939463337, 17233701424227033180, 11210563472291767183, 17213936162010861261, 18382678886915690953, 1984585131920774163, 4753821504734636013, 4801675127142302222, 3728922949657540850, 15046984045342280573, 7941868964101559476, 2322124455119809883, 7110766811481185396, 18420452678689873365
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, size_t vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    12231369354510055460, 11092451434260830113, 6055798483939463337, 17233701424227033180, 11210563472291767183, 17213936162010861261, 18382678886915690953, 1984585131920774163, 4753821504734636013, 4801675127142302222, 3728922949657540850, 15046984045342280573, 7941868964101559476, 2322124455119809883, 7110766811481185396, 18420452678689873365
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
