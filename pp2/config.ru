#!/usr/bin/env ruby
require File.expand_path('../environment', __FILE__)
require 'main'

run Rack::Cascade.new([Rack::File.new('public'), Main])
