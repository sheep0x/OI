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
    int i, a, b, sum=0;
    for(i=0; i<12; i++) {
        scanf("%d.%d", &a, &b);
        sum += 100*a+b;
    }
    sum = (sum+6)/12;
    printf("$%d.%d\n", sum/100, sum%100);
    return 0;
}
