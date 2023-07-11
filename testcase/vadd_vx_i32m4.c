/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1304551793, 1705019123, 913076326, -983451705, -1920050867, -1109873030, 1558480270, 1718749329, -111259566, -622321916, 1105254741, -1131205252, -1045588698, -1333743437, 1050051651, -1418202981
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    128863133, -479490870, 368122024, 999658575, -789747902, -186216757, -780627226, 1445208952, 933662968, -288985773, 526684241, -1818486177, 233119813, 1149159630, 181977887, -57394454
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_i32m4(op1, op2, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3119278636, 1225528253, 1281198350, 16206870, 1585168527, 2998877509, 777853044, 3163958281, 822403402, 3383659607, 1631938982, 1345275867, 3482498411, 4110383489, 1232029538, 2819369861
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1018220806, 1946626984, -1752918703, -410832393, -1404750460, -967077140, 451596405, -174039227, -1867250290, -885909438, 1839993346, -381371759, -2013353708, -2107490066, 432025343, 661188662
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2073397264, 1152291511, -830241091, -975243337, 1427898919, -1616734860, -1890282471, 600209826, -1286489977, -1726196791, -569408001, 683825863, 2090611985, 2038711392, 261746154, -11457075
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1055176458, 3098918495, 1711807502, 2908891566, 23148459, 1711155296, 2856281230, 426170599, 1141227029, 1682861067, 1270585345, 302454104, 77258277, 4226188622, 693771497, 649731587
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
