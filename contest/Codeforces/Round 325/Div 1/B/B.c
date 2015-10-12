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
#include <string.h>

#define maxN 100

int N, K; // K is useless
short f[3][maxN];   // at first: is is safe to be in row i at time j?
                    // in the end: is it possible to reach row i at time j?

void solve(void)
{
    static char line[maxN+1];
    scanf("%d%d", &N, &K);

    f[0][0] = f[1][0] = f[2][0] = 0;

    for (int i = 0; i < 3; i++) {
        scanf("%s", line);
        if (line[0] == 's')
            f[i][0] = 1;
        for (int t = 1; t < N; t++)
            f[i][t] = (line[t] == '.');
    }

    for (int j = 1; j < N; j++) {
        if (j % 3 == 1) {
            short from[3];
            for (int i = 0; i < 3; i++)
                from[i] = f[i][j-1] && f[i][j];

            f[0][j] &= from[0] || from[1];
            f[1][j] &= from[0] || from[1] || from[2];
            f[2][j] &= from[1] || from[2];
        } else {
            for (int i = 0; i < 3; i++)
                f[i][j] &= f[i][j-1];
        }
    }

    short ans = f[0][N-1]
             || f[1][N-1]
             || f[2][N-1];
    puts(ans ? "YES" : "NO");
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
