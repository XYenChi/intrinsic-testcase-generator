/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    13755306122105527878, 10457623427440068714, 6235886067320581094, 508567130999522368, 3620835426198058148, 13871162255961748133, 18429777599480669442, 9749990067361956047, 8194907239992979003, 4785975631183085457, 16360794025446543610, 17163021805385078289, 5686460917626969001, 12438407471271147865, 8385474235856027201, 5599058209653876761
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    3351713423862105552, 17281812938555219001, 17017155544401851947, 11589012284165124699, 18226541588091225837, 10153479874931102195, 17382948551888313990, 6831836073212184065, 9859168238934926329, 8388059426358356727, 15989352746583097881, 9847340624713326125, 987300696648143646, 4704877588276230069, 14006243046159660045, 7073414484575304715
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    46103844178793700588520071907514578656, 180726691854871954953431692670758434714, 106117043164762686746486633721795290018, 5893790728476078915312358212159767232, 65995307479232925301758428606325969876, 140840566807811515805999710764673451935, 320363875834516190503531173941894093580, 66610333855663903795937567091403791055, 80794969181556656471760664559048869987, 40145048007466666062044897324131819239, 261598506887054030274477592717765090410, 169010121867009135236415954364714000125, 5614246825435548675044974052237117646, 58521184545431239615111894312458152685, 117448990204709470035036208162432884045, 39604459440146005095581740142632228115
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