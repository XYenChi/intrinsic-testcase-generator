/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    46015091457778734, 15340349982292783212, 549072453180336516, 12699416542552244999, 3308538887265182049, 10535583100699422716, 380197437398279277, 4100634966368657321, 14487146260591642879, 12964791070886871273, 4143179731782488673, 8376104148920928857, 2099985539999536859, 10439597490224461938, 2985776198789122410, 12575356544504209482
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    14245393175563156701, 5093809303212038506, 10224422287444026172, 10026124078678011339, 577273194630412874, 872614139306082327, 3804266898551086998, 5303675065180566995, 2747654497267110502, 14634842992997803628, 5391433493206780438, 11090106482934152039, 11054266417039621819, 7618833034898220061, 17736656988960213751, 11096199038227601024
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    46015091457778734, 15340349982292783212, 549072453180336516, 12699416542552244999, 3308538887265182049, 10535583100699422716, 380197437398279277, 4100634966368657321, 2747654497267110502, 14634842992997803628, 4143179731782488673, 8376104148920928857, 2099985539999536859, 7618833034898220061, 17736656988960213751, 11096199038227601024
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
