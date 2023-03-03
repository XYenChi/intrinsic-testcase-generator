/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    13312881490837295247, 8765810808167494908, 4862733994845676410, 11993725833381126873, 9736760395404689351, 18043256943732304785, 3922800514812204068, 6190823701488866483, 6823799740196544067, 3064505655051829621, 792653618514389013, 3169963476947923530, 7266413627037393282, 15627930352766345142, 5560409720897014652, 13000700911585125742
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    14851014324672088458, 6718971666113355270, 11438363974871925978, 12347025774076978411, 14740134903565669400, 2263829609417732845, 6366590118570378887, 11969311172698354068, 15316361708758410972, 12415158187787998763, 11286580984818354176, 14969917312571264702, 4099774865374528391, 7612471307712987335, 9062833263884925294, 2199332822402846300
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i64m8 (data1_v, data2_v, vl);
        void vint64m8_t __riscv_vse64_v_i64 (int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    1, 0, 2, 1, 1, 0, 1, 1, 2, 4, 14, 4, 0, 0, 1, 0
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
