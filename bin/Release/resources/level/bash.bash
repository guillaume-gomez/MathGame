#!/bin/bash

ls "$1"* | \
while read file;
do
	mv $file $(echo $file | sed "s/.*_\(.*\)/$2_\1/")
done

