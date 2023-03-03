/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    6919625347750448259, 13101652083522453054, 4853299098309932917, 11919189337740736086, 2453595721908562440, 13857083193756389100, 2446008819211582402, 15049147422989682529, 14135293249129632158, 538459536377366425, 7258930762385023017, 698852321898641039, 2751733121411943369, 15495579521490918968, 9928630118527057943, 5428346004245636928
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    2608141401916626540, 14190638995631870053, 17807394179589982579, 1295733541704638537, 9345630184839211868, 10520606517436311759, 5911256302171797190, 16867748744457532991, 12275468314386812130, 3523388811032917009, 3814918010229941639, 8572775814878061239, 8762957405096524805, 5015298721175012878, 12787419711005000457, 17250840326850326906
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 1, 3, 0, 3, 0, 2, 1, 0, 6, 0, 12, 3, 0, 1, 3
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
