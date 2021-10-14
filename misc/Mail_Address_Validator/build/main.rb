#!/usr/bin/env ruby
require 'timeout'

$stdout.sync = true
$stdin.sync = true

pattern = /\A([\w+\-].?)+@[a-z\d\-]+(\.[a-z]+)*\.[a-z]+\z/i

begin
  Timeout.timeout(60) {
    Process.wait Process.fork {
      puts "I check your mail address."
      puts "please puts your mail address."
      input = gets.chomp
      begin
        Timeout.timeout(5) {
          if input =~ pattern
            puts "Valid mail address!"
          else
            puts "Invalid mail address!"
          end
        }
      rescue Timeout::Error
        exit(status=14)
      end
    }
    
    case Process.last_status.to_i >> 8
    when 0 then
      puts "bye."
    when 1 then
      puts "bye."
    when 14 then
      File.open("flag.txt", "r") do |f|
        puts f.read
      end
    else
      puts "What's happen?"
    end
  } 
rescue Timeout::Error
  puts "bye."
end
