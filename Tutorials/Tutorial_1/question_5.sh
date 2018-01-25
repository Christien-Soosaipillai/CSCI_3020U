#!/bin/bash
ARG1="$1"
if [ $ARG1 == 'loop' ]
then
	echo "loop"
	for i in {1..5}
		do
			echo i >> count.log
	done
fi

ps >> processes.log
