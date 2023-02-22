/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m4_t data1[] = {
    463289557, 3429950133, 2412298634, 717069797, 3697040954, 3214749948, 1621855625, 3076175476, 3656829032, 170869000, 1425864654, 4102813583, 1936549277, 1897519853, 3047783856, 227833134
    };
    const vint32m4_t *in1 = &data1[0];
    vint32m4_t data2[] = {
    722857202, 1047217641, 1225022043, 3574012908, 1423698326, 3884305954, 1470928039, 1140170863, 2446374183, 693811583, 1533525050, 2412317451, 226417984, 4016701341, 2232740726, 2685010590
    };
    const vint32m4_t *in2 = &data2[0];
    vint32m4_t out_data[64];
    vint32m4_t *out = &out_data[0];
    for (int n = 16, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m4_t out = __riscv_vadd_vx_i32m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m4_t golden[] = {
    1186146759, 4477167774, 3637320677, 4291082705, 5120739280, 7099055902, 3092783664, 4216346339, 6103203215, 864680583, 2959389704, 6515131034, 2162967261, 5914221194, 5280524582, 2912843724
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
