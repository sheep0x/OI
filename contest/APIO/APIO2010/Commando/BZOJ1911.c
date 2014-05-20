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

// This program uses the 'pop when not needed' version of slope optimization
// implementation.

#include <stdio.h>

#define maxN 1000000
typedef long long i64;
typedef int Array[maxN+1];
typedef i64 LArray[maxN+1];

int N;
i64 a, b, c;
LArray S, F, Y; // S - prefix sum, F - DP array (see ./note)
i64 *X = S;
int Q[maxN+1], Qhead, Qtail;    // monotone chain

void gen_point(int n)
{
    i64 s = S[n];
    Y[n] = F[n] + a*s*s - b*s;
}

// (Pj-Pi) * (Pk-Pi)
i64 cross(int i, int j, int k)
{
    i64 x1 = X[j]-X[i], y1 = Y[j]-Y[i];
    i64 x2 = X[k]-X[i], y2 = Y[k]-Y[i];
    return x1*y2 - x2*y1;
}

int main(void)
{
    scanf("%d%lld%lld%lld", &N, &a, &b, &c);
    S[0] = F[0] = 0;
    for(int i=1, x; i<=N; i++) {
        scanf("%d", &x);
        S[i] = S[i-1] + x;
    }

    gen_point(0);
    Qhead = Qtail = 0;
    Q[Qtail++] = 0;

    for(int i=1; i<=N; i++) {
#       define h Qhead
#       define t Qtail

        i64 s = S[i], k = 2*a*s;
        while(t-h > 1 && Y[Q[h+1]] - Y[Q[h]] > k * (X[Q[h+1]] - X[Q[h]]))
            h++;

        int j = Q[h];
        F[i] = Y[j] - k * S[j] + (a*s*s + b*s + c);

        gen_point(i);
        while(t-h > 1 && cross(Q[t-2], Q[t-1], i) > 0)
            t--;
        Q[t++] = i;

#       undef h
#       undef t
    }

    printf("%lld\n", F[N]);

    return 0;
}
