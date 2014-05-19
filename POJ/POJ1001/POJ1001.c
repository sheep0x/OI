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

#if defined(_WIN32)     /* GCC predefined macro */
#   define LLU  "I64u"
#else
#   define LLU  "llu"
#endif

#include <stdio.h>
#include <string.h>

typedef unsigned long long lint;
#define maxDigitWidth "9"
#define maxDigitVal 1000000000
#define maxN 25
#define maxD (maxN*5)
#define maxBID ((maxD-1)/9+1)

typedef struct BigInt
{
    lint* v;
    int l;
} BigInt;

/* XXX maxD must be bigger than 6, because str is also used for reading input */
char str[maxD+1];
lint _a[maxBID+1], _b[maxBID+1], _c[maxBID+1];
BigInt ans={_a}, tmp={_b}, R={_c};

/* a*=b (restrictions: a!=0, b!=0, both a.l and b.l <= maxDigitVal) */
BigInt mul(BigInt a, BigInt b)
{
    int l, i, j;
    lint* v = tmp.v;

    l = a.l+b.l;
    memset(v, 0, sizeof(v[0])*l);
    for(i=0; i<a.l; i++)
        for(j=0; j<b.l; j++)
            v[i+j] += a.v[i] * b.v[j];
    for(i=0; i<l-1; i++)
        if(v[i] >= maxDigitVal) {
            v[i+1] += v[i]/maxDigitVal;
            v[i] %= maxDigitVal;
        }
    if(v[l-1]==0) l--;

    tmp.v = a.v;
    a.v = v, a.l = l;
    return a;
}

int main(void)
{
    int i, N, intR, fracR, fracD;
    char* p;

    while(scanf("%6s%d", str, &N) != EOF) {
        sscanf(str, "%d.%d", &intR, &fracR);
        fracD = 5 - (strchr(str, '.') - str);
        for(i=0; i<fracD; i++) intR *= 10;
        R.v[0] = intR + fracR;
        R.l = 1;
        ans.l=1, ans.v[0]=1;

        fracD *= N;
        for(; N; N>>=1) {
            if(N&1) ans = mul(ans, R);
            R = mul(R, R);
        }

        p = str + sprintf(str, "%"LLU, ans.v[ans.l-1]);
        for(i=ans.l-2; i>=0; i--)
            p += sprintf(p, "%0" maxDigitWidth LLU, ans.v[i]);
        while(fracD>0 && p[-1]=='0')
            p--, fracD--;
        *p = '\0';
        N = p-str;  /* number of significant digits */
        if(fracD == 0) {
            puts(str);
        } else if(N > fracD) {
            printf("%.*s.%s\n", N-fracD, str, str+N-fracD);
        } else {
            putchar('.');
            if(N < fracD)
                printf("%0*d", fracD-N, 0);
            puts(str);
        }
    }

    return 0;
}
