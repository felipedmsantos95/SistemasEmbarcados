#!/usr/bin/env python
# -*- coding: latin1 -*-
# -------------------------------------------------
# Usage: ./getstates.py fsmfile.txt
# -------------------------------------------------

from __future__ import print_function
import os
import sys
import re



if __name__ == "__main__":  
	
	if len(sys.argv) <= 1 or len(sys.argv) > 2:
		print("Usage: ./getstates.py fsmfile.txt")
	else:
		# Open fsm file 
		fsmfile = open(sys.argv[1])
		lines = fsmfile.readlines()
		fsmfile.close()
		
		# Read file
		for line in lines:
			# Apply REGEX 
			matchstates = re.match(r'states\s*=\s*[{](.*)[}]', line.strip(), re.IGNORECASE)
			if matchstates:
				listst = matchstates.group(1).replace(" ", "")				
				getstates = listst.split(",")
				print("States: ")
				for st in getstates:
					print(st)
