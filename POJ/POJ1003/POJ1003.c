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

#define maxN 276
#define eps 1e-9

double C, L[maxN+1];

int main(void)
{
    int N, Top, Bot, Mid;

    L[0] = 0;
    for(N=1; N<=maxN; N++)
        L[N] = L[N-1] + 1.0/(N+1);

    while(scanf("%lf", &C), C > eps) {
        Bot = 1, Top = maxN;
        while(Bot < Top) {
            Mid = (Top+Bot) >> 1;
            if(L[Mid] >= C - eps)
                Top = Mid;
            else Bot = Mid + 1;
        }
        printf("%d card(s)\n", Bot);
    }

    return 0;
}
