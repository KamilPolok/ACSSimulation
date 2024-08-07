#!/bin/bash

# Swap delimiters from comas to semicolons
# and decimal separators from dots to comas
swap_delimiters()
{
    sed -i -e 's/,/;/g' -e 's/\./,/g' $inputfile
} 

# Check if exactly one argument was provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

inputfile=$1

# Check if provided argument is a file
if [ ! -f "$inputfile" ]; then
    echo "File: $inputfile not found!"
    exit 1
fi

# Check if the file delimiters have already been swapped.
if ! grep -q ';' "$inputfile"; then
    swap_delimiters
fi 
