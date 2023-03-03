/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    3917428060088288095, 13692326929522282569, 8730351787723029131, 3606754348105211068, 2276884808639528926, 11254276753498871233, 577627316115142688, 3579329167127048860, 10704522040649854750, 15577290695615741675, 8663694964129523093, 10325416382820879619, 4606368659925421605, 1662539002774048989, 157042096531102776, 11623946202593779398
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    799642519605873753, 5125783458925600569, 8459858673156212785, 1766720923494447424, 1772838051326825310, 8197684901916775534, 9834750300637597258, 6696733080463900878, 12010005358985669595, 4586500870019683071, 4745744323342955847, 13006590936666542510, 2894903749369986566, 13855399956368452705, 4969593858595113066, 2511308506103849723
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 0, 0, 0, 0, 0, 17, 1, 1, 0, 0, 1, 0, 8, 31, 0
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
