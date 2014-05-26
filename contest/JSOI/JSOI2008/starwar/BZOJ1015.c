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

#define maxE 200000
#define maxV (maxE * 2)

// CCcnt - number of connected components
int hdr[maxV], nxt[maxE*2], dst[maxE*2], Ecnt;
int Tcnt, Tlist[maxV], hit[maxV];   // targets
int CCcnt, p[maxV]; // disjoint set

void connect(int s, int d)
{
    dst[Ecnt] = d;
    nxt[Ecnt] = hdr[s];
    hdr[s] = Ecnt++;
}

int root(int u)
{
    if(p[u] == -1)
        return u;
    return p[u] = root(p[u]);
}

void merge(int u, int v)
{
    int a = root(u), b = root(v);
    if(a != b) {
        p[b] = a;
        CCcnt--;
    }
}

void add_planet(int u)
{
    CCcnt++;
    for(int e=hdr[u]; e!=-1; e=nxt[e])
        if(!hit[dst[e]])
            merge(u, dst[e]);
}

int main(void)
{
    static int V, tmpE, ans[maxV];
    int u, v;

    scanf("%d%d", &V, &tmpE);
    memset(hdr, -1, sizeof(hdr[0])*V);
    Ecnt = 0;
    while(tmpE--) {
        scanf("%d%d", &u, &v);
        connect(u,v);
        connect(v,u);
    }

    memset(hit, 0, sizeof(hit[0])*V);
    scanf("%d", &Tcnt);
    for(int i=0; i<Tcnt; i++) {
        scanf("%d", &u);
        Tlist[i] = u;
        hit[u] = 1;
    }

    memset(p, -1, sizeof(p[0])*V);
    CCcnt = 0;
    for(int u=0; u<V; u++)
        if(!hit[u])
            add_planet(u);
    for(int i=Tcnt; i--;) {
        ans[i] = CCcnt;
        u = Tlist[i];
        hit[u] = 0;
        add_planet(u);
    }

    printf("%d\n", CCcnt);
    for(int i=0; i<Tcnt; i++)
        printf("%d\n", ans[i]);

    return 0;
}
