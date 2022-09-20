#!/bin/bash

data_path="../data"
app="../../app.exe"
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

ERR=255

pos_in_raw=$(find $data_path -name "pos_[0-9][0-9]_in.txt" | sort | tr '\n' ' ')
pos_out_raw=$(find $data_path -name "pos_[0-9][0-9]_out.txt" | sort | tr '\n' ' ')
neg_in_raw=$(find $data_path -name "neg_[0-9][0-9]_in.txt" | sort | tr '\n' ' ')

IFS=' ' read -r -a pos_in <<< "$pos_in_raw"
IFS=' ' read -r -a pos_out <<< "$pos_out_raw"
IFS=' ' read -r -a neg_in <<< "$neg_in_raw"

pos_in_c=${#pos_in[@]}
pos_out_c=${#pos_out[@]}
neg_in_c=${#neg_in[@]}
pos_failed=0
neg_failed=0

if [ "$pos_in_c" -ne "$pos_out_c" ]; then
    echo "pos_in and pos_out files count is not equal! Aborting tests..."
    exit $ERR
fi

if [ ! -f "$app" ]; then
    echo "Cannot find app.exe, please compile the program!"
    exit $ERR
fi

if [ -n "$USE_VALGRIND" ]; then
    echo "Running Valgrind!"
fi


echo "Starting positive tests:"

for i in "${!pos_in[@]}"; do
    echo $"Test ${pos_in[$i]}"
    eval ./pos_case.sh "${pos_in[$i]}" "${pos_out[$i]}"
    res=$?
    if [ $res -eq 0 ]; then
        echo -e "TEST: ${GREEN}PASSED${NC}"
    else
        echo -e "TEST: ${RED}FAILED${NC}"
        pos_failed=$((pos_failed+1))
    fi
    if [ -n "$USE_VALGRIND" ]; then
        memory=$(grep -Eo "ERROR SUMMARY: [0-9]+" < v.temp | cut -d ' ' -f 3)
        if [ "$memory" -eq 0 ]; then
            echo -e "MEMORY: ${GREEN}PASSED${NC}"
        else
            echo -e "MEMORY: ${RED}FAILED${NC}"
        fi
    fi
done

echo "Positive tests passed: $((pos_in_c - pos_failed))/$pos_in_c"

echo "Starting negative tests:"

for i in "${!neg_in[@]}"; do
    echo $"Test ${neg_in[$i]}"
    eval ./neg_case.sh "${neg_in[$i]}"
    res=$?
    if [ $res -eq 1 ]; then
        echo -e "TEST: ${GREEN}PASSED${NC}"
    else
        echo -e "TEST: ${RED}FAILED${NC}"
        neg_failed=$((neg_failed+1))
    fi

    if [ -n "$USE_VALGRIND" ]; then
        memory=$(grep -Eo "ERROR SUMMARY: [0-9]+" < v.temp | cut -d ' ' -f 3)
        if [ "$memory" -eq 0 ]; then
            echo -e "MEMORY: ${GREEN}PASSED${NC}"
        else
            echo -e "MEMORY: ${RED}FAILED${NC}"
        fi
    fi
done

echo "Negative tests passed: $((neg_in_c - neg_failed))/$neg_in_c"

total=$((pos_in_c + neg_in_c))
total_failed=$((pos_failed + neg_failed))

echo "Total tests passed: $((total - total_failed))/$total"

exit $total_failed
