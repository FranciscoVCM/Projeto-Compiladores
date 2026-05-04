#!/usr/bin/env bash

if [[ -z "$1" ]]; then
    echo "Missing argument executable"
    echo "Usage: $0 executable"
    echo "Example: $0 ./path/to/jucompiler"
    exit 1
fi

exe="$1"

accepted=0
total=0

run_test() {
    inp="$1"
    flag="$2"

    total=$((total + 1))
    echo "$inp"

    out=${inp%.java}.out
    tmp=${inp%.java}.out_temp

    if [[ -z "$flag" ]]; then
        cmd=("$exe")
    else
        cmd=("$exe" "$flag")
    fi

    if "${cmd[@]}" < "$inp" > "$tmp"; then
        if ! diff -q "$out" "$tmp" > /dev/null; then
            echo " Wrong Answer, run 'diff $out $tmp' to see the differences"
        else
            accepted=$((accepted + 1))
        fi
    else
        echo " Runtime Error, failed to execute '$exe'"
    fi
}

if [[ -d meta1 ]]; then
    for inp in meta1/*.java; do
        [[ -e "$inp" ]] || continue

        flag="-l"
        if [[ "$inp" == *_e1.java ]]; then
            flag="-e1"
        fi

        run_test "$inp" "$flag"
    done
fi

if [[ -d meta2 ]]; then
    for inp in meta2/*.java; do
        [[ -e "$inp" ]] || continue

        flag="-t"
        if [[ "$inp" == *_e2.java ]]; then
            flag="-e2"
        fi

        run_test "$inp" "$flag"
    done
fi

if [[ -d meta3 ]]; then
    for inp in meta3/*.java; do
        [[ -e "$inp" ]] || continue

        flag="-s"
        if [[ "$inp" == *NoFlags.java ]]; then
            flag=""
        elif [[ "$inp" == *_e3.java ]]; then
            flag="-e3"
        fi

        run_test "$inp" "$flag"
    done
fi

if [[ -d meta4 ]]; then
    for inp in meta4/*.java; do
        [[ -e "$inp" ]] || continue

        flag="-s"
        if [[ "$inp" == *NoFlags.java ]]; then
            flag=""
        elif [[ "$inp" == *_e4.java ]]; then
            flag="-e4"
        fi

        run_test "$inp" "$flag"
    done
fi

echo "Accepted: $accepted / $total"