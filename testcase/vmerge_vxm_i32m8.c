/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1282927177, 1486044551, -377203154, -1991861536, 1525533952, 2123398824, -1269864853, -2074368062, -695234741, -82410673, -1709604917, -280616640, 1062819090, 194494241, 872778371, 501987523
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -572190892, -1374061497, -101978680, -1034754939, -1931672425, 858466979, 588786514, -1822615998, -605477923, -1073877979, 10780242, -1989215016, -1445370099, 1372388332, -1724186722, 7432615
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1282927177, 1486044551, -101978680, -1991861536, 1525533952, 2123398824, 588786514, -2074368062, -605477923, -82410673, -1709604917, -280616640, -1445370099, 1372388332, -1724186722, 7432615
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
