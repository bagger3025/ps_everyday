#!/bin/bash

git pull

# Prompt for submission URL
read -p "Enter LeetCode submission URL: " SUBMISSION_URL

# Prompt for problem number
read -p "Enter problem number: " PROBLEM_NUMBER

# Get current date in YYMMDD format
FOLDER=problem

# Extract problem slug from URL
PROBLEM_SLUG=$(echo "$SUBMISSION_URL" | sed -E 's#.*/problems/([^/]+)/.*#\1#')

# Build filename and destination directory
FILENAME="${PROBLEM_NUMBER}-${PROBLEM_SLUG}.cpp"
DEST_DIR="./$FOLDER"
mkdir -p "$DEST_DIR"

# Prompt for code
echo "Paste your C++ code below. Press Ctrl+D when you're done:"
cat > "$DEST_DIR/$FILENAME"

# Git add & commit
git add "$DEST_DIR/$FILENAME"
git commit -m "leetcode #${PROBLEM_NUMBER}"

echo "✅ Saved to $DEST_DIR/$FILENAME"
echo "Following is git log and File content:"

git log -1

echo "======= File start ======="
cat $DEST_DIR/$FILENAME
echo "======= File end ======="
