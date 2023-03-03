/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    11111667089955246983, 17306518219857630830, 9302063916813219764, 1492675607360478357, 1629467274883103455, 16987524552788828736, 2216752399205126924, 4509118597170383974, 8105520358658260296, 8310554582307592224, 17999230870807064015, 3040189260846969826, 4166039192055824287, 2754925528668194019, 13812928320504915624, 563312887887467902
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    15052167387662661286, 16750312013389487367, 547692792148365705, 16426900519261114576, 10342452179734309069, 18279708355039182182, 17883940166171411852, 15503530451132099312, 14880927723145156765, 17786755171150020295, 14911694627439623872, 18430176132662441958, 3214741186527978093, 6781071572140452470, 13081734615175558604, 9096146738045062690
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u64m2 (data1_v, data2_v, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    -3940500297707414303, 556206206468143463, 8754371124664854059, -14934224911900636219, -8712984904851205614, -1292183802250353446, -15667187766966284928, -10994411853961715338, -6775407364486896469, -9476200588842428071, 3087536243367440143, -15389986871815472132, 951298005527846194, -4026146043472258451, 731193705329357020, -8532833850157594788
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
