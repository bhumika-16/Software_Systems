: '
==================================================================================================
Name : 5.sh
Author : Bhumika Jindal
Description : Write a program to create five new files with infinite loop. Execute the program 
			in the background and check the file descriptor table at /proc/pid/fd.
Date: 11th Aug, 2023.
==================================================================================================
'

#!/bin/bash

i=1

while true; do
  filename="file_$i.txt"
  touch "$filename"
  echo "Created file: $filename"
  i=$((i + 1))
  if [ $i -eq 6 ];
  then
  	i=1
  fi
  sleep 1
done

