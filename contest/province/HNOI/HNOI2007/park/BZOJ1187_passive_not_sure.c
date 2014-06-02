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

// Probably one of the worst programs I've ever written.
// XXX Accepted on BZOJ, but still NOT sure if the program is correct.
// XXX line length exceeds 80 columns

#include <stdio.h>
#include <stdint.h>

#define maxN 100
#define maxM 6
#define maxST (1 << ((maxM+1)*2))
#define NegInfi (INT32_MIN + maxN*maxM*1000)

int N, M, ans;
int *f, *pf;    // pf - previous f

int max(int a, int b)
{
    return a>b ? a : b;
}

void swap_f(void)
{
    int* tmp = f;
    f = pf;
    pf = tmp;
}

#define __ 0
#define l_ 1
#define r_ 2
#define _l 4
#define ll 5
#define rl 6
#define _r 8
#define lr 9
#define rr 10

int main(void)
{
    static int b1_[maxST], b2_[maxST];
    f=b1_, pf=b2_;

    scanf("%d%d", &N, &M);
    int mask = 1 << (M+1)*2;

    ans = NegInfi;
    for(int s=0; s < mask; s++)
        pf[s] = NegInfi;
    pf[0] = 0;

    while(N--) {
        for(int s=0; s < mask; s++)
            f[s] = s&3 ? NegInfi : pf[s>>2];
        swap_f();

        for(int i=0; i<M; i++) {
            int v;
            scanf("%d", &v);

            for(int s=0; s < mask; s++) {
                int x = s>>(i*2) & 15;

                char invalid = (x&3) == 3 || (x&12) == 12;
                int sum = 0;
                // "&& !invalid" seems to improve the performance greatly.
                // It's a good habit to use such "breaks".
                for(int j=0, tmp=s; j<=M && !invalid; j++) {
                    if((tmp&3) == 1) sum++;
                    if((tmp&3) == 2) sum--;
                    tmp >>= 2;
                    if(sum<0) invalid = 1;
                }
                if(invalid || sum != 0) {
                    f[s] = NegInfi;
                    continue;
                }

                int bs = s & ~(15 << i*2);
#               define ps(x) pf[bs | ((x) << i*2)]

                switch(x) {
                    case ll:
                    case rl:
                    case rr:
                        f[s] = NegInfi;
                        break;

                    case l_: case _l: f[s] = max(ps(l_), ps(_l)) + v; break;
                    case r_: case _r: f[s] = max(ps(r_), ps(_r)) + v; break;

                    case lr:
                        f[s] = ps(__) + v;
                        break;

                    case __:
                        // lr will make a cycle
                        if(s == 0) {
                            int happiness = ps(lr) + v;
                            if(ans < happiness) ans = happiness;
                            f[s] = 0;
                        } else {
                            f[s] = max(ps(__), ps(rl) + v);

#                           define bbs (bs & ~(3 << j*2))
#                           define y (bs>>(j*2) & 3)
                            for(int j=0; j<i; j++)
                                if(y == 2)
                                    f[s] = max(f[s], pf[bbs | 1<<(j*2) | rr<<(i*2)] + v);
                            for(int j=i+2; j<=M; j++)
                                if(y == 1)
                                    f[s] = max(f[s], pf[bbs | 2<<(j*2) | ll<<(i*2)] + v);
#                           undef y
#                           undef bbs
                        }
                        break;
                }
#               undef ps
            }
            swap_f();
        }
    }

    printf("%d\n", ans);

    return 0;
}
