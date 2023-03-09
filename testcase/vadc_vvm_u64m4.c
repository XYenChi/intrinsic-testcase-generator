/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    11641786551454916892, 12980992518760934281, 15048757191449749463, 11549025643776512226, 5345212537576235184, 3004587850886035281, 8675866618228006256, 6777389294575150537, 15757909645318822558, 2733119676676823070, 17490893195423907894, 9182437360869129299, 8014852412779023564, 8071281451444682436, 8727223357258343019, 15145468200847033268
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    8186431088501096613, 16408667467544378998, 4447422100084286518, 7539593414180124364, 11799312898801246696, 17520626208648794941, 2902304709193129418, 4757657317673477866, 9223664922119244176, 9469104476062138998, 2123355767061614173, 3270755343006877618, 15920563701306094514, 13800860832122841612, 6124439443159282198, 17505225744941372509
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    bool16_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    19828217639956013506, 29389659986305313280, 19496179291534035981, 19088619057956636591, 17144525436377481881, 20525214059534830223, 11578171327421135674, 11535046612248628404, 24981574567438066734, 12202224152738962068, 19614248962485522068, 12453192703876006918, 23935416114085118079, 21872142283567524049, 14851662800417625218, 32650693945788405778
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
