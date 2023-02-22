/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    1148078913599916968, 15944272797156381643, 8423924921549659566, 5188517827816899315, 261590503485217301, 9513516846761665898, 14085169829616184480, 18277855173957013822
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    6335403981765082721, 2021527835278510465, 7228600381393711121, 8221358917642463064, 3257838585363793878, 7984234323061962715, 4479698413780040109, 13205816012076878750
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[] = {
    10218176056732846458, 3946455923665118684, 177032907417009064, 17214351408947596607, 11000952780562450832, 7038392917611554836, 9206194861601362209, 12405545324331073462
    };
    vint64m4_t *out = &out_data[0];
    int masked[] = {
    0, 1, 0, 0, 0, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vv_i64m4_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m4_t golden[] = {
    10218176056732846458, 17965800632434892108, 177032907417009064, 17214351408947596607, 11000952780562450832, 7038392917611554836, 9206194861601362209, 31483671186033892572
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
