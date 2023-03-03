/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    8884599225583890608, 5564542730603458858, 13922182482533206547, 9710063343202172505, 7961566572181711227, 12555424440426003013, 10357746802970643928, 12599228007137391198, 3099973562107570855, 12016065439621630071, 8668127281850217339, 9340154736276290055, 1769804942734034209, 8596431963460256855, 8247323258041061620, 14529230374545951502
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    11973209935095913232, 5050004345077894064, 13406933820203623601, 4444244227445016298, 2110791056927068544, 16909896677568475101, 18049681166562458933, 10379118003679982038, 13466439015585522439, 6929219003239434331, 15797401746576613085, 10625095571839662505, 9798243634492928611, 2732342776294166374, 2291074396223193914, 11146100931447889000
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int out_data[] = {
    14907079725646644456, 6718407602695532882, 2432938521501320174, 953106825368944464, 14799812440622768707, 1227861201711653148, 2584440971473453814, 15240027940826193093, 8418198868430384934, 2682530261810207090, 16766924531159189117, 17316133115980368942, 17393351706566985831, 9528615650934607474, 481815507922096565, 129347550199340686
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, *in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i64m8_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse64m8_v_i64 (vbool64_t mask, int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    132443428986197493802140439024573669248, 37384866186810438481510211854673168756, 33871814065125918814448996053919979179, 9254727647170782084906620203492762321, 117829692001821262277694290349886173489, 15416318541421332338677102118258934925, 26768985209745511406088331985747541392, 192012586861613756432859139429826595415, 26096193932698062582720203923329498571, 32233459169676792468690490131881403390, 145337835961264631697001989233453499663, 161735362737214755627650146825905471810, 30782839820993700539536474351972292679, 81912096149221921184355231708642734270, 3973688244570774377942812888755335300, 1879320355229367939116547010931410372
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
