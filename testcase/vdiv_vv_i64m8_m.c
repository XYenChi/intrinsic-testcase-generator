/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5859728416699873564, 2608231200654087269, 1252538941327080585, 9852584088764521169, 683989415223818241, 15070337521497654717, 2016548384889483896, 11182571179741922918, 586389478354697534, 8444342795532357778, 1968828006470415805, 13476824516533672663, 9741761527026473303, 4392263869453521759, 12381874105442616492, 12549241398499576965
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    10475439834362270977, 16052305189015928625, 1218932859454643556, 5648268402277604899, 8760065517760487620, 1382917341558602165, 7046912188076752182, 6030903049112326917, 608187327109575942, 1441103973581685080, 5207642586727980349, 2504521568346134801, 6307580657335403728, 15641083742604815338, 16551658841490198211, 17285787908874251912
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int out_data[] = {
    18170944018168379064, 9670306314111227776, 7209420206284957312, 13697755451664126170, 2632901392138170931, 2154719145116974508, 13489399873803387528, 4417779759198527504, 4775971182352821373, 4240015490233261732, 4808318936380390154, 12133774602651568277, 1903188151052050121, 7157500775025457555, 13683526233050618795, 13002083386151511149
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, *in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i64m8_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse64m8_v_i64 (vbool64_t mask, int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18170944018168379064, 6, 7209420206284957312, 13697755451664126170, 2632901392138170931, 0, 13489399873803387528, 0, 4775971182352821373, 4240015490233261732, 2, 12133774602651568277, 1903188151052050121, 7157500775025457555, 13683526233050618795, 1
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