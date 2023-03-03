/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1456048441, 145657732, 3530482981, 3871575496, 2071520971, 2679083073, 618881078, 765483566, 657341827, 1796634455, 1583218013, 3109869100, 988561179, 21046589, 4128482080, 1555270525
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4223902363, 258122873, 1853878872, 280416895, 2473330693, 4120456939, 2181238833, 1960698673, 2980535269, 3892676376, 3205356367, 452484872, 2427112195, 2155961694, 3409725405, 2166567476
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    const int out_data[] = {
    3080084739, 3735510393, 3202612872, 1027144506, 1428276390, 1584136508, 987503634, 713183113, 3302648227, 3522779722, 4254084018, 1036955255, 188415963, 441656331, 1882144569, 3965822005
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    6150206453662450822, 37597595994014429, 6545087809634090304, 1085655180373549426, 5123556400195739293, 11039046439884430055, 1349927441330005608, 1500882612772691031, 1959230502465044690, 6993716502808914802, 5074777942572722789, 1407168722687210455, 2399348893242893868, 45375640115018097, 14076990234145386969, 3369598539812266905
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
