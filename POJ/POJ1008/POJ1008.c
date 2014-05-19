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

const int HaabToNum[] = {0, 17, 6, 0, 7, 0, 9, 3, 12, 1, 11, 10, 0, 5, 0, 0, 0, 18, 8, 0, 14, 0, 2, 15, 0, 16, 0, 4, 0, 13, 0};
const char TzolkinName[][9] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

int main(void)
{
    int T, Y, M, D, tot;
    char c1, c2;

    scanf("%d", &T), printf("%d\n", T);
    while(T--) {
        scanf("%d. %c%c%*[^0-9]%d", &D, &c1, &c2, &Y);
        M = HaabToNum[(c1*5 + c2*13) % 31];
        tot = 365*Y + 20*M + D;

        Y = tot/260;
        tot %= 260;
        printf("%d %s %d\n", tot%13+1, TzolkinName[tot%20], Y);
    }

    return 0;
}
