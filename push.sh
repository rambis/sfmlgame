#!/bin/bash

git status

read -p "Add all files? y/n" -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
	git add .
	read -p "Commit Message: " commitmsg
	echo
	git commit -m "$commitmsg"
	echo "Committed! Pushing now"
	echo
	git push http://github.com/rambis/sfmlgame
	echo "rambis"
	echo "Alf0ns0g0mez!"
else
	exit 0

fi	

