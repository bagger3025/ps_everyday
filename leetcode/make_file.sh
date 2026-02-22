#!/bin/bash

git pull

# Prompt for submission URL
read -p "Enter LeetCode submission URL: " SUBMISSION_URL

# Prompt for problem number
read -p "Enter problem number: " PROBLEM_NUMBER

# Prompt for date
CUR_DATE=$(date '+%y%m%d')
read -p "Enter current date(Default=$CUR_DATE): " DATE
: ${DATE:=$CUR_DATE}
FOLDER=${DATE:0:4}

# Extract problem slug from URL
PROBLEM_SLUG=$(echo "$SUBMISSION_URL" | sed -E 's#.*/problems/([^/]+)/.*#\1#')

#Prompt for extension
read -p "Enter the language you solved with(Default=cpp): " EXT
: ${EXT:=cpp}

# Build filename and destination directory
FILENAME="${DATE}-${PROBLEM_NUMBER}-${PROBLEM_SLUG}.${EXT}"
DEST_DIR="./$FOLDER"
mkdir -p "$DEST_DIR"

# Prompt for code
echo "Paste your C++ code below. Press Ctrl+D when you're done:"
cat > "$DEST_DIR/$FILENAME"

# Git add & commit
git add "$DEST_DIR/$FILENAME"
git commit -m "$DATE leetcode"

echo "✅ Saved to $DEST_DIR/$FILENAME"
echo "Following is git log and File content:"

git log -1

echo "======= File start ======="
cat $DEST_DIR/$FILENAME
echo "======= File end ======="
