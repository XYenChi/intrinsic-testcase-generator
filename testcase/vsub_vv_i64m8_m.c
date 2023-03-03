/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    3769225677746386965, 12543759611784468376, 13063027362723478064, 9572218464674723917, 3559187317441636779, 189234730818685307, 14141311755427477568, 174922308686657880, 7515664911917397683, 16339873752530526247, 17759640326046357938, 11153520639968716439, 6281955939871472758, 10804774954040980521, 170041964241904116, 2948741102433426621
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17564246264312263940, 62306160639147371, 7110706442492994349, 10861697459478201136, 11081606794438231146, 2488063065242131234, 5819583100748786466, 14722154428057854437, 7058492858115610229, 11428890865076452179, 9941437806521917781, 8775113297968791170, 7945141080033547080, 7598782519349112068, 8017703165375612732, 8547240553937310122
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int out_data[] = {
    12183559045814836162, 4565213719055227569, 2658212047469329851, 6998910503719001403, 5840727845126229735, 15129172280747280986, 4751105159739412205, 3889953727834183895, 9372909037485244626, 15971752097895955862, 17267832346434879897, 10337148560129096533, 10755447128974001332, 14019665130996366603, 907980892826974684, 7984770269401801870
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, *in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u64m8_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse64m8_v_i64 (vbool64_t mask, int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    12183559045814836162, 12481453451145321005, 5952320920230483715, -1289478994803477219, -7522419476996594367, 15129172280747280986, 8321728654678691102, -14547232119371196557, 457172053801787454, 4910982887454074068, 7818202519524440157, 10337148560129096533, 10755447128974001332, 14019665130996366603, 907980892826974684, -5598499451503883501
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
