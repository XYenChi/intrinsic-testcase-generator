/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    624125669577661972, 2413661276613855095, 1097938150679048961, 506041072262897872, 8556293892536940485, 17747297046206861709, 10942025379726442021, 827505418192260507, 4582746370152016724, 13110169110684351540, 10767650147701217475, 5625313647929643313, 8883861874828908440, 18241741245333770809, 8933207628282712875, 2646533333065429387
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    1717000244574215144, 13875136756460681837, 15009148957771223922, 4743517244187570315, 14216493833453956722, 16315762530031710389, 10541195990857420073, 11112542999364158531, 9713348335347459844, 11845535225176822569, 7130690806015423085, 13222129292678877146, 7791519218174195392, 4146367320427728512, 964060298371777569, 3055027125080239199
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int out_data[] = {
    1032749974083393809, 8278520867195828720, 388291981785323313, 12223686845458531113, 7617851245860398079, 7630908017297611090, 5565389737841657696, 109284717565037672, 9532035664308980068, 2164608159134431449, 4890591150238183092, 13044564841843902054, 15686251345772650575, 3454607241568675007, 10969467569615794582, 15147805958341008866
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, *in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse64m4_v_i64 (vbool64_t mask, int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    1717000244574215144, 8278520867195828720, 15009148957771223922, 4743517244187570315, 7617851245860398079, 7630908017297611090, 10541195990857420073, 109284717565037672, 9713348335347459844, 2164608159134431449, 7130690806015423085, 13044564841843902054, 15686251345772650575, 3454607241568675007, 964060298371777569, 15147805958341008866
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
