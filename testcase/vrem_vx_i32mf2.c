/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    134442653, 3591556021, 1708677085, 2346233680, 1667126508, 3196746943, 360465986, 1474154891, 3877071308, 2473770809, 3850161499, 3678288686, 611002720, 3189697398, 2414500693, 2757868192
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    248631604, 1009963699, 504971728, 3797226216, 3494863949, 4120440709, 1728244692, 1119104439, 2910737223, 1001581143, 1739238889, 1011569194, 885749111, 2297611908, 3118749111, 3387905268
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    114188951, 1009963699, 504971728, 1450992536, 160610933, 923693766, 286380748, 1119104439, 2910737223, 1001581143, 1739238889, 1011569194, 274746391, 2297611908, 704248418, 630037076
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
