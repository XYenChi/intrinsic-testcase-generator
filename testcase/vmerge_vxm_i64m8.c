/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7427752484449264479, 1639301830573658301, 3703743532501760617, -3738245038407034835, 8703986229946359800, 7138186223133399869, -4527370503748614637, 394622821654866411, 2419934905053169812, -7033415459685322468, -560367645446811708, 1316579582705660927, -5711155404904043194, -6369746576304985494, -3694566375675500324, -9034869086309498140
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -8133598154880406054, 1096928902756596971, -8781438259539736015, -1704812540765512194, 2045214597062323019, 2874898556260655872, -7278421922341682156, 4541505626076366674, 5966298583119510951, -8614243776198447502, 71570634307563348, 945209713836026381, -6039653811067374702, 8997442951072904525, 5800725513635637682, 1294011266627074914
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    bool8_t masked[] = {
    1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -8133598154880406054, 1639301830573658301, 3703743532501760617, -1704812540765512194, 2045214597062323019, 7138186223133399869, -4527370503748614637, 4541505626076366674, 5966298583119510951, -8614243776198447502, 71570634307563348, 945209713836026381, -6039653811067374702, -6369746576304985494, 5800725513635637682, -9034869086309498140
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
