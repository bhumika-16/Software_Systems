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

