/*
 * Copyright 2013 Chen Ruichao <linuxer.sheep.0x@gmail.com>
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
#include <string.h> /* POJ doesn't have memory.h */
#include <stdint.h>

#define maxN 20000
#define maxM 200000
#define maxV (maxN+2)
#define maxE ((maxN*2+maxM)<<1)

int V, hdr[maxV], nxt[maxE], dst[maxE], cap[maxE];
int layer[maxV];

char dinicBFS(void)
{
    static int Q[maxV];
    int Qhead=0, Qtail=0;
    int u,v,e;

    memset(layer, -1, sizeof(layer[0])*V);
    layer[0] = 0;
    Q[Qtail++] = 0;
    while(Qhead < Qtail) {
        u = Q[Qhead++];
        for(e=hdr[u]; e!=-1; e=nxt[e]) {
            v = dst[e];
            if(cap[e]>0 && layer[v] == -1) {
                layer[v] = layer[u]+1;
                if(v==V-1) return 1;
                Q[Qtail++] = v;
            }
        }
    }
    return 0;
}

int dinicDFS(void)
{
    static int Stop, eS[maxV-1];
    static int cur[maxV];
    int res=0;
    int u,e,f,i,back; /* back - 记录第一条饱和的边, 回退时回退到这条边之前 */

    memcpy(cur, hdr, sizeof(cur[0])*V);
    Stop=0;
    while(Stop>=0) {
        u = Stop==0 ? 0 : dst[eS[Stop-1]];
        if(u==V-1) {
            f=INT32_MAX;
            back=-1;
            for(i=0;i<Stop;i++)
                if(f > cap[eS[i]]) {
                    f = cap[eS[i]];
                    back = i;
                }
            for(i=0;i<Stop;i++) {
                cap[eS[i]  ] -= f;
                cap[eS[i]^1] += f;
            }
            res+=f;
            Stop=back;
            continue;
        }
        for(e=cur[u]; e!=-1; e=nxt[e])
            if(cap[e]>0 && layer[dst[e]] == layer[u]+1)
                break;
        cur[u]=e;
        if(e!=-1)
            eS[Stop++] = e;
        else {
            layer[u]=-1; /* 光靠cur[u]==-1是不能防止死递归的 */
            Stop--;
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

int main(void)
{
    int N,M,res;
    int u,v,c,a,b;

    /* 0, N+1 represent CoreA, CoreB respectively */
    scanf("%d%d",&N,&M);
    V=N+2;
    memset(hdr, -1, sizeof(hdr[0])*V);
    for(v=1;v<=N;v++) {
        scanf("%d%d",&a,&b);
        connect(v, N+1, a);
        connect(N+1, v, 0);
        connect(0, v, b);
        connect(v, 0, 0);
    }
    while(M--) {
        scanf("%d%d%d",&u,&v,&c);
        connect(u, v, c);
        connect(v, u, c);
    }

    res=0;
    while(dinicBFS()) res += dinicDFS();
    printf("%d\n", res);

    return 0;
}
