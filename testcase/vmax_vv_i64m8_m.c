/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1309194259484740646, 17354456143425589235, 15357670935581815508, 2353016220654645376, 18300315047078022097, 221546654189578630, 18257317826566622828, 12315889104960946268, 3174786806371263801, 3534499179163299243, 17876272267118411604, 16143699244967782457, 13930829317943787633, 17293887307192092721, 18302774863016930035, 9700133735028415201
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    13845644996031732461, 10325999882191419639, 14135446226590367622, 2666097396710412193, 11686817492943600316, 877484086589791482, 9928179048301547342, 5272091608921277005, 11585330107340058986, 3036968409754607414, 4253215094011042173, 3978100466232417126, 9701404577155819874, 11262778867743569370, 13448866821310803740, 5861292077438906482
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int out_data[] = {
    4586921550829902429, 170647631078455972, 3943501188940060287, 7155195691690944563, 7679495542018509500, 2298729410421285721, 15884297883621824508, 10950726489288151547, 17309840725029040107, 1271622941769405771, 5700665417152541862, 10415429800617584452, 8883933982564753650, 877548569292137130, 13641929134631452779, 13733746457021948650
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, *in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i64m8_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse64m8_v_i64 (vbool64_t mask, int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    13845644996031732461, 170647631078455972, 15357670935581815508, 2666097396710412193, 18300315047078022097, 2298729410421285721, 18257317826566622828, 12315889104960946268, 11585330107340058986, 1271622941769405771, 17876272267118411604, 16143699244967782457, 13930829317943787633, 17293887307192092721, 18302774863016930035, 9700133735028415201
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