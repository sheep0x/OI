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
#include <stdlib.h>

#define maxN 100000

int N, no[maxN+1];

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main(void)
{
    int i, j, v, cnt;
    char C, dupl;

    scanf("%d", &N);
    for(i=0; i<N; i++) {
        v = 0;
        for(j=0; j<7; j++) {
            scanf(" %*[-]"); C = getchar();
            if(C>='0' && C<='9')
                v = v*10 + C-'0';
            else if(C<'Q')
                v = v*10 + (C-'A')/3+2;
            else v= v*10 + (C-'Q')/3+7;
        }
        scanf("%*[-]");
        no[i] = v;
    }

    qsort(no, N, sizeof(no[0]), cmp);

    dupl = 0;
    no[N] = -1;
    for(i=0; i<N; i++) {
        for(cnt=1; no[i+1]==no[i]; cnt++) i++;
        if(cnt>1) {
            dupl = 1;
            printf("%03d-%04d %d\n", no[i]/10000, no[i]%10000, cnt);
        }
    }
    if(!dupl) puts("No duplicates.");

    return 0;
}
