/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    803728058175116839, 16557356224835718339, 3314008865496244769, 14699139361371009495, 4777175589570938654, 13427652389236093135, 18384462301016585392, 1096902810830761411
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    3882246278816744857, 5078226604405341595, 410441075272639299, 17542915600458059542, 12142308544888939191, 8005979582724269866, 15213817894855559839, 5527952740670863199
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[64];
    vint64m4_t *out = &out_data[0];
    for (int n = 8, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vv_i64m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m4_t golden[] = {
    4685974336991861696, 21635582829241059934, 3724449940768884068, 32242054961829069037, 16919484134459877845, 21433631971960363001, 33598280195872145231, 6624855551501624610
    };
    int fail = 0;
    for (int i = 0; i < 8; i++){
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
