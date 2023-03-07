/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1542247936, 272046611, 1746144057, -1400668792, 2062484668, 412535030, 643705892, 866238784, 79084785, 2034231231, 2138915501, 1698412537, -287516001, -1571959395, -696632247, -1008552027
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1544452898, -75478303, -516329158, 571588156, 1786750971, 1730693074, 960522696, -1150146267, 1827372041, -305286365, -1024950180, 1282603668, -835969125, -2081895093, -1050381482, -875102699
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    1431886883, -1817362010, 1678830120, 1669268575, -403869015, -2068602176, -1558956447, -106614416, 480149223, -1091826416, 947288900, -364270835, -737741431, 155762678, -2037329977, -1240801691
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1431886883, -1817362010, 1678830120, 1669268575, -403869015, -2068602176, -1558956446, -106614415, 480149223, -1091826416, 947288901, -364270835, -737741430, 155762679, -2037329977, -1240801690
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
