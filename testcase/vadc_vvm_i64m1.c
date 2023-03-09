/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    4642007711893020257, -3656726228127591303, -1295475472385950248, -4947049286598486569, -840358245848100462, 6071303955154633143, 3724809801645343146, 1734762469839575253, 5824115943862857234, 4466846396310215524, -6712977024699945164, -4654712297301085001, -8787371858166263285, -2776672256710956118, 3770700266723529633, -8900276681640706291
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4915116078463321964, 6245265788365459470, 3304667236532068781, 8891955799168699383, -6445928399005308153, 3828314724224090650, 3637979847557381169, -2787223141971693628, -7900140027189588653, -8009535507253205739, -50539393605605133, -3788000453488561829, -3028981715256658192, 4626676761552299000, 503967873898604719, 9138229075382303892
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    bool64_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    9557123790356342221, 2588539560237868168, 2009191764146118534, 3944906512570212814, -7286286644853408615, 9899618679378723794, 7362789649202724315, -1052460672132118375, -2076024083326731418, -3542689110942990214, -6763516418305550296, -8442712750789646829, -11816353573422921476, 1850004504841342882, 4274668140622134352, 237952393741597602
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
