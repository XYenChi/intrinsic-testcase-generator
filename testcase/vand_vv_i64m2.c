/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    17168350178108042980, 16192086241837375507, 5734965723142887214, 12478293715661518914, 3692564210438634384, 4545268584914231077, 619066955835339439, 4741268427702665276, 16123625855144867685, 5786748609875113301, 18255501533094955827, 12596792089409060067, 957771953872025977, 3312670294131034189, 16383707699379867623, 4360170353763247551
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    3819746599063689234, 367318887163477830, 14746743410277695785, 16170535575587340221, 565385700143689740, 14846095495801122771, 15771806134737500182, 17012832691575390785, 8851744300452982319, 18113343147644758273, 10485472491580428015, 12057033577968878085, 11073398963317965406, 3958561721168290942, 1695130131147558729, 13132855570282641595
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, size_t vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    3819746599063689234, 367318887163477830, 14746743410277695785, 16170535575587340221, 565385700143689740, 14846095495801122771, 15771806134737500182, 17012832691575390785, 8851744300452982319, 18113343147644758273, 10485472491580428015, 12057033577968878085, 11073398963317965406, 3958561721168290942, 1695130131147558729, 13132855570282641595
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