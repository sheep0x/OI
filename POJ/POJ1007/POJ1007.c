/*
 * Copyright 2014 Chen Ruichao <linuxer.sheep.0x@gmail.com>
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

#define maxL 50
#define maxM 100

int id[maxM], icnt[maxM];
char s[maxM][maxL+1];

int icmp(const void* a, const void* b)
{
    int A = *(int*)a, B = *(int*)b;
    return icnt[A] != icnt[B] ? icnt[A] - icnt[B] : A - B;
}

int main(void)
{
    int L, M, i, j;
    int C, G, T;

    scanf("%d%d\n", &L, &M);
    for(i=0; i<M; i++) {
        C = G = T = 0;
        icnt[i] = 0;
        id[i] = i;
        for(j=0; j<L; j++) {
            scanf(" %c", &s[i][j]);
            switch(s[i][j]) {
                case 'A':      icnt[i] += T+G+C; break;
                case 'C': C++, icnt[i] += T+G  ; break;
                case 'G': G++, icnt[i] += T    ; break;
                case 'T': T++;
            }
        }
        s[i][L] = '\0';
    }
    qsort(id, M, sizeof(id[0]), icmp);
    for(i=0; i<M; i++) puts(s[id[i]]);

    return 0;
}
