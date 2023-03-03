/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1063951004, 1862264707, 1844313982, 193321146, 2262853304, 2611557044, 1291144420, 970421060, 541933429, 3002645897, 2156403010, 3726799651, 3319832673, 1936375160, 1151374388, 2265532932
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    384731722, 2305548578, 2416605027, 1688936795, 437334552, 1621316734, 3373011544, 3584483351, 4024377713, 1552888413, 4209376780, 1314093560, 1145146904, 2471708627, 1795123651, 4181496117
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    856734975, 3417575103, 1831014919, 3501816196, 1863585832, 3402507813, 1667261008, 2282226404, 428445190, 2715227298, 898634938, 3351724821, 312065537, 1901929315, 1127750800, 2886465029
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    911524036813164901, 6364429497838789821, 3376966416362297459, 676975120092080616, 4217021357228788929, 8885843246305184772, 2152674747162775361, 2214720566129668241, 232188770955256510, 8152866105762096306, 1937819085194363381, 12491206893150837471, 1036005365849890401, 3682848681641815401, 1298463387166510400, 6539381580265835028
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
