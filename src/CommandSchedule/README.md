# CommandSchedule

A 'Command' is a string message that should be sent to the flight computer at a certain time.

The CommandSchedule subsystem provides functions for registering a list of commands (from a JSON config)
and utilities for 

The actual sending of commands over serial occurs in `main.cpp`.