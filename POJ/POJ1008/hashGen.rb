#! /usr/bin/env ruby

=begin
Copyright 2014 Chen Ruichao <linuxer.sheep.0x@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
=end

#a=[]
#while s=gets; a << (s[0..-2]+"\0"); end
a = ["pop\u0000", "no\u0000", "zip\u0000", "zotz\u0000", "tzec\u0000", "xul\u0000", "yoxkin\u0000", "mol\u0000", "chen\u0000", "yax\u0000", "zac\u0000", "ceh\u0000", "mac\u0000", "kankin\u0000", "muan\u0000", "pax\u0000", "koyab\u0000", "cumhu\u0000", "uayet\u0000"]

P = 30
plist = []
pr = Array.new(P+1) {true}

(2..P).each {|j|
  plist << j if pr[j]
  plist.each {|i|
    break if j*i > P
    pr[i*j]=false
    break if j%i==0
  }
}

MOD = 31
plist.each {|i|
  plist.each {|j|
    h = a.collect {|s| (s[0].ord * i + s[1].ord * j) % MOD}
    if h.uniq==h
      printf("%d %d %p\n", i, j, h)
      map = Array.new(MOD) {0}
      h.each_with_index {|v,i| map[v]=i;}
      p map
    end
  }
}
