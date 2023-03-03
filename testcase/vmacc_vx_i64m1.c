/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    9526030652217121115, 10836118609791184760, 1799270318535664148, 5239019700780706835, 957209603260244665, 14621960383782753951, 16063793204899747577, 199196657739009885, 15957217265824646650, 891474924191645648, 7640725569345184439, 9859086141164158014, 9859258113783859512, 16955779131396921132, 6467019548395482826, 11809083698134291529
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    2235929421188876646, 13275567753944301529, 13426080522292936432, 13060272053985886351, 16524926422263639960, 4295939041648983458, 2537804897551187241, 5656719852027693214, 18345531194885210151, 1796815033837902209, 17327601975186319312, 15992737129080984511, 109691543591361902, 570801752449431098, 2403335894223253175, 7870046320574505201
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (*out, vl);
    const int out_data[] = {
    4843403423757466066, 16118592316265833130, 6857922786559876238, 14164548871126818795, 13507604066894285742, 13760430176378843393, 13874166534547055367, 18039887998182793265, 13619633543734363921, 18434601669226330910, 7140992617553767598, 16637830356535597291, 359602813152982543, 15370204092695203692, 1581913119831323001, 4520441992618389295
    };
    const int64_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    21299532202439324705076190138734446356, 143855626794059605851290806735855331170, 24157148178031487813969788962825316174, 68423022588387765788520934038885727880, 15817818264559713121865789469965099142, 62815050478137086386964669947261985951, 40766773068644061665451890652110120424, 1126799688289823065014476175076213655, 292743627133746935970642676244302508071, 1601815546077053100018315481030767342, 132395451467242232080357862697741353566, 157673772988603798441207588470026118445, 1081477241166610749202265407070094367, 9678388442346855237390831894869366628, 15542420209302316631734627260393795551, 92938035707858151921756529752479131624
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