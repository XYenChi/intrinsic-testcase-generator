/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1919249969, 944459563, 1029299027, 3633805518, 2872520595, 3708918995, 3953945351, 1627314102, 414070035, 2378963366, 3528763024, 29222405, 2525019590, 3822490524, 794700725, 4035096819
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    422903382, 4241522852, 2356226961, 3010242072, 2355348718, 2825866097, 1344869016, 4069497236, 3667703382, 1678445544, 2776956082, 2424984879, 1609340559, 2132198736, 2231816356, 440799105
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2342153351, 5185982415, 3385525988, 6644047590, 5227869313, 6534785092, 5298814367, 5696811338, 4081773417, 4057408910, 6305719106, 2454207284, 4134360149, 5954689260, 3026517081, 4475895924
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
