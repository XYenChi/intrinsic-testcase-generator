/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    12429527145131537578, 10770617599697624297, 14215174876256654587, 12713416324914369038, 15796614314251723745, 10831201338434890085, 13658557844031064823, 12590150387535543819, 17600334923413260766, 17508754617730092175, 14233922440680334711, 4884108577271830747, 7457852525972803957, 7173238767939357060, 8307829318221621587, 15727467626865845306
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    887950757190343974, 9639618956381599323, 4546621872606672982, 10432969181481463426, 7954038877379324660, 17493574027451525572, 13716079529812683298, 7505948367068355846, 4806251043697330217, 7460307063100097122, 8487515409736978086, 10328881469908513835, 9434286376471836881, 4506226698003355017, 17324087062314220206, 16575604382101658749
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i64m2 (data1_v, data2_v, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    13317477902321881552, 20410236556079223620, 18761796748863327569, 23146385506395832464, 23750653191631048405, 28324775365886415657, 27374637373843748121, 20096098754603899665, 22406585967110590983, 24969061680830189297, 22721437850417312797, 15212990047180344582, 16892138902444640838, 11679465465942712077, 25631916380535841793, 32303072008967504055
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
