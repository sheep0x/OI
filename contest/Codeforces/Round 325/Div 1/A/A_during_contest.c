/*
 * Copyright 2015 Chen Ruichao <linuxer.sheep.0x@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

#define maxN 4000
#define maxV 1000000

int N;
long v[maxN], d[maxN], p[maxN], gone[maxN];
int remain_cnt, remain[maxN];

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%ld%ld%ld", &v[i], &d[i], &p[i]);
        gone[i] = 0;
    }

    /* by using lazy delete, array can be fast enough */
    /* however, we must use gone == 1 instead of p < 0, otherwise children
       can run away multiple times LOL. */
    remain_cnt = 0;
    for (int i = 0; i < N; i++) {
        if (gone[i]) continue;

        remain[remain_cnt++] = i;
        for (int j = i+1, dis = 1; j < N && dis <= v[i]; dis++) {
            while (j < N && gone[j])
                j++;
            if (j < N) { /* don't forget this check! */
                p[j] -= v[i] - dis + 1;
                j++;    /* don't forget this line!!! */
            }
        }
        gone[i] = 1; /* not necessary but makes me comfortable */

        long sum_d = 0; /* be careful, don't let it overflow */
        for (int j = i+1; j < N; j++) {
            if (gone[j]) continue;

            p[j] -= sum_d;
            if (p[j] < 0) {
                gone[j] = 1;
                sum_d += d[j];
                if (sum_d > maxV)
                    sum_d = maxV;
            }
        }
    }

    printf("%d\n", remain_cnt);
    for (int i = 0; i < remain_cnt; i++)
        printf("%d ", remain[i] + 1); /* number starts from 1 */
    putchar('\n');

    return 0;
}
