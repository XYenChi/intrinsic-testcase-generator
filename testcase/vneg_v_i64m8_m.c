/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -4771712544849569780, -3974879603497690377, 3515126622741523537, -2195739879907578614, -6318283049656158851, 7600476928922615259, 5561291219221160947, 8757054763110388883, 3246474466442194983, -8733700721305560927, -5046159699730126108, 3952732240005581771, 5347695075291792376, -2589638206565472170, 8365111682559038552, 9152654846081904822
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    2578361272956421423, -4530552168400553503, -7173595707009355717, 6851218622821327038, -2457977639345639618, -5444519777455167494, -6126982509924718312, 6527015694145667912, 8889815823789673381, 2467232599870667838, -8107607419751676851, 4583484949738931702, -4373829196667569091, -4613757090550873518, 2256068542789337791, -3349901362608119911
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m8 (mask, data1_v, vl);
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    4771712544849569780, 3974879603497690377, -3515126622741523537, 2195739879907578614, 6318283049656158851, -7600476928922615259, -5561291219221160947, -8757054763110388883, -3246474466442194983, 8733700721305560927, 5046159699730126108, -3952732240005581771, -5347695075291792376, 2589638206565472170, -8365111682559038552, -9152654846081904822
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
