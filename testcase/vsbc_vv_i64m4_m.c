/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    2486217907311845620, 13678178953454608591, 9226970034027271724, 1370205227172278814, 4958082251360087485, 8137171239417117901, 10404369364782029425, 17946785698185154712, 4698505058001119450, 6130427406986878433, 17739748555724225634, 16336830668112591368, 10316373819271123620, 13046497031040934629, 17798549023657729979, 15270493456273070252
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    6107644118401824206, 4872273865355319423, 2730959913844748971, 343871988130812126, 169607297327314173, 6393557473936955621, 17658530145352465543, 12843444262216002549, 10199148842984764990, 10812050193808558812, 177030609927139340, 1638736470694806877, 5402024646898024068, 10329391754211502176, 17076318662297517482, 14589439832740055082
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int out_data[] = {
    4576979160046231983, 6729971037694054843, 806365423186073132, 3320089502644388167, 16966370449529700873, 10142221407575896484, 18016791025239884566, 6469619525415042450, 823957843354900045, 776715076587948978, 1240631300084664719, 16742995151396189651, 6773896112573892617, 14459933032432695147, 17688684831524602266, 9833120120633973929
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, *in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i64m4_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse64m4_v_i64 (vbool64_t mask, int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -3621426211089978586, 8805905088099289168, 6496010120182522753, 1026333239041466687, 4788474954032773312, 1743613765480162279, -7254160780570436118, 5103341435969152163, -5500643784983645541, -4681622786821680379, 17562717945797086293, 14698094197417784491, 4914349172373099552, 2717105276829432452, 722230361360212497, 681053623533015170
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