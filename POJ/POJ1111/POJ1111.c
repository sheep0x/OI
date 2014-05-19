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
#include <string.h>

#define maxS 20

int R,C,ans;
char G[maxS+2][maxS+2];
char vis[maxS+1][maxS+1];

#define tryEdge(r,c)   if(G[r][c]=='X') floodfill(r,c); else ans++
#define tryCorner(r,c) if(G[r][c]=='X') floodfill(r,c)
void floodfill(int r, int c)
{
    if(vis[r][c]) return;
    vis[r][c] = 1;

    tryEdge(r-1, c);
    tryEdge(r+1, c);
    tryEdge(r, c-1);
    tryEdge(r, c+1);

    tryCorner(r-1, c-1);
    tryCorner(r-1, c+1);
    tryCorner(r+1, c-1);
    tryCorner(r+1, c+1);
}

int main(void)
{
    int r,c,i;

    while(1) {
        scanf("%d%d%d%d", &R, &C, &r, &c);
        if(R==0) break;
        scanf(" ");

        memset(G[0]  , '.', sizeof(G[0][0])*(C+2));
        memset(G[R+1], '.', sizeof(G[0][0])*(C+2));
        for(i=1; i<=R; i++) {
            gets(G[i]+1);
            G[i][0] = G[i][C+1] = '.';
        }

        for(i=1; i<=R; i++)
            memset(vis[i]+1, 0, sizeof(vis[0][0])*C);
        ans=0;
        floodfill(r,c);
        printf("%d\n", ans);
    }

    return 0;
}
