/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    18189920956161566322, 17942465704970776129, 9036793402500741930, 13297884812076392685, 11249064838690164638, 14755819510716835547, 6467557917628279686, 7570189128455812079, 9098604133304484163, 2822411631286934900, 9260183575685838305, 583798315326096166, 10335965597967523832, 11223468808942410831, 14000823161930910699, 9073173789384466474
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    10989957634900671182, 2290969441118655149, 8093151431212498399, 18090148942239204398, 17937740383442972656, 6561616449524963971, 147354940775662370, 14512460625935822907, 15032474662491029200, 17525372714886584849, 6962073128405899253, 4410985799568919605, 15433728356343545409, 5132297891326895733, 4963390991848841849, 940003757565673442
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int out_data[] = {
    11178633438467636527, 14513458896383044811, 10519904967796663119, 1301751625168741483, 6303820809663352408, 12930906145597972177, 13800545396121995096, 8285096038425930948, 4841081011591254005, 10938924259020150185, 1812685809157619809, 7251983193466395189, 9561371335681558529, 17611993708202346586, 9219645065770850479, 10776611895670864414
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, *in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i64m2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse64m2_v_i64 (vbool64_t mask, int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    203338458643630888879907789161700243695, 260407238508855790614294006286856116620, 95066207807919665268387029775767879670, 17310543165427168605789809935957251855, 70912089019387382397153604420533748304, 190806117194462791645899157297590575820, 89255826644277312809074247728608419857, 62719743958304299545817920816918320892, 44047079701726037096375358938832822815, 30874147062425287683880322626317956500, 16785803357840184904246652622638983745, 4233695571118844435748134255973745374, 98826005194997382136959506652710363128, 197667662047299024286490034450262272967, 129082620181626557937759787512230374822, 97778072590169735549272677751782656237
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