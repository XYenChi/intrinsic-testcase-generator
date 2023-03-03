/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5291883617653799979, 18264419407892252634, 3257135290419326783, 16878658482016724860, 17138899404225331736, 13386941181553612013, 1026073589103860056, 7999250282927270882, 12650953434638413550, 18171523671267695141, 13686105443380753751, 8311609869042307452, 14000692538940956708, 12097803505911229884, 13666152612614052825, 15589085211105016159
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    7883890446415325617, 4060981799047271452, 14765331724448071622, 17420958582094889344, 3661836407451753697, 14707990710857745308, 2105728089651300669, 7843931936642936684, 339244673938296512, 7373137025109670424, 18840136206063174, 16949812556847880645, 1476934143852038622, 16288847593807537689, 12265699619355344808, 1650450881424306325
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int out_data[] = {
    10678840364358664305, 10900961208566180337, 13073473567009308624, 13803067991734791811, 687359693993534279, 9443443368967154853, 16156824706424900053, 1146013242583099154, 16089260037138850072, 3654824252799728077, 9651988663315539068, 17313832191543977665, 14605005067226618502, 5245255581116779593, 2513419480152828734, 5032090652277840274
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, *in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i64m8_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse64m8_v_i64 (vbool64_t mask, int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    10678840364358664305, 10900961208566180337, 48092683034447868904404392703806852026, 294042410336537960448308351338993891840, 62759845822045490550907203584789427992, 196895006545089534841097986084603185004, 2160631978625324873270888148955177464, 1146013242583099154, 4291768572942480959204162565178537600, 133981133983280650436273660268616209784, 9651988663315539068, 140880229325914071681873924486690066540, 14605005067226618502, 5245255581116779593, 2513419480152828734, 5032090652277840274
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
