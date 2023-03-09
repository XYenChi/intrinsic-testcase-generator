/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    13146669785507317147, 3158290166372286194, 11607533943924005693, 8933502361144006745, 1746903769647732117, 17375092555285196963, 13900472138542258967, 9749830600283461914, 18285393041711669930, 212490520334868461, 9165369458934061029, 16458542998349842937, 14078616334964054727, 6287805999492049835, 14541625676105367389, 11755073786353791515
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    5408472874559818866, 271817652375653298, 5697280802151434049, 17048765046142030369, 18031289930637768692, 16630021144175206062, 10289831100356656423, 16523669052781264204, 16277840595378988573, 2036067205466651821, 1389469264619091292, 2662153870165853024, 15965543972720022643, 9403290877146462717, 8586495080202943068, 8618521356698423795
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    bool16_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1
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
    5408472874559818866, 271817652375653298, 5697280802151434049, 8933502361144006745, 1746903769647732117, 17375092555285196963, 10289831100356656423, 9749830600283461914, 16277840595378988573, 212490520334868461, 9165369458934061029, 2662153870165853024, 14078616334964054727, 9403290877146462717, 14541625676105367389, 8618521356698423795
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
