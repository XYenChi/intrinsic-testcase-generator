/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    157580896843890901, 5415245608585610869, 626394348143587033, 841162151285715563, 4047500673251009032, 15503033785252170611, 5953709900868776055, 2915147419503070612, 2096823713510551397, 16766147189007665949, 6111301164839471609, 7837714710667961092, 10096009771227341962, 5489371840216746773, 1211774837932086448, 8442303708554644502
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    5906825424227466834, 7057256754979099683, 349662679904032496, 6003668722587102805, 6432764696168699826, 15532068000536984031, 14517004041831972941, 13884923244820360395, 16948421652829483964, 1586277100157440443, 1341692817385267801, 752723455342491163, 16774251942707948459, 11593281599127961224, 3206435030854011185, 6554077266879749015
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int out_data[] = {
    12382266273691132510, 10633586188472963808, 16021065957793667539, 17742518355198028896, 16983437329775723296, 16378797231588776115, 11556829733273870426, 2405512919234888668, 8769353217683101509, 3795251731335404301, 308461280272526063, 2308420337776341027, 8642045341818780900, 2908903913836676381, 7879179909845067317, 14526500122936473898
    };
    const int64_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, *in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i64m1_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse64m1_v_i64 (vbool64_t mask, int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    12382266273691132510, 10633586188472963808, 16021065957793667539, 7, 16983437329775723296, 16378797231588776115, 11556829733273870426, 4, 8769353217683101509, 0, 308461280272526063, 2308420337776341027, 1, 2908903913836676381, 7879179909845067317, 0
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