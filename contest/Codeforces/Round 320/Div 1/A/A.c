/*
 * Copyright 2015 Chen Ruichao <linuxer.sheep.0x@gmail.com>
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

#define eps 1e-10
#define INF 1e10

long a, b;

// TODO too ugly... any way to improve?

double findInc(void)
{
    if (a - b < 0)
        return INF;
    if (a - b == 0)
        return b;
    if (a - b < b * 2)      // XXX forgot this!
        return INF;

    double p = a - b;
    long L = 1, H = a-b;
    while (L < H) {
        long M = (L+H+1)/2;
        double x = p / (2*M);
        if (x + eps >= b)
            L = M;
        else
            H = M-1;
    }
    return p / (2*L);
}

double findDec(void)
{
    if (b > a)
        return INF;

    double p = a + b;
    long L = 1, H = a+b;
    while (L < H) {
        long M = (L+H+1)/2;
        double x = p / (2*M);
        if (x + eps >= b)
            L = M;
        else
            H = M-1;
    }
    return p / (2*L);
}

int main(void)
{
    scanf("%ld%ld", &a, &b);

    double ans1 = findInc();  // slope == 1
    double ans2 = findDec();  // slope == -1
    double ans = ans1 < ans2 ? ans1 : ans2;

    if (ans != INF)
        printf("%.9f\n", ans);
    else
        puts("-1");

    return 0;
}
