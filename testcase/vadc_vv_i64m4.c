/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1476699676520421940, 9752238473598565269, 1907125582986721914, 8190331515179238549, 16821690646343433917, 10497457248230586625, 14351147965175509830, 13316152825973853197, 12574809250653870527, 4005051701017581453, 9257560058368737163, 11679619302590141527, 13237216769330555709, 12881601201367627741, 5100396468240341711, 10346002171505031298
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    9925217305859237073, 1812062271523476132, 498897404473197566, 16110599606446254290, 11656105915112802619, 13209422634101117878, 1661354075788343075, 12135794724961622181, 13582340673880128202, 10908762546157121284, 12952734811142945755, 16782596522715206463, 16649137997734342202, 17711540036437797428, 9739938238892912926, 12722478614326723572
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
        out_v = __riscv_vadc_vv_i64m4 (data1_v, data2_v, mask, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    11401916982379659013, 11564300745122041401, 2406022987459919480, 24300931121625492839, 28477796561456236536, 23706879882331704503, 16012502040963852905, 25451947550935475378, 26157149924533998729, 14913814247174702737, 22210294869511682918, 28462215825305347990, 29886354767064897911, 30593141237805425169, 14840334707133254637, 23068480785831754870
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
