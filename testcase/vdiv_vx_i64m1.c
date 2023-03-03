/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1967798238696792869, 2776692211299956135, 11175854351391216453, 1439756174361392480, 1329652189654495151, 5824837052692622234, 8794437772164911707, 9861405226098018999, 5680192390697778103, 14121319536586597667, 4827995432341247182, 12825762608456105882, 2659706734567241386, 6849035558723066029, 4754758508498079792, 15714478973359875720
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    1898120598629066712, 1443455481851926338, 12621014688806784137, 11445090345247756914, 15853355317570311520, 12097880768158908485, 6399560302732256005, 10815121619634447308, 16178538084107736179, 15784104580244415777, 3894680966758872074, 4083716058800933190, 7431358539276832863, 7275677348971283029, 16150119921857265640, 2476265705436961150
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 0, 1, 7, 11, 2, 0, 1, 2, 1, 0, 0, 2, 1, 3, 0
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
