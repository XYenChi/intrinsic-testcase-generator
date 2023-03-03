/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1240939477, 2511758220, 2060666371, 363011989, 2705145210, 373414328, 4269560525, 2516916335, 1208331809, 4200494770, 2599537405, 1867133678, 3175596831, 3627740284, 1687093998, 156270578
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4040983995, 2280561730, 970894210, 3818324408, 3264901986, 1313833851, 1825492333, 443858950, 3167824322, 2614595162, 326435409, 4156222640, 2604223397, 3231449528, 1791590679, 721504715
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5014616565320670615, 5728219671544920600, 2000689048345611910, 1386097537995327512, 8832033968547387060, 490604384574817128, 7794050003666954825, 1117155841690948250, 3827782893596458498, 10982593303648302740, 848581056011973645, 7760223264410069920, 8269963566729254907, 11722859628438385952, 3022581881413644642, 112749958842775270
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
