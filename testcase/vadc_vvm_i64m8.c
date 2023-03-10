/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    878876825891744431, -8832205892178485606, -4722447290889067103, 2375647426320214406, -2496238171641838243, -1015102801005713700, 6413238238030046058, -8429895382600817746, 40378030421917431, 559902040482561587, 5860981034767408388, -2167594660197134478, 7190955783428184214, -4662904009578904487, -2273416302796004038, 8950710091945295565
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    1123694337281398429, -3026005136439421436, -5397234330451322292, 5739294496164794891, -3370664760737407954, -1643119313355859204, 5954252281858216644, 7736653203371289114, -7928833617521192789, -5377340347802556593, 8499420934569528116, 129086403466269485, -8785184353749766396, 7600477014912831107, -2031619412660360099, 7987662027621974337
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    bool8_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    2002571163173142860, -11858211028617907042, -10119681621340389394, 8114941922485009298, -5866902932379246197, -2658222114361572904, 12367490519888262702, -693242179229528632, -7888455587099275358, -4817438307319995006, 14360401969336936504, -2038508256730864992, -1594228570321582182, 2937573005333926620, -4305035715456364136, 16938372119567269902
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
