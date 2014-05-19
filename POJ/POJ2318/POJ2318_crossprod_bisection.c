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
#include <string.h>

#define maxN 5000

int N, M, L, R, T, B;
int u[maxN+1], l[maxN+1];   /* cardboards */
int cnt[maxN+1];            /* bins */

int main(void)
{
    int i, x, y, lb, rb;
    int first_time = 1;

    while(scanf("%d",&N), N!=0) {
        if(!first_time) putchar('\n');
        first_time = 0;

        scanf("%d%d%d%d%d", &M, &L, &T, &R, &B);
        T-=B;
        for(i=1; i<=N; i++) {
            scanf("%d%d", u+i, l+i);
            u[i] -= l[i];
        }
        memset(cnt, 0, sizeof(cnt[0])*(N+1));

        while(M--) {
            scanf("%d%d", &x, &y);
            lb = 0, rb = N+1;
            while(rb-lb > 1) {
                i = (lb+rb) >> 1;
                if( (x-l[i])*T > u[i]*(y-B) )
                    lb=i;
                else rb=i;
            }
            cnt[lb]++;
        }

        for(i=0; i<=N; i++)
            printf("%d: %d\n", i, cnt[i]);
    }
    return 0;
}
