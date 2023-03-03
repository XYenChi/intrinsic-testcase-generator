/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    14705937595587235722, 10680228896131674449, 10242965844273376226, 6963479935965487229, 17755714278226390978, 11685420419787080483, 5734876671136263365, 17529229361803870072, 9440916024057977183, 1170746445063478523, 16776439033217103827, 8722437896056699161, 10726201901268644698, 6968945212711206031, 3430764088234767502, 13622481796713301824
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    1595833737004188216, 8477153334726211776, 15276980413612399522, 552303343696719395, 2336948844760337806, 15019980885671370966, 11018121103392975614, 396511701787530743, 1274062794423566077, 7522350581751024405, 8444394800549732635, 12119459431284010714, 3156809494635476794, 15973453493920812553, 6582949610710984940, 3677463930904567790
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
        out_v = __riscv_vdiv_vv_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 0, 6, 0, 1, 0, 2, 1, 0
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
