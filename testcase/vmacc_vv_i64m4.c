/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10363141376385261529, 6176312136321842221, 1626113102741935773, 1159172369665231935, 14402817979954128700, 18093386865813120311, 4387799311633824099, 11031653716165975632, 5932447770357401352, 2012851285745239757, 9829598043835375945, 11403304977681996686, 10755819685639701947, 6839605592742288612, 2910975252707323391, 5078139050088691450
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    113844481968223127, 5536109145437701485, 3485566848882794166, 2475396348523490589, 16142625610489246558, 15485419109449493918, 16276469153442879494, 2121604941870259682, 16618719295151700221, 8794700375944817210, 3890845481252745410, 11947774350264136416, 16668748576018229649, 12979083939551773729, 415705323190800315, 5387310673583618169
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    const int out_data[] = {
    1823631363587988262, 5049989810445911937, 5444459631858692553, 6506617956799921963, 10380934213189551601, 18013527101061989461, 17862921600917212403, 11274870130627145179, 11570292868754743253, 16767673785983421027, 469146192036942489, 5507128742832988718, 13370354775741392012, 18280494077332548164, 17451882565747061945, 640828346883829741
    };
    const int64_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    1179786461558038905628724686909169445, 34192738102969218381866793633513310122, 5667925923451232395515252639809792871, 2869411051178636947527169335274681678, 232499298386422513710430011677553566201, 280183678726524979457093029704458757959, 71417880147305838335574376078167338309, 23404811041219148943176388055351214203, 98589684228718228543945954742838842045, 17702423959464668798063212858973238997, 38245447131387698191732870802760104939, 136244114720588310574642815435196906094, 179286054068915624309067534354699818615, 88771815101629927791188964668770022312, 1210107908227119507346754764556730110, 27357512706484583260169835588538784791
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
