/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    903079389, 1416027670, 2652739293, 597777172, 3645656839, 3156101207, 3973543840, 530904592, 1206996312, 3140969138, 496127536, 2400206718, 916994460, 671526452, 384357388, 3130297898
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2851449234, 235278450, 2487547970, 2833870484, 3421324951, 4102163593, 4028020109, 1580628050, 1491858298, 4054794617, 1261530561, 3471507888, 2938915021, 854486980, 3644021267, 441733922
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    const int out_data[] = {
    2107831014, 3183805902, 2522401654, 1747571643, 88499690, 2241166343, 2030274004, 454699534, 652232521, 2398573428, 3509858664, 2723022135, 3037540616, 3901594404, 22845136, 3956119110
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2575085034113069040, 333160798538517402, 6598816245763786864, 1694023085487362891, 12472976706142989579, 12946843469419923094, 16005514493543352564, 839162690443705134, 1800667464364829497, 12735984755324103574, 625880052327486360, 8332336557090613719, 2694968795705324276, 573810613861189364, 1400606496023415732, 1382758771468015066
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
