/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -1740632333762250790, -5652705417627947781, -1913982176814429776, -920779837095832048, -6560128522083511275, 7162392704430835815, 8630917149913479281, -8016453840257758908, 6887364810825415753, 6677135602317328652, 5396307941267270019, 8741361795922882928, -1840181819205495082, -2532898841538548682, -4581803649716526580, -2823101219005476252
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -1474247653751054455, -6759832041939766456, -3261674341375690250, -9150173110641735349, 7395491514157984355, -246076489993949794, -3625956458108467641, 4729391110152376299, 6102459713394101683, -2539461220834541787, -7984189571512499727, 2893422193002793188, 1650694914084923882, 8096156681772279788, -5510171486859168307, 1088878131597172564
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1
    };
    const int64_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1
    };
    const uint64_t *mask = &masked[0];
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
    1, 1, 1, 1, 1, 6916316214436886021, 5004960691805011640, 15159681343604169007, 0, 0, 1, 11634783988925676116, 0, 5563257840233731106, 0, 16712520986301247928
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
