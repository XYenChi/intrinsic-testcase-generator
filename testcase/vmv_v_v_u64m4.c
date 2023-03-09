/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10416991955687767185, 11865159694817660378, 5365838918709852029, 125145395947335569, 12951341997353922319, 16422859410630599489, 6172878506051116796, 6076326499166441631, 3351928784568141961, 14958847398022353216, 9722525143975417167, 6546652658902252039, 1009399622796596327, 1356221229817210263, 6152493765130786324, 14298247042117588765
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_u64m4 (src, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    10416991955687767185, 11865159694817660378, 5365838918709852029, 125145395947335569, 12951341997353922319, 16422859410630599489, 6172878506051116796, 6076326499166441631, 3351928784568141961, 14958847398022353216, 9722525143975417167, 6546652658902252039, 1009399622796596327, 1356221229817210263, 6152493765130786324, 14298247042117588765
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
