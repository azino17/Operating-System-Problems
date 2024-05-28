#!/bin/bash
find_substring() {
string="$1"
substring="$2"
length=${#substring}


for (( i=0; i<${#string}; i++ ))
do
if [[ ${string:$i:$length} == "$substring" ]]
then
echo "Substring found at position $i"
fi
done
}


echo "Enter the string: "
read string
echo "Enter the substring to search for: "
read substring


find_substring "$string" "$substring"

