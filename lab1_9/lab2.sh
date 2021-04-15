#!/bin/bash

# Counting the no of lines in a file list

#---------------------------------------------------------------
#function definitions
#---------------------------------------------------------------
#fun def: iist of all files 
get_files () {
  files="`ls *.sh`"
}

# func def: counting the number of lines in a file
count_lines () {
  local f=$1  # 1st argument is filename
  l=`wc -l $f | sed 's/^\([0-9]*\).*$/\1/'` #number of lines
}


#---------------------------------------------------------------
# The script is called without any argument
if [ $# -ge 1 ]
then
  echo "Usage: $0 "
  exit 1
fi

#---------------------------------------------------------------
#by newline
IFS=$'\012'

#---------------------------------------------------------------
echo "$0 counts the lines of code" 
#initialization
l=0
ctr=0
sum=0
#---------------------------------------------------------------
#function call for getting file list
get_files
#for each line f in files count the no of files
for f in $files
do
        #function call to count the lines
        count_lines $f
        echo "$f: $l" 
	# inc ctr
        ctr=$[ $ctr + 1 ]
	# inc sum 
        sum=$[ $sum + $l ]
done

echo "$ctr - files with $sum - lines"
