/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    10704608742173150688, 11831927694911591823, 418456248662683333, 3677694538447410690, 9226762400527417211, 15693845212081922421, 17176489022267633030, 9499349037270755190
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    2186366198292468185, 16248351620925984067, 15339396873237128494, 16367925193334949618, 5856060467392431934, 16812530694810469650, 11787777730168884429, 17055372864986239017
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[] = {
    18229913754759805062, 6337948541278249882, 16868171579791670030, 14045872235676458922, 16240748999117796882, 184627958947325260, 3568625180557795799, 13153560624444148641
    };
    vint64m4_t *out = &out_data[0];
    int masked[] = {
    0, 0, 1, 0, 0, 0, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vx_i64m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m4_t golden[] = {
    18229913754759805062, 6337948541278249882, 15757853121899811827, 14045872235676458922, 16240748999117796882, 184627958947325260, 3568625180557795799, 13153560624444148641
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
