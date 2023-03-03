/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    3930094922645132917, 16201554010403666948, 12071939191707478428, 10496769582375180409, 17191226807806076400, 13603442611963399406, 8435210379709930498, 3908531259131089176, 8524772723359919885, 10791224063416122759, 16361900965486809783, 16106814542626124635, 5292430208930718958, 14198439302898434528, 6516038804908372274, 3424529550420864012
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17592283876514772162, 9538044727998146548, 17855001408021106994, 6230592262203329530, 8682662954547065890, 16988663972295591239, 3531045185068258419, 13384263131914321282, 1028737915829247867, 2776927340928252147, 10140375000222764666, 11947349879489519683, 6322744121917232625, 15912133709417002642, 13469068507586061070, 3501366898748748726
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int out_data[] = {
    14618999411575652262, 1768056650665639202, 2042342086665598504, 3909918460685516018, 8366619663897057840, 10686944273734967803, 6219708618376441610, 841527863470925288, 9351072830221605090, 11199299011837345547, 248862610728821377, 11995963364878953394, 6478481407392964299, 5939361736055121990, 14561128696338360836, 12051283962114429380
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, *in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u64m2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse64m2_v_i64 (vbool64_t mask, int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -13662188953869639245, 6663509282405520400, -5783062216313628566, 4266177320171850879, 8508563853259010510, -3385221360332191833, 4904165194641672079, 841527863470925288, 7496034807530672018, 8014296722487870612, 248862610728821377, 4159464663136604952, 6478481407392964299, 5939361736055121990, -6953029702677688796, 12051283962114429380
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
