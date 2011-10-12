##!/usr/bin/env ruby
#  stripchart
#
#  Created by Paolo Bosetti on 2010-09-14.
#  Copyright (c) 2010 University of Trento. All rights reserved.
#

# STDLIB:
require "yaml"

# RUBYGEMS:
require "rubygems"    # version >= 1.3.5 
require "serialport"  # sudo gem install serialport 
require "timeout"

# Charter client:
require "../ruby/charter_client"

# @author Paolo Bosetti
# Class for communicating with Arduino or with simulator.
# 
class Arduino

# Creates a new connection in unconnected state. Before using it,
# remember to call #connect  
# @example
#   ard = Arduino.new :simulate => true
#   ard.connect  
#   ard.command('?') {|l| puts l}
#   puts ard.command('?', "") {|l| l + "\n"}
#   table = ard.command("10/", Table.new(6)) {|l| l.split.map {|e| e.to_i}}
# @option cfg [String] :port ('/dev/ttyUSB0') The port to be used 
# @option cfg [Fixnum] :baud (115200) The baud rate (default to 115200) 
# @option cfg [String] :term ('>') The prompt character
  def initialize(cfg={})
    @cfg = {
      :port => "/dev/tty.usbserial-A6004aLr",
      :baud => 115200,
      :prompt => '>'
    }.merge(cfg)
    @port = nil
  end

# Connects to the arduino or to the simulator (via fifo)
  def connect
    return if @port
    case File.stat(@cfg[:port]).ftype
    when 'socket'
      @port = UNIXSocket.open(@cfg[:port])
    when 'characterSpecial'
      @port = SerialPort.new(@cfg[:port], @cfg[:baud], 8, 1, SerialPort::NONE)
    else
      raise ArgumentError, "#{@cfg[:port]} id not a valid port"
    end
    sleep 2
  end
  
# Sends a command to the controller and optionally read the result when a block
# is given. In this latter case, the controller is routinely read line by line
# until either a timeout or a prompt strengs is read. Each line is passed
# to the block and, if slurp is not nil, added to it and returned at the end.
# @param [String] cmd The string command to be written, arbitrary length.
# @param [Array, String, Numeric, Table] slurp The object to be used to store the command output.
# @return [Array, String, Numeric, Table] Returns the updated value of slurp.
# @yield [line] Each line of the stream is chomp-ed and passed to line.
  def command(cmd, slurp=nil)
    @port.write cmd
    if block_given? then
      begin
        while line = Timeout::timeout(1) {@port.gets.chomp}
          break if line =~ /#{@cfg[:prompt]}/
          case slurp
          when Array, Table, String
            slurp << yield(line)
          when Fixnum
            slurp = yield(line).to_i
          when Float
            slurp = yield(line).to_f
          else
            yield(line)
          end
        end
      rescue
        warn "Timeout"
      end
    end
    slurp
  end
  
# Closes the connection. Also sets @port to nil.
  def close
    @port.close
    @port = nil
  end

# Reboots the microcontroller by toggling the dtr line.  
  def reboot
    @port.dtr = 0
    @port.dtr = 1
  end
  
# Flushes the @port buffer.
  def flush
    @port.flush if @port.respond_to? :flush
  end
end

# A Table class that implements a by-column Array of Arrays.
# @author Paolo Bosetti
class Table
  attr_reader :col_names
  
# Creates a new instance with cols columns (of unlimited capacity).
# @param [Fixnum] cols The number of columns in the table.
  def initialize(cols=2)
    @cols = cols
    @content = Array.new(cols) {|n|
      if block_given? then
        yield n
      else
        []
      end
    }
    self.col_names = (0..@cols).to_a
  end
  
  def col_names=(ary)
    @col_names = {}
    @cols.times {|i| @col_names[ary[i].to_s] = i}
  end

# Appends an Array of @cols elements after the last row of the Table.
# @param [Array] ary An Array exactly of length @cols
# @raise [ArgumentError] if the argument is not an array or if its not of @cols length.
  def <<(ary)
    raise ArgumentError unless ary.respond_to? :size and ary.size == @cols
    @cols.times {|i| @content[i] << ary[i] }
  end

# Gives an Array description of the Table.
  def to_a
    @content
  end
  
# Clears the content.
  def clear
    @content.map! {|col| col = []}
  end

# Returns the i-th column of the table as an Array.
# @return [Array] Returns the i-th column
  def [](i)
    @content[i]
  end
  
  def each
    if block_given? then
      @content.each_with_index do |c,i|
        yield @col_names.keys[i], c
      end
    end
  end
  
  def inspect
    sep = " "
    desc = (@col_names.keys * sep) + "\n"
    @content[0].count.times do |r|
      @cols.times do |c|
        desc << @content[c][r].to_s
        desc << sep
      end
      desc << "\n"
    end
    return desc
  end
end

if ($0 == __FILE__) then
  ch = Charter::Client.new(1)
  ch.clear
  ard = Arduino.new :port => Dir.glob("/dev/tty.usb*")[0], :baud => 115200
  ard.connect
  ard.command('*') {|l| puts l}
  
  n = 10
  data = []
  yaml = ""
  start = Time.now.to_f
  ch.labels %w|Time(s) Value|
  100.times do |i|
    yaml = ""
    ard.command('a', yaml) {|l| l + "\n"}
    data = YAML.load(yaml)
    data.map! {|val| val / 1024.0 * 5.0}
    ch << [Time.now.to_f - start] + data
  end
  ard.close
end