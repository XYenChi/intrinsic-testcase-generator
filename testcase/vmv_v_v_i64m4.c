/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    4773571299800253777, 7958559232779660253, 7832045721096318267, 8162109836183311449, -585665368616464815, -4813597815454773472, 3252646861673688971, -9012351735818823093, 3637954933767338836, -5076303471600853084, -8737184516013661374, 7299576708376250459, 4648649454016288896, -4598742857470296849, -1318458587154957645, 1229118403275308830
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_i64m4 (src, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    4773571299800253777, 7958559232779660253, 7832045721096318267, 8162109836183311449, -585665368616464815, -4813597815454773472, 3252646861673688971, -9012351735818823093, 3637954933767338836, -5076303471600853084, -8737184516013661374, 7299576708376250459, 4648649454016288896, -4598742857470296849, -1318458587154957645, 1229118403275308830
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
