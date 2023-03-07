/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    205583300, 581746357, -171568864, -1228227711, -69753028, 1755818248, 1351597984, -982836937, -420716012, 1309523461, 850713431, 19973849, -1398570369, -1666021278, 479808165, -1928369741
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    144624283, -1603731988, 1117477515, 590459587, -1479397478, 298972707, -281954148, 74860481, 521631889, -2128700014, 1820658083, 1453577008, -963997791, 805761819, -1646516934, -610086611
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    983591168, -844687407, -1539964048, 1671957937, -126693518, -1277071473, 825266429, -305934582, 604429025, -1783851766, 1161979414, -1129640994, -2130155473, -1493397515, -1834934772, 1394932617
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    983591169, -844687406, -1539964047, 1671957938, -126693517, -1277071473, 825266429, -305934581, 604429025, -1783851766, 1161979414, -1129640994, -2130155473, -1493397514, -1834934771, 1394932617
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
