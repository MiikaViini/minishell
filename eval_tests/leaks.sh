#!/bin/sh
#a script which periodically checks for leaks using the leaks command line

while true
do
	leaks minishell;
		sleep 1;
	# echo
done

#copied from Alex Mann
