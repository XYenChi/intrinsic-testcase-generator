/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    3022261002786110382, 16555894629701086667, 12030492557862089276, 4953422500336636879, 10679275427843457644, 5138456159408022353, 10606285539463594790, 3882800116239016562, 14703593772759905586, 9986784272821077774, 6739806146777295077, 10371171395559580434, 1082486375675609214, 6876798154139595320, 4227739917354842369, 6678849931848321622
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    13209979323622848998, 17376588493560634732, 17614675828433909087, 7091728970449778300, 16676000810658528397, 7571258892599361487, 5004986143319316518, 10788049478088110771, 18331616352396232937, 15167720017821217506, 17883808590840150499, 1062926302518814943, 14574888853746467676, 18183928748274546086, 9874260765601170332, 5088666952782231586
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    -10187718320836738616, -820693863859548065, -5584183270571819811, -2138306470113141421, -5996725382815070753, -2432802733191339134, 5601299396144278272, -6905249361849094209, -3628022579636327351, -5180935745000139732, -11144002444062855422, 9308245093040765491, -13492402478070858462, -11307130594134950766, -5646520848246327963, 1590182979066090036
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