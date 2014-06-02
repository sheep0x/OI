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
#include <stdint.h>

#define maxN 100
#define maxM 6
#define maxST (1 << ((maxM+1)*2))
#define NegInfi (INT32_MIN + maxN*maxM*1000)

int ____[maxST], _____[maxST];
int *f=____, *pf=_____;
int mask, ans;

void roll_f(void)
{
    int* tmp = pf;
    pf = f;
    f = tmp;
}

void init(int* f)
{
    f[0] = 0;
    for(int s=1; s<mask; s++)
        f[s] = NegInfi;
}

// XXX This function only checks the state itself; current column position
//     is not taken into account. (That is, l[ll]rrr will be considered valid.)
// If l is +1 and r is -1, then sum is the number of unbalanced l's.
char is_valid(int s)
{
    int sum = 0;
    for(; s; s>>=2) {
        register int x = s&3;
        if(x == 1) sum++;
        if(x == 2) sum--;
        if(x == 3 || sum < 0)
            return 0;
    }
    return sum == 0;
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

// Since nested function is a GNU extension, we use a macro instead.
#define update(nx) updatev(nx, pf[s] + v)
#define updatev(nx, val)                \
    do {                                \
        int ns = bs | ((nx) << (c*2));  \
        if(f[ns] < (val))               \
            f[ns] = (val);              \
    } while(0)

void next_cell(int c, int v)
{
    init(f);
    for(int s=0; s<mask; s++) {
        if(!is_valid (s))
            continue;

        // If s is __l[_r]lr, then x is _r and bs is __l[__]lr.
        int x = s>>(c*2) & 15;
        int bs = s & ~(15 << c*2);

        // XXX invalid states could be updated
        switch(x) {
            case __:
                update(lr);
                if(bs != 0)
                    updatev(__, pf[s]);
                break;

            case l_:
            case _l:
                update(l_);
                update(_l);
                break;

            case r_:
            case _r:
                update(r_);
                update(_r);
                break;

            case lr:
                if(bs == 0 && ans < pf[s] + v)
                    ans = pf[s] + v;
                break;

            case rl:
                update(__);
                break;

            case ll:
                // find r for second l & turn it into l (ll_rr -> ___lr)
                for(int j=c+1, sum=0;; j++) {
                    int x = s>>(j*2) & 3;
                    if(x == 1) sum++;
                    if(x == 2) sum--;
                    if(sum == 0) {
                        bs ^= 3 << j*2;
                        update(__);
                        break;
                    }
                }
                break;

            case rr:
                // find l for first r & turn it into r (ll_rr -> lr___)
                for(int j=c, sum=0;; j--) {
                    int x = s>>(j*2) & 3;
                    if(x == 2) sum++;
                    if(x == 1) sum--;
                    if(sum == 0) {
                        bs ^= 3 << j*2;
                        update(__);
                        break;
                    }
                }
                break;
        }
    }
}
#undef update
#undef updatev

int main(void)
{
    int N, M;
    scanf("%d%d", &N, &M);
    mask = 1 << (M+1)*2;
    ans = NegInfi;
    init(pf);

    while(N--) {
        // passive, column M to col 0
        for(int s=0; s<mask; s++)
            f[s] = s&3 ? NegInfi : pf[s>>2];
        roll_f();

        // active, col i to col i+1
        for(int i=0, v; i<M; i++) {
            scanf("%d", &v);
            next_cell(i, v);
            roll_f();
        }
    }

    printf("%d\n", ans);

    return 0;
}
