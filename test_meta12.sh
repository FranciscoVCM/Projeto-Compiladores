#!/usr/bin/env bash

if [[ -z "$1" ]]; then
    echo "Missing argument executable"
    echo "Usage: $0 executable"
    echo "Example: $0 ./claudecompiler"
    exit 1
fi

exe="$1"

accepted=0
total=0

if [[ -d meta1 ]]; then
    for inp in meta1/*.java; do
        total=$(( total + 1 ))
        echo "$inp"
        out=${inp%.java}.out
        tmp=${inp%.java}.out_temp
        flag="-l"
        if [[ "$inp" == *_e1.java ]]; then
            flag="-e1"
        fi
        if $exe $flag < "$inp" > "$tmp"; then
            lines=$(diff "$out" "$tmp" | wc -l)
            if [[ $lines -gt 0 ]]; then
                echo " Wrong Answer, run 'diff $out $tmp' to see the differences"
            else
                accepted=$(( accepted + 1 ))
            fi
        else
            echo " Runtime Error, failed to execute '$exe'"
        fi
    done
fi

if [[ -d meta2 ]]; then
    for inp in meta2/*.java; do
        total=$(( total + 1 ))
        echo "$inp"
        out=${inp%.java}.out
        tmp=${inp%.java}.out_temp
        flag="-t"
        if [[ "$inp" == *_e2.java ]]; then
            flag="-e2"
        fi
        if $exe $flag < "$inp" > "$tmp"; then
            lines=$(diff "$out" "$tmp" | wc -l)
            if [[ $lines -gt 0 ]]; then
                echo " Wrong Answer, run 'diff $out $tmp' to see the differences"
            else
                accepted=$(( accepted + 1 ))
            fi
        else
            echo " Runtime Error, failed to execute '$exe'"
        fi
    done
fi

echo "Accepted: $accepted / $total"