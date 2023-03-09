/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7837204017490684141, 2154087377372043345, -7383153345034278117, -4247381975184390930, -3922146753780300180, 8693167273361239569, -2756858289211292070, 6681714890831088300, 6065170313020766463, 7618421564173400908, 5692242316036972017, -3800523348391864274, -4895774829538681835, 2906472209275542682, 1250647726966183, -4135308168064029359
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_64m2 (data1_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    7837204017490684141, -2154087377372043345, 7383153345034278117, 4247381975184390930, 3922146753780300180, -8693167273361239569, 2756858289211292070, -6681714890831088300, -6065170313020766463, -7618421564173400908, -5692242316036972017, 3800523348391864274, 4895774829538681835, -2906472209275542682, -1250647726966183, 4135308168064029359
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
