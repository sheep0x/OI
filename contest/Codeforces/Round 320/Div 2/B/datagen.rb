#! /usr/bin/env ruby

N = 400

puts N
for i in 2..N
  puts (i-1).times.collect { rand(1000000) }.join(' ')
end

