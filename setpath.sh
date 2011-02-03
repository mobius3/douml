#!/bin/bash

# Written by Robert Allen [rageek] 2011
# FREE for all uses, no support, no warranty!
#
# Script to set PATH to plugouts and tools for testing purposes.
#
# In order to build and test the application without actually
# installing it to /usr/bin/... and /usr/lib/..., you must
# add the locations of the various plugouts and tools to your
# PATH variable.
# This script will perform that function safely and temporarily.
#
# Test method:
# 1. Build the application by running make in the top of the source tree
#    !!! DO NOT run make install !!!
# 2. Source this script (*below) to add plugouts and tools to the PATH variable
# 3. Run the application by executing ./src/douml from the top of the source tree
# 
# Note that all PATH changes are relative to the top of the source tree - they will
# not have any effect if you run the application from another place!
#
# *Note the difference between executing the file, and 'sourcing' it.
# If you make the file executable and run it as ./setpath.sh,
# it will NOT set your PATH because the PATH cannot be exported from
# within a script!
# But 'sourcing' it by running it as 
# . setpath.sh OR
# source setpath.sh
# will add the changes to your open shell's environment.
# This will ONLY affect the shell in which you run it, and only for as
# long as that shell is open!
# If you close the shell and open another your PATH will again be the default
# for your login - you will have to run this script again.

PATH='./'$( find ./genplugouts/ ./src/ -type d -printf ":%p" )':'$PATH

