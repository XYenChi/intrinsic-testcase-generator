/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7639556530207851857, -3257838359566060799, -2885485152289354507, -4621692798342593776, -8556194773940736916, 7024884965886362428, 7906685099164868268, 1051478948379472748, -5737920688289371602, -3057763209855796660, 6544739833477405414, 4524057346936295454, 2597497195953833844, 4154782160693818070, -3958868574263194380, -4036703303388953447
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -6711333845040500953, 7380416445984241912, -6000296132138498917, -5605941516245533156, 9107136704052316785, 738217507396035022, 4410623091146415126, 6204316881963974789, -3415194964957442443, -3799804982526873728, -8599774808817439631, -6336074862428238805, 2112030483068580644, 27596336879968813, -8678733065524517307, 5203556613960352415
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_i64m1(op1, op2, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    4095853698461198806, 4122578086418181113, 9560962789281698192, 8219109759121424684, 550941930111579869, 7763102473282397450, 12317308190311283394, 7255795830343447537, 9293628420462737571, 11589175881326881228, 16391709098369517399, 16634726558217608265, 4709527679022414488, 4182378497573786883, 5809142433921839929, 1166853310571398968
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
    const int64_t data1[] = {
    2139039183535161165, -4325498631595051613, 5690839492660519942, 1941732053591096718, 4912641861888089460, 1283705028833242021, -5890950760156333640, -7832327420578765565, -949757223824096701, 1178821431442094411, -1968017260444974490, -8462791355382724005, -2397213856100047749, 3460025320724030379, -5371919236472959834, -6462881208542544559
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -4854863253665231310, -430447843163554198, 3795997150955761052, 6729308578034100920, -997471581234040610, -3713996248033054093, -2453115186218158864, 2884432795528283723, 7535786107703877019, -5240366732023908427, 233805023913907005, 2648772769670768088, 6411103919064130692, -436774347619325437, 5689988569008707469, 6605775020755230945
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    15730920003579481471, 13690797598950945805, 9486836643616280994, 8671040631625197638, 3915170280654048850, 16016452854509739544, 10102678127335059112, 13498849448659069774, 6586028883879780318, 14385198773127737600, 16712531837178484131, 12632725487997595699, 4013890062964082943, 3023250973104704942, 318069332535747635, 142893812212686386
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
