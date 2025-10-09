#!/bin/bash

if [ ! -f "src.cpp" ]; then
  echo "File src.cpp not exist, set the file first!"
  exit 1;
fi

SRC_FILE_NAME=`readlink src.cpp`

if [[ $SRC_FILE_NAME =~ files/([0-9]+).cpp ]]; then
  PROBLEM_NUM="${BASH_REMATCH[1]}"
else
  echo "SRC_FILE_NAME format is not file/[0-9]+.cpp, Check the symlink";
  exit 1;
fi

echo "Remove ref.cpp"
rm -f ref.cpp

REF_FILE_NAME="files/$PROBLEM_NUM""_ref.cpp"

if [ ! -f "$REF_FILE_NAME" ]; then
  echo "Copy: $SRC_FILE_NAME => $REF_FILE_NAME"
  cp "$SRC_FILE_NAME" "$REF_FILE_NAME"
fi

echo "Soft Link: $REF_FILE_NAME => ref.cpp"
ln -s "$REF_FILE_NAME" ref.cpp

echo "Check the following:"
ls -al ref.cpp
