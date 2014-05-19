#! /usr/bin/env ruby

0.upto(25) do |k|
  ans = 1
  (26-k).upto(25) {|i| ans*=i}
  2.upto(k) {|i| ans/=i}
  k.times {ans<<=2}
  puts "%2d%20d    %f" % [k, ans, Math.log2(ans)]
end
