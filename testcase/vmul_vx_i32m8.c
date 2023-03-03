/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1946453425, 3506398162, 870186219, 4071009702, 3329294144, 3250164093, 2185847472, 2320127172, 4028383289, 3512003723, 4120347341, 125521442, 198977725, 495406443, 1635790197, 1334278684
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3886976159, 2352051252, 1306581661, 2617417486, 773988637, 3680610351, 2027729045, 2571351883, 1688116814, 545312590, 2678964298, 1927210588, 27752257, 534592316, 47604203, 452067355
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    7565818057578894575, 8247228186942598824, 1136969355400329759, 10655531979690449172, 2576835836686641728, 11962587603144326643, 4432306406914224240, 5965863372521664876, 6800381563397521246, 1915139846278772570, 11038263421898231618, 241906252043427896, 5522080961475325, 264840477724691988, 77870488603397991, 603183835508760820
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
