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
#include <stdlib.h>
#include <string.h> // for memset

#define maxN 400
#define maxM ((maxN)*2)     // stupid mistake

struct comb {
    int a, b;
    long v;
};

struct comb combs[maxM*maxM]; // 好随便...
int teammate[maxM+1];

int cmp(const void * p1, const void * p2)
{
    long v1 = ((struct comb *) p1)-> v;
    long v2 = ((struct comb *) p2)-> v;
    return v1 - v2;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    int M = N * 2;

    long pair_cnt = 0;
    for (int i = 2; i <= M; i++) {
        for (int j = 1; j < i; j++) {
            scanf("%ld", &combs[pair_cnt].v);
            combs[pair_cnt].a = j;
            combs[pair_cnt].b = i;
            pair_cnt++;
        }
    }
    qsort(combs, pair_cnt, sizeof(combs[0]), cmp);

    memset(teammate+1, 0, sizeof(teammate[0]) * M);
    while (pair_cnt > 0) { // a little wasteful but who cares
        struct comb * c = &combs[--pair_cnt];
        if (!teammate[c->a] && !teammate[c->b]) {
            teammate[c->a] = c->b;
            teammate[c->b] = c->a;
        }
    }

    for (int i = 1; i <= M; i++)
        printf("%d ", teammate[i]);
    putchar('\n');

    return 0;
}
