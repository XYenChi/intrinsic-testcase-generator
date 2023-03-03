/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4129460695, 294677103, 1485974260, 670075326, 1704593372, 2967430250, 1255728833, 1174071527, 2695998075, 2664709238, 550857996, 1485819770, 1103601779, 4263316309, 357500360, 4032757764
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3640124146, 3705463274, 2540276212, 728170774, 3072771034, 4021645119, 950821206, 3241385243, 581481275, 4056755141, 486556294, 4192354337, 3226931304, 1000280158, 3505402656, 3826981454
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    const int out_data[] = {
    2486223390, 64707028, 1594953772, 531860002, 697360139, 2927812019, 3567994436, 4143470163, 3294799235, 3457104100, 1099954941, 3629355826, 1692280778, 3800288825, 908609377, 2236537946
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    15031749588313664860, 1091915182919922250, 3774785065917256892, 487929269303582326, 5237825138927346787, 11933951383813261769, 1193973606970027034, 3805618125987746224, 1567672401343344860, 10810072903983796658, 268023426153981765, 6229082960389198316, 3561247129497470594, 4264510714970785647, 1253182712373565537, 15433289173539046802
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
