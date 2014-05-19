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

#define maxN    100000
#define maxlogN 16
#define minV    (-100000)

#define max(a,b) ((a) > (b) ? (a) : (b))

/*  intervals                                         */
/*  the i-th element belongs to the b[i]-th interval  */
/*  l[i] = r[i-1]+1                                   */
int Icnt, b[maxN+1], r[maxN+1];
/*  sparse-table  */
int iLog[maxN+1], st[maxlogN+1][maxN];

int main(void)
{
    int N, Q, L, R, ans;
    int x, y, i, e;

    for(e=0, i=1; i<=maxN; i++) {
        if(i >= 1<<(e+1)) e++;
        iLog[i] = e;
    }

    while(scanf("%d%d", &N, &Q) == 2) {
        Icnt = 0;
        y = minV-1; /* y - previous x */
        for(i=1; i<=N; i++) {
            scanf("%d", &x);
            if(x!=y) r[Icnt++] = i-1;
            y=x;
            b[i] = Icnt;
        }
        r[Icnt] = N;

        for(i=1; i<=Icnt; i++)
            st[0][i] = r[i]-r[i-1];
        for(e=1; 1<<e <= Icnt; e++)
            for(i=1; i <= Icnt-(1<<e)+1; i++)
                st[e][i] = max(st[e-1][i], st[e-1][i+(1<<(e-1))]);

        while(Q--) {
            scanf("%d%d", &L, &R);
            x = b[L]+1;
            y = b[R]-1;

            /* RMQ */
            if(x<=y) {
                e = iLog[y-x+1];
                ans = max(st[e][x], st[e][y-(1<<e)+1]);
            } else ans = 0;

            /* partial intervals */
            x = r[x-1]+1;
            y = r[y];
            if(x<=R) ans = max(ans, x-L); else ans = max(ans, R-L+1);
            if(y>=L) ans = max(ans, R-y); else ans = max(ans, R-L+1);

            printf("%d\n", ans);
        }
    }

    return 0;
}
