/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10043801227107455138, 17412253226575751891, 15105463583079471089, 15599813550054557453, 15348247353665840145, 17527378036569777879, 13923050094667082982, 9564470976176448738, 14823479267154959710, 8890079120745007500, 18446342355365091580, 12305306007661725975, 9487702975209399510, 17379249645318263191, 690036747793555443, 6489773468011101407
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_u64m2 (src, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    10043801227107455138, 17412253226575751891, 15105463583079471089, 15599813550054557453, 15348247353665840145, 17527378036569777879, 13923050094667082982, 9564470976176448738, 14823479267154959710, 8890079120745007500, 18446342355365091580, 12305306007661725975, 9487702975209399510, 17379249645318263191, 690036747793555443, 6489773468011101407
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
