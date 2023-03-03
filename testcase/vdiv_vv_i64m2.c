/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    12332186689523260080, 2767352692923590813, 16625019344039311938, 8118159332657664738, 14170344974476671851, 6222852070413231500, 2584239563455672225, 13596748598757266683, 13995631710760895507, 6105857902853036955, 6155720018450534066, 3700602524696226284, 2855572417567715008, 2232057368601497160, 5562876317933564676, 2828083717035799247
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4654932945227657390, 9059140804200495335, 8876244528232578659, 3180480466222610456, 17579993460775499913, 2366430143823352144, 2081652531738837975, 5424275629998484865, 1793731020803024000, 12130536306528565679, 16726167494819301163, 148786594335591621, 10358133290604995730, 211656379638610431, 12277873582470795814, 11146227524310305377
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i64m2 (data1_v, data2_v, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 3, 0, 0, 1, 0, 0, 0, 0, 1, 2, 0, 3, 0, 2, 3
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
