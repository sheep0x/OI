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

#include <cstdio>
#include <list>

struct Kid {
    long v, d, p;
};

int N;
std::list<Kid> line;

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        long v, d, p;
        scanf("%ld%ld%ld", &v, &d, &p);
        line.push_back({v, d, p});
    }

    // iterators won't be invalidated, yay!
    // However, we need to be careful not to remove stuffs in the updating
    // loop.
    // XXX 停工！我发现最简单的办法就是lazy delete！
    //while (!line.empty())
    //{
    //    long v = line.front().v;
    //    line.pop_front();
    //    for (auto&& kid : line)
    //    {
    //        kid.p -= v;
    //        if (--v <= 0)
    //            break;
    //    }
    //    for (auto&& kid : line)
    //    {
    //        if (kid.p < 0) /* not including == 0 */
    //            f
    //        for ()
    //    }
    //}

    return 0;
}
