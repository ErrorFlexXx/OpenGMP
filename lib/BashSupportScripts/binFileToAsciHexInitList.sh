#!/bin/bash

cat public_key.bin | hexdump -v -e '"0x" 1/1 "%02X" ", "' | rev | cut -c 3- | rev ; echo
