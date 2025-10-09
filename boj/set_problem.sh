#!/bin/bash

if [[ "$#" -ne 1 ]]; then
  echo "Give argument";
  exit 1;
fi

EXEC_FILES=`ls e_* w_* 2>/dev/null`
EXEC_FILES_STR=`echo ",${EXEC_FILES}" | tr '\n' ',' | sed 's/,*$//'`
EXEC_FILES_ARGS=`echo "${EXEC_FILES}" | tr '\n' ' '`

echo "Delete {src.cpp,tc${EXEC_FILES_STR}}"
rm -f src.cpp tc ${EXEC_FILES_ARGS}

SRC_FILE_NAME="files/$1.cpp"

if [ ! -f "$SRC_FILE_NAME" ]; then
  echo -n "files last modified file: "
  ls -tld files/* | head -1
  echo "File $SRC_FILE_NAME not exist, which file to copy (without .cpp)?"
  read FILE_NAME

  FROM_FILE_NAME="files/$FILE_NAME.cpp"

  if [ ! -f "$FROM_FILE_NAME" ]; then
    echo "File $FROM_FILE_NAME not exist! Check the file name again";
    exit 1;
  fi
  
  echo "Copy: $FROM_FILE_NAME => $SRC_FILE_NAME"
  cp "$FROM_FILE_NAME" "$SRC_FILE_NAME"
fi

echo "Soft Link: $SRC_FILE_NAME => src.cpp"
ln -s "$SRC_FILE_NAME" src.cpp

if [ ! -d "testcase/$1" ]; then
  echo "Create: testcase/$1";
  mkdir -p "testcase/$1"
fi

echo "Soft Link: testcase/$1 => tc"
ln -s "testcase/$1" tc

echo "Changed Makefile"
sed -i '' 's/^PROBLEM.*$/PROBLEM='$1'/g' Makefile

echo;
echo "Check the following:"
ls -al src.cpp tc
cat Makefile | head -1
