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
    int A,B,a,b,P;
    while(scanf("%d-%d", &A, &B) != EOF) {
        printf("%d-", A);
        for(P=1,a=b=0;; P*=10) {
            a += A%10 * P; A/=10;
            b += B%10 * P; B/=10;
            if(a<b && A==B || a>=b && A+1==B)
                break;
        }
        for(; b<P; P/=10)
            putchar('0');
        if(b!=0) printf("%d", b);
        putchar('\n');
    }
    return 0;
}
