/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7500329074060402271, 322392363744597038, -2342869238520454293, 6605594444097073414, -1974899023670471216, -458639861895295431, 4201324118281383149, -3646957617826392741, -806622542728619082, -605311740931388128, 6707142477401110945, -3851150605297459969, -4087651391942986743, 7347667679965406560, -994523695470185686, 923984046403827111
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_i64m2 (src, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -7500329074060402271, 322392363744597038, -2342869238520454293, 6605594444097073414, -1974899023670471216, -458639861895295431, 4201324118281383149, -3646957617826392741, -806622542728619082, -605311740931388128, 6707142477401110945, -3851150605297459969, -4087651391942986743, 7347667679965406560, -994523695470185686, 923984046403827111
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
