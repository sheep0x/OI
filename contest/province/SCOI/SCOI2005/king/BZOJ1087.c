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

#define maxN 9
#define maxK (maxN*maxN)

typedef long long lint;

int N, K;
lint f[maxN+1][maxK+1][1<<(maxN+1)];

int main(void)
{
    int r, c, k, s, mask;
    char valid;
    lint ans;

    scanf("%d%d", &N, &K);
    for(k=0; k<=K; k++)
        memset(f[N][k], 0, sizeof(f[N][k][0])*(1<<(N+1)));
    f[N][0][0]=1;
    for(r=1; r<=N; r++) {
        mask = 1;
        for(c=1; c<=N; c++) {
            for(s=(1<<(N+1))-1; s>=0; s--) {
                valid = 1;
                if(s & mask & ((s & mask) << 1)) valid = 0;
                if(s &~mask & ((s &~mask) << 1)) valid = 0;
                if(s>>N && (s&1 || c!=1 && s&2)) valid = 0;
                if(c!=N && (s>>(N-1))&1 && s&1 ) valid = 0;
                if(!valid)
                    for(k=0; k<=K; k++) f[c][k][s] = 0;
                else if(c==1)
                    for(k=0; k<=K; k++)
                        f[1][k][s] = f[N][k-(s&1)][s>>1       ]
                                   + f[N][k-(s&1)][s>>1 | 1<<N];
                else if(s&1)
                    for(k=0; k<=K; k++)
                        f[c][k][s] = f[c-1][k-1][s>>1];
                else for(k=0; k<=K; k++)
                    f[c][k][s] = f[c-1][k][s>>1       ]
                               + f[c-1][k][s>>1 | 1<<N];
            }
            mask = mask<<1|1;
        }
    }

    ans = 0;
    for(s=(1<<(N+1))-1; s>=0; s--)
        ans += f[N][K][s];
    printf("%lld\n", ans);
    return 0;
}
