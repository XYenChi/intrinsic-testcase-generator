/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    9403135962734694070, 11482476504051402389, 14562572372875100355, 11131795450474718936, 16489248278665077568, 8922770107453446923, 10413281661786319466, 8459218120292042484, 1845179173889386297, 10721047113668484679, 18389383618491003089, 16241771262266029704, 12725483176572179504, 11895202528460130568, 14932655969947013775, 9345428402659349015
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    13524241229104098327, 7383001601840809569, 2175199505121292072, 1244177848366616260, 5996196332484523602, 5913169267596037478, 9690609489557860387, 13313864149356571590, 5702621748293060167, 8258631858657998824, 6020638193718169376, 12755991061932552665, 15464232065751755966, 5766354780626904661, 8954489041026670435, 13536575231385975032
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u64m2(op1, op2, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    4480633118129240781, 418734032182660342, 16737771877996392427, 12375973298841335196, 4038700537440049554, 14835939375049484401, 1657147077634628237, 3326338195939062458, 7547800922182446464, 532934898616931887, 5963277738499620849, 10551018250489030753, 9742971168614383854, 17661557309087035229, 5440400937264132594, 4435259560335772431
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
    const uint64_t data1[] = {
    3680889415614922436, 14165628052358090967, 15716840359603120258, 15835021254590270755, 5924122409832634817, 1886094713148854175, 16795294635051890025, 10070257044651731223, 15028469115943975113, 10204988099016076471, 6274149392753701947, 12907303696269503080, 8754176192639898054, 11502666973291455773, 16518230909544294584, 9051596203858375636
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    9218120345962905499, 9555574850582578840, 13040168856547913060, 4367145726267949964, 1406336622256195182, 4713760526145953330, 14421842602070985636, 12228255822843616886, 14026802773558305494, 9333554186776981287, 6391029850649319930, 6910739594394764684, 17072024898322206723, 11689839283696356337, 13936530291067136769, 10747188770669159178
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    12899009761577827935, 5274458829231118191, 10310265142441481702, 1755422907148669103, 7330459032088829999, 6599855239294807505, 12770393163413324045, 3851768793785796493, 10608527815792728991, 1091798212083506142, 12665179243403021877, 1371299216954716148, 7379457017252553161, 4745762183278260494, 12008017126901879737, 1352040900817983198
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
