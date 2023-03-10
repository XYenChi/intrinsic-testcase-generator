/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -4947857857214916774, 35224874114658076, 46038552933259795, 3431670513665909175, -3814711651309959868, 2322758579449420985, 3497631713752149123, -5507496773162052516, 5078028990433808004, 3477162400902661714, 7312679271938144276, -2420985910098572390, 1339158406704189429, -1665628763945109696, -4433791072824293536, -5364365352204739623
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4690499076838534965, 2918252475106501379, -4458052141803771592, -22281323133692474, 5805102345455628697, 7779335294382025824, 3299555126364354153, 6873814291306389390, -6918142020040622759, 2021387420245420730, 1312222536759830207, -6743688313007715696, -1824297301244505703, -6986725640245575848, 4334064026469472989, -13043698738267601
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    bool64_t masked[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    4690499076838534965, 2918252475106501379, -4458052141803771592, -22281323133692474, 5805102345455628697, 7779335294382025824, 3299555126364354153, -5507496773162052516, 5078028990433808004, 3477162400902661714, 7312679271938144276, -2420985910098572390, -1824297301244505703, -6986725640245575848, 4334064026469472989, -13043698738267601
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
