/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10052066685351034715, 14980079002254980692, 633328019216203978, 4671089140717582274, 4099793359325884670, 10079207912801693900, 1227303906453021677, 17229161178678144857, 14749261175132106243, 13481483022790774811, 4315201041145394112, 12768528926880860311, 889140945369084992, 861559148120426057, 4786166097896098815, 16154059245312009186
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    5894516881118704754, 4903461317166815164, 3577256316167766652, 12835634808687379856, 1040509113904195723, 202910794126046619, 9136620482958308795, 14085397735938218434, 10277147788890619195, 16808254392594128773, 6138925476127510576, 9530971510412903572, 3202083066951305544, 17713517731335446776, 13938518853320773031, 14744281264685012315
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int out_data[] = {
    10127869043450782522, 7832036549166542732, 17413525475349687741, 15915294029948028450, 736020498937186990, 536943538122916369, 10288689992100146335, 434151500407242982, 6458219290627083068, 3457727932500179212, 7006303057264930346, 5634701446615044615, 16670182475799280658, 551599136426057633, 3671033647741702474, 11850522584782265139
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, *in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse64m4_v_i64 (vbool64_t mask, int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    15946583566469739469, 19883540319421795856, 4210584335383970631, 17506723949404962131, 5140302473230080393, 10282118706927740519, 10363924389411330472, 31314558914616363291, 25026408964022725439, 30289737415384903584, 10454126517272904688, 22299500437293763883, 4091224012320390536, 18575076879455872834, 18724684951216871846, 30898340509997021502
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