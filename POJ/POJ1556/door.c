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

#if (__STDC_VERSION__ >= 199901L)
#   include <stdbool.h>
#else
    typedef enum { false, true = !false } bool;
#endif

#include <stdio.h>
#include <math.h>

#define maxN 20

int N, n;
double x[maxN+1], y[4][maxN+1], mind[4][maxN+1];

bool visible(int c, int r, double X, double Y)
{
    int i;
    double ty;

    /* there's no need to use eps here */
    for(i=c+1; i<n; i++) {
        ty = Y - (Y-y[r][c]) * (X-x[i]) / (X-x[c]);
        if(ty<y[0][i] || ty>y[3][i] || (ty>y[1][i] && ty<y[2][i]))
            return false;
    }
    return true;
}

/* XXX expressions are not enclosed by parentheses */
#define closer(c, r) (tx=X-x[c], ty=Y-y[r][c], td = sqrt(tx*tx+ty*ty) + mind[r][c], td<ret)
#define tryComingFrom(c, r) if(visible(c,r,X,Y) && closer(c,r)) ret = td
double calcMinDis(double X, double Y)
{
    double ret = INFINITY;
    double td, tx, ty;      /* tmp */
    int i, j;

    tryComingFrom(0, 0);
    for(i=1; i<n; i++)
        for(j=0; j<4; j++)
            tryComingFrom(i, j);
    return ret;
}
#undef closer
#undef tryComingFrom

void work(void)
{
    int i;

    x[0]=0, y[0][0]=5;
    mind[0][0]=0;
    scanf("%d", &N);
    for(n=1; n<=N; n++) {
        scanf("%lf", x+n);
        for(i=0; i<4; i++) {
            scanf("%lf", y[i]+n);
            mind[i][n] = calcMinDis(x[n], y[i][n]);
        }
    }

    printf("%.2lf\n", calcMinDis(10, 5));
}

int main(void)
{
    freopen("door.in", "r",stdin );
    freopen("door.out","w",stdout);
    work();
    return 0;
}
