#!/bin/bash

case $1 in
	1)
		./RMM.sh $2 $3
		;;
	2)
		./SMM_Order.sh $2 $3
		;;
	3)
		./SMM_Time.sh $2 $3
		;;
	*)
		echo "Invalid option entered for merge type. Try again."
		;;
esac
