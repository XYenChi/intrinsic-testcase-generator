/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    2988842353247890989, 14793049768808711333, 9393623499407923426, 6233041487087567599, 4755233315644163951, 8216140028086769675, 76833843056646952, 14312277603174349090, 9394116445035624338, 3541237663194975064, 12400094533071804970, 16192401279985601483, 16240303770358226069, 11367943793031845909, 7972856675195725618, 10781567864184373418
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    5309818403470654729, 18257852964277442038, 8236500717042550875, 8953656194840392514, 2017316270520096590, 4341345924345871128, 10808947925170968321, 7212043548692313152, 10308103313556345541, 10236149798837881228, 3080251080707208695, 6516833551914516356, 18229359838348693528, 7818493660815323183, 8843357775556728733, 15223931873732632726
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1 (in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    8298660756718545718, 14604158659376601755, 17630124216450474301, 1, 6772549586164260541, 1, 10885781768227615273, 1, 1, 1, 0, 0, 0, 1, 0, 1
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
