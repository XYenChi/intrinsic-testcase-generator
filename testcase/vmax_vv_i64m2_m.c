/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    221284525212641148, 10133331191651402747, 9687934757921667172, 1487053272622626544, 17871855085590734595, 12942821084423268348, 10771997728241725286, 6219784966818125524, 10036171588414839380, 10566703833630707911, 6509714031001903835, 16495855250302484120, 9257768984677061997, 11765969142295358395, 12013461581322437895, 8380018211815883494
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    12318459280018715512, 18370547929408654225, 4943519837686922157, 6361779123841802464, 1573065058473336882, 12040795553655266660, 7384697138961269478, 3144793573601795276, 14527756930775387067, 8994846422206596362, 2387158140527573584, 14769813329991412653, 10435796910027508712, 11763210576272546017, 9052390722584311198, 5643776349394605296
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int out_data[] = {
    424291983596874872, 1295596509983319613, 2850862724510387507, 5927521067175157889, 9373686911931376109, 7439239877205401210, 11550078058019939182, 15262984779565551207, 9451084252644728755, 293988253029161628, 9404044035303029644, 8058154942269966241, 5881329092624529739, 3004008604157009939, 4543009731694726301, 2482239186836455652
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, *in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i64m2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse64m2_v_i64 (vbool64_t mask, int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    424291983596874872, 1295596509983319613, 2850862724510387507, 6361779123841802464, 17871855085590734595, 12942821084423268348, 10771997728241725286, 15262984779565551207, 9451084252644728755, 10566703833630707911, 9404044035303029644, 16495855250302484120, 5881329092624529739, 11765969142295358395, 4543009731694726301, 8380018211815883494
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
