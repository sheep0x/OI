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
#include <math.h>

#ifdef ONLINE_JUDGE
#   define M_PI_2 1.57079632679489661923
#endif

int main(void)
{
    int N, i;
    double x, y, A;

    scanf("%d", &N);
    for(i=1; i<=N; i++) {
        scanf("%lf%lf", &x, &y);
        A = (x*x+y*y)*M_PI_2;
        printf("Property %d: This property will begin eroding in year %d.\n",
                i, (int)ceil(A/50)
              );
    }
    puts("END OF OUTPUT.");

    return 0;
}
