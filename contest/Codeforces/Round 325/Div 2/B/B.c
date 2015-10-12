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

#define maxN 50

int N;
int a1[maxN-1], a2[maxN-1], b[maxN];
int p[maxN];    /* cost of path that crosses main avenue at i-th column */

int cmp(const void * a, const void * b)
{
    return *(int*)a - *(int*)b;
}

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N-1; i++) scanf("%d", &a1[i]);
    for (int i = 0; i < N-1; i++) scanf("%d", &a2[i]);
    for (int i = 0; i < N  ; i++) scanf("%d", & b[i]);

    for (int i = 1; i < N; i++) {
        a1[i] += a1[i-1];
        a2[N-i-1] += a2[N-i];
    }
    for (int i = 0; i < N; i++)
        p[i] = a1[i-1] + b[i] + a2[i];
    qsort(p, N, sizeof *p, cmp);
    printf("%d\n", p[0] + p[1]); /* 2*maxN*maxV within int16_t */

    return 0;
}
