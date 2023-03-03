/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    6846984359009626064, 12221481313981377757, 6899995911308225084, 8937281388401626664, 5040666980536669547, 1654043344577668211, 3503585336883178782, 10572944929501497509, 5342200544032726132, 9521678934394156849, 11398956414605239586, 3238848956240462499, 14518672847338842060, 8900676174670275079, 7606546679859106749, 9377623660657318129
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17827859203625670212, 15406883821376517793, 2026946945853381527, 15073799729795490195, 13348911829680956770, 15634435527044530202, 15839185056197517927, 4514502496337606159, 4193314562220239130, 5948218498448323380, 12802658032818813903, 5893236731746157269, 16247408760808778390, 13810460805482784388, 637524153773975874, 7441870205187388849
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int out_data[] = {
    6541813431169625816, 2396217997022897056, 1239569739774042651, 9893507191375737373, 1886952015548518305, 2643798026677632748, 1856250320122998300, 3608572102508202451, 9430981168726608220, 5083641467700066499, 6272926906222638962, 18151685779452551716, 11175019822106007370, 11216933386199293015, 6803848478904647708, 12298062882556814385
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, *in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i64m4_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse64m4_v_i64 (vbool64_t mask, int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    6541813431169625816, 2396217997022897056, 2026946945853381527, 9893507191375737373, 1886952015548518305, 748045425845516303, 1856250320122998300, 3608572102508202451, 9430981168726608220, 5083641467700066499, 1403701618213574317, 18151685779452551716, 11175019822106007370, 4909784630812509309, 637524153773975874, 7441870205187388849
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
