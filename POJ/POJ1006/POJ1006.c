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

int main(void)
{
    int T, p, e, i, d, ans;
    for(T=1;; T++) {
        scanf("%d%d%d%d", &p, &e, &i, &d);
        if(p==-1) break;
        ans = 5544*p + 14421*e + 1288*i - d + 21252;
        printf(
                "Case %d: the next triple peak occurs in %d days.\n",
                T, (ans-1) % 21252 + 1
              );
    }
    return 0;
}
