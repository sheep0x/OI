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

int main(void)
{
    int N, has_class, ans = 0, last_class = -1;

    scanf("%d", &N);
    for (int t = 0; t < N; t++) {
        scanf("%d", &has_class);
        if (has_class) {
            if (last_class != -1 && t - last_class == 2)
                ans++; /* didn't go home during break */
            ans++;
            last_class = t;
        }
    }
    printf("%d\n", ans);

    return 0;
}
