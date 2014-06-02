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

#if (__STDC_VERSION__ >= 199901L)
#   include <stdbool.h>
#else
    typedef enum { false, true = !false } bool;
#endif

#include <stdio.h>
#include <string.h>

#define maxN 10000000
#define maxP 664579     /* number of prime numbers */

typedef long long lint;

lint R;
bool np[maxN+1];
int plist[maxP], pcnt;
lint fac[maxN+1], *inv=fac, f[maxN+1];   /* f[M] = φ(M!)/M! */
/* we use the same array for inverse and factorial to save memory space */

void work(void)
{
    int T, N, M, i, j;
    R=0; scanf("%d%d", &T, (int*) &R); /* only works on little-endian machines */
    N = R < maxN ? R : maxN;

    inv[1] = 1;
    f  [1] = 1;
    pcnt = 0;
    memset(np+1, false, sizeof(np[0])*N);
    for(i=2; i<=N; i++) {
        inv[i] = (-R/i*inv[R%i] % R + R) % R;
        if(!np[i]) {
            f[i] = f[i-1] * (i-1) % R * inv[i] % R;
            plist[pcnt++] = i;
        } else
            f[i] = f[i-1]; // (f[i] = f[i-1] * i * inv[i])
        for(j=0; j<pcnt && i*plist[j] <= N; j++) {
            np[i * plist[j]] = true;
            if(i % plist[j] == 0) break;
        }
    }

    fac[1] = 1;
    for(i=2; i<=N; i++)
        fac[i] = fac[i-1] * i % R;

    while(T--) {
        scanf("%d%d", &N, &M);
        printf("%d\n", (int)(fac[N]*f[M]%R));
    }
}

int main(void)
{
    freopen("cash.in" ,"r",stdin );
    freopen("cash.out","w",stdout);
    work();
    return 0;
}
