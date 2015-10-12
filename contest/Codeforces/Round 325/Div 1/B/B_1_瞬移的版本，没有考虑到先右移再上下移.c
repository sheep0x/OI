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
short safe[3][maxN];    // only need about N/3 columns
                        // whether i-th row is safe from t = 3j-2 to t = 3j
short f[3][maxN];       // can we reach row i on round j?

void solve(void)
{
    static char line[maxN+1];
    scanf("%d%d", &N, &K);

    memset(safe, -1, sizeof safe);  // all true (TODO can we init 2D array this way?)
    for (int i = 0; i < 3; i++)
        f[i][0] = 0;

    for (int i = 0; i < 3; i++) {
        scanf("%s", line);
        if (line[0] == 's')
            f[i][0] = 1;
        for (int t = 1; t < N; t++)
            if (line[t] != '.')
                safe[i][(t+2)/3] = 0;
    }

    int maxJ = (N+1)/3;
    for (int j = 1; j <= maxJ; j++) {
        f[0][j] = safe[0][j] && (f[0][j-1] || f[1][j-1]);
        f[1][j] = safe[1][j] && (f[0][j-1] || f[1][j-1] || f[2][j-1]);
        f[2][j] = safe[2][j] && (f[1][j-1] || f[2][j-1]);
    }

    short ans = f[0][maxJ]
             || f[1][maxJ]
             || f[2][maxJ];
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
