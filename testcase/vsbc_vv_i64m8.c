/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1396563608643912384, 12398230762584119048, 1923632233582498938, 7817975710249989579, 12939581362444676017, 15945987408111827045, 15987092102954812600, 9474661037523676808, 6446560772549895390, 13015853963524820155, 2505615437963762691, 14001690266269150016, 16726906175357699169, 11559934706957872078, 7579428893494685978, 13902955029574940954
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17259876953774360974, 15774543489855930807, 15108749508329248165, 13415098443827793775, 17634438502099887857, 6387126170548937545, 7690247821227260001, 850275297281194092, 791085550825408249, 1179401662861043208, 9617042126168071049, 6860900310473594892, 2940910319942239655, 1111040443688001445, 4428855115438202433, 2841462696050451674
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i64m8 (data1_v, data2_v, vl);
        void vint64m8_t __riscv_vse64_v_i64 (int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    -15863313345130448590, -3376312727271811759, -13185117274746749227, -5597122733577804196, -4694857139655211840, 9558861237562889500, 8296844281727552599, 8624385740242482716, 5655475221724487141, 11836452300663776947, -7111426688204308358, 7140789955795555124, 13785995855415459514, 10448894263269870633, 3150573778056483545, 11061492333524489280
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