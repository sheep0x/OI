#! /usr/bin/env ruby

l = 0
n = 0
while l < 5.20 + 1e-9
  n += 1
  l += 1.0/(n+1)
  printf "%3d   %5.4f\n", n, l
end
