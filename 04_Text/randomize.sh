#!/bin/bash
line_number=0
buf=()
t=${1:-0.01}
clear
while IFS= read -r line
do
    len=${#line}
    for (( offset=0 ; offset<$len ; offset++))
    do
        buf+=("$offset|$line_number|${line:offset:1}")
    done
    line_number=$((line_number+1))
done
buf=($(shuf -e "${buf[@]}"))
for line in ${buf[@]}
do
    readarray -d "|" -t huy <<< $line
    tput cup ${huy[1]} ${huy[0]}
    if [[ ${#huy[@]} -eq 4 ]]; then
        echo -n "|"
    else
        echo -n ${huy[2]}
    fi
    sleep $t
done
tput cup $line_number 0
echo