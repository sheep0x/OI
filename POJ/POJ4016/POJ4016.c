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

int N, C, A, tA, bA, rA; /* total area, bedroom area, balcony area */
char T[9];

int main(void)
{
    scanf("%d%d", &N, &C);
    tA = bA = rA = 0;
    while(N--) {
        scanf("%d%s", &A, T);
        tA += A;
        if(T[2] == 'd') bA += A;
        if(T[2] == 'l') rA += A;
    }
    printf("%d\n%d\n", tA, bA);
    tA = ((tA<<1) - rA) * C;
    printf(tA&1 ? "%d.5\n" : "%d\n", tA>>1);
    return 0;
}
