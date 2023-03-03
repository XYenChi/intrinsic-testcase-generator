/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5605311958496252429, 8301965166083250838, 7400027008904634698, 11159470341493229241, 8734514659207477992, 3668116869452662602, 7083139854621629004, 15299473856757923586, 11560590846051373479, 16226503723312395744, 14168129592288652642, 1536935292964144390, 1676134036537975910, 17561064383095475874, 2336027246443702930, 7919606023567379842
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17963148682968562680, 984399258716333352, 3750519109895662565, 1059117806580207166, 1763197021405791334, 12564835639487230845, 15406870729919790906, 8580030898891950047, 13454024904470214610, 6987559356210726009, 12881759409228743539, 12881190538419225585, 8749075316905016630, 15042336486018057508, 16398730914134144550, 5384969192378323119
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
        out_v = __riscv_vsbc_vx_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    -12357836724472310251, 7317565907366917486, 3649507899008972133, 10100352534913022075, 6971317637801686658, -8896718770034568243, -8323730875298161902, 6719442957865973539, -1893434058418841131, 9238944367101669735, 1286370183059909103, -11344255245455081195, -7072941280367040720, 2518727897077418366, -14062703667690441620, 2534636831189056723
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
