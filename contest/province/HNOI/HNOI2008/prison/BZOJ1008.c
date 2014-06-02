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

#define P 100003

typedef long long lint;

lint power(lint b, lint e)
{
    lint ret = 1;
    for(; e; e>>=1, b=b*b%P)
        if(e&1) ret = ret*b % P;
    return ret;
}

int main(void)
{
    lint M, N;

    scanf("%lld%lld", &M ,&N);
    M %= P;
    printf("%lld\n", ((power(M,N) - M * power(M-1,N-1)) % P + P) % P);

    return 0;
}
