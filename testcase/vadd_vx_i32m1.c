/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1439018733, -75744529, -1901551331, -2081219984, -534937025, -95920952, 476796738, 582080540, -738755654, 718634143, 1852520911, -1869498939, 1867835937, -1946988338, 116396283, 743269551
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -2010159790, 1103215780, -73695652, -597488966, 1784915051, -1417404869, 759263012, -307487800, 155529127, -293824683, 1481116736, 1345878035, 1585362952, 1209992919, 57846680, -114395209
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_i32m1(op1, op2, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    845788773, 1027471251, 2319720313, 1616258346, 1249978026, 2781641475, 1236059750, 274592740, 3711740769, 424809460, 3333637647, 3771346392, 3453198889, 3557971877, 174242963, 628874342
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
    -405743619, 1563268839, 1242901066, -830836863, -1463621683, 1141346534, 393584816, 822631079, 1014503508, 1666369655, -2002290033, 522462269, -226003042, -704131950, -70509776, 1921763317
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    650523441, 182452031, -213938397, 2022473085, 1337233768, 344405361, 450214266, -1790682849, -1187408185, -2115319870, -1797501862, -387654681, -1590650681, -282464087, 1783441646, -865199790
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    244779822, 1745720870, 1028962669, 1191636222, 4168579381, 1485751895, 843799082, 3326915526, 4122062619, 3846017081, 495175401, 134807588, 2478313573, 3308371259, 1712931870, 1056563527
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
