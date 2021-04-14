#!/bin/bash

# check if there is an arg with filename
if [ -z "$1" ] 
then
  echo filename not in args
  exit 1
fi


FILENAME_STRING="$(grep -i "output:" "$1")"
FILENAME_WITH_WHITESPACE=${FILENAME_STRING#//Output:}
FILENAME=$(echo "$FILENAME_WITH_WHITESPACE" | tr -d [:space:])

# check if var FILENAME is not empty and contains name
if [ -z "$FILENAME" ] 
then
  echo File name is not valid
  exit 1
fi

TEMP_FOLDER=$(mktemp -d)

# check if program was killed to remove temp dir
trap "rm -rf TEMP_FOLDER; exit 1" SIGINT SIGHUP SIGTERM 

cp "$1" "$TEMP_FOLDER"/

PRIMARY_DIR=$(pwd)

cd $TEMP_FOLDER
gcc "$1" -o "$FILENAME"

# check if compilation succeded 
if [ $? -ne 0 ] 
then
  echo Compilation failed
  cd "$PRIMARY_DIR"
  rm -rf "$TEMP_FOLDER"
  exit 1
fi

echo Compilated: $FILENAME
#delete temp dir
mv "$FILENAME" "$PRIMARY_DIR"
cd "$PRIMARY_DIR"
rm -rf "$TEMP_FOLDER"