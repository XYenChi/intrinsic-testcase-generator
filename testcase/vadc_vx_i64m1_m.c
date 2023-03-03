/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    9948492330801568983, 5355596308358643624, 12873713990288312801, 9680042936195799592, 8291217518772510629, 5390273326093597322, 6860780378264167358, 9103256143917395180, 6468238210804677960, 11662051922577824177, 2389016630583240308, 16320870806901451678, 18310182253177889068, 14438583324081207186, 18070209405955890730, 13437752732587755883
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    60477874813808596, 13110893539423994616, 4104334221908999856, 11378033020910519178, 7281829056518203085, 12686036800289900769, 15117443593841098503, 9071855665111478800, 5766968657854493797, 13312574218558460826, 6174652784435738526, 1359487978403302547, 14057946814690952473, 4775197474256782684, 10334127545483668985, 8148940334684257161
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int out_data[] = {
    5534419659388564913, 2541824108964443878, 2655030203901914259, 17491611911525917799, 4718962584420281864, 6205599021948701260, 2083500318574969646, 17260775794855551654, 12102815835589254548, 15838522948550998308, 7264938630569704363, 4403424083127459386, 2340853610002850874, 5553631673746561661, 4622392062237797007, 14192440907820475347
    };
    const int64_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, *in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse64m1_v_i64 (vbool64_t mask, int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    10008970205615377579, 18466489847782638240, 16978048212197312658, 21058075957106318770, 15573046575290713715, 18076310126383498091, 21978223972105265862, 18175111809028873981, 12235206868659171758, 24974626141136285003, 8563669415018978834, 17680358785304754225, 32368129067868841542, 19213780798337989870, 28404336951439559716, 21586693067272013044
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
