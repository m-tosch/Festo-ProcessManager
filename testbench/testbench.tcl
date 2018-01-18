#!/usr/bin/expect

# This script automates a test procedure for sending commands to a TCP/IP gateway
# and validating the responses. It starts a TCP/IP client program and passes the
# address of the gateway as first argument. After connection is established,
# commands are passed to the client program via command line. Responses of the
# gateway are verfied by comparison with expected outputs.
#
# Expect Scripting Language is used. Expect can be installed using apt.
#
# Marc Hamme, 2018


# ------ Setup Test Parameters ------

# Adjust the following settings for your test procedure.

# Set name of executable
set exec_name ProcessManager

# Set IP address of gateway
set gateway_address 127.0.0.1

# Set commands and expected outputs (two lines: command followed by output)
set commands {
	"setup0"
	"setup[1-4]"
	"DV"
	"V=\d*\.\d*"
	"DS"
	"S=\d*"
}

# Enable evaluation of expected output as regular expression
set enable_regex 1

# Enable wait for first program message (can be any message)
set enable_firstmsg 1

# Set timeout for answers in seconds
set timeout 5


# ------ End of Setup ------


# --- Procedures ---

proc putfailuremessage {} {
	puts "\n--------------------------------------------"
	puts "Timeout or unexpected response. Test failed."
	puts "--------------------------------------------\n"
}


# --- Start Test ---

spawn "./$exec_name" $gateway_address

if {$enable_firstmsg} {expect -re "\[a-zA-Z0-9\]"}

puts "\n-------------------------"
puts "Starting command sequence"
puts "-------------------------\n"

foreach {cmd res} $commands {
	send "${cmd}\n"
	if {$enable_regex} {
		expect {
			-re $res continue
			timeout {
				putfailuremessage
				exit
			}
		}
	} else {
		expect {
			$res continue
			timeout {
				putfailuremessage
				exit
			}
		}
	}
}

puts "\n------------"
puts "Test passed."
puts "------------\n"
