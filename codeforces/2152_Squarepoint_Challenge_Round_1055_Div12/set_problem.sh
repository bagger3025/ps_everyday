#!/bin/bash

if [[ "$#" -ne 1 ]]; then
  echo "Give argument";
  exit 1;
fi

echo "Delete {src.cpp,tc}"
rm -f src.cpp tc

if [ ! -f "$1.cpp" ]; then
  echo "File $1.cpp not exist, which file to copy (without .cpp)?"
  read FILE_NAME

  if [ ! -f "$FILE_NAME.cpp" ]; then
    echo "File $FILE_NAME.cpp not exist! Check the file name again";
    exit 1;
  fi
  
  echo "Copy: $FILE_NAME.cpp => $1.cpp"
  cp "$FILE_NAME.cpp" "$1.cpp"
fi

echo "Soft Link: $1.cpp => src.cpp"
ln -s "$1.cpp" src.cpp

echo "Soft Link: testcase/$1 => tc"
ln -s "testcase/$1" tc

echo "Changed Makefile"
sed -i '' 's/^PROBLEM.*$/PROBLEM='$1'/g' Makefile

echo "Check the following:"
ls -al src.cpp tc
cat Makefile | head -1
