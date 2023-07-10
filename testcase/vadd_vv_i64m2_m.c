/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    4929956773752793081, 8534999337924366713, -8709040678093001175, -6015618613734420296, -3588764478063630569, -8722106262254911054, 1438675596771097112, 9059288608261876973, -2432773132630032777, 4730813607643838420, -4937959120441917947, -6355853065603677933, -5571630661991186334, 5043050514626101282, 2164499185191367197, 7408776021136210481
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -1800296766112350044, 8270151294296293710, -704326516372926073, 6524060444648352633, -7776643854333111058, -7630598914724316642, -6112056722038016700, 1376114141043334143, 7721825102201806863, -3604861388640384591, 7971833416527948712, 2400503120384643173, -4058283630048713619, 7234438089428568581, 8072213500048023633, -1895897055330772918
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1
    };
    const int64_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0
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
    3129660007640443037, 1, 0, 0, 1, 2094038896730323920, 13773362948442632028, 0, 5289051969571774086, 1, 1, 1, 8816829781669651663, 12277488604054669863, 0, 1
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
