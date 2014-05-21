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
#include <string.h> // for memset
#include <stdint.h>

#define maxS 100
#define maxV (maxS*maxS+2)
#define maxE ( (maxS*(maxS-1) << 1) + maxS*maxS << 1 )

int V, hdr[maxV], nxt[maxE], dst[maxE], cap[maxE];

int calcMaxFlow(void)
{
    static int h[maxV], hcnt[maxV+1];
    static int cur[maxV];
    static int Stop, eS[maxV-1];
    int res=0;
    int u,e,f;

    memset(cur, -1, sizeof(cur[0])*V);
    memset(h, 0, sizeof(h[0])*V);
    memset(hcnt, 0, sizeof(hcnt[0])*V); // no need to set hcnt[V]
    hcnt[0] = V;

    Stop = 0;
    while(h[0]<V) {
        u = Stop==0 ? 0 : dst[eS[Stop-1]];
        if(u == V-1) {
            f = INT32_MAX;
            for(int i=0; i<Stop; i++)
                if(f > cap[eS[i]])
                    f = cap[eS[i]];
            while(Stop > 0) {
                Stop--;
                cap[eS[Stop]  ] -= f;
                cap[eS[Stop]^1] += f;
            }
            res += f;
            continue;
        }
        if(cur[u] == -1) cur[u] = hdr[u];
        for(e=cur[u]; e!=-1; e=nxt[e])
            if(cap[e]>0 && h[dst[e]] == h[u]-1)
                break;
        cur[u]=e;
        if(e!=-1) {
            eS[Stop++] = e;
        } else {
            if(--hcnt[h[u]] == 0) break;
            h[u]++;
            hcnt[h[u]]++;
            if(Stop>0) Stop--;
        }
    }

    return res;
}

void connect(int s, int d, int c)
{
    static int e=0;
    cap[e]=c;
    dst[e]=d;
    nxt[e]=hdr[s];
    hdr[s]=e++;
}

void connect2(int s, int d, int c)
{
    connect(s, d, c);
    connect(d, s, 0);
}

#define P(r,c) ((r)*M+(c)+1)
int main(void)
{
    int N, M, sum = 0;

    scanf("%d%d", &N, &M);
    V = N*M + 2;
    memset(hdr, -1, sizeof(hdr[0])*V);

    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++) {
            int v, p = P(i,j);
            scanf("%d", &v);
            sum += v;

            if((i^j)&1) {
                connect2(0, p, v);
            } else {
                connect2(p, V-1, v);
                if(i>0  ) connect2(P(i-1, j), p, INT32_MAX);
                if(i<N-1) connect2(P(i+1, j), p, INT32_MAX);
                if(j>0  ) connect2(P(i, j-1), p, INT32_MAX);
                if(j<M-1) connect2(P(i, j+1), p, INT32_MAX);
            }
        }

    printf("%d\n", sum - calcMaxFlow());

    return 0;
}
