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
        if [[ "$inp" == *_e3.java ]]; then
            flag="-e3"
        fi

        run_test "$inp" "$flag"
    done
fi

meta4_args() {
    case "$(basename "$1")" in
        fluxControl1.java)
            echo "15"
            ;;
        fluxControl2.java)
            echo "30"
            ;;
        fluxControl3.java)
            echo "30"
            ;;
        length.java)
            echo "1 3"
            ;;
        MultipleParametersCommandLine.java)
            echo "1 2"
            ;;
        Factorial.java)
            echo "5"
            ;;
        complex.java)
            echo "0"
            ;;
        randomTest.java)
            echo "7"
            ;;
        strings_tests.java)
            echo "1 2 3 4 5"
            ;;
        *)
            echo ""
            ;;
    esac
}

run_meta4_test() {
    inp="$1"

    total=$((total + 1))
    echo "$inp"

    out=${inp%.java}.out
    tmp=${inp%.java}.out_temp
    ll=${inp%.java}.ll

    args_string="$(meta4_args "$inp")"

    if "$exe" < "$inp" > "$ll"; then
        if [[ -n "$args_string" ]]; then
            # shellcheck disable=SC2086
            if ! lli "$ll" $args_string > "$tmp"; then
                echo " Runtime Error, failed to execute LLVM '$ll'"
                return
            fi
        else
            if ! lli "$ll" > "$tmp"; then
                echo " Runtime Error, failed to execute LLVM '$ll'"
                return
            fi
        fi

        if ! diff -q "$out" "$tmp" > /dev/null; then
            echo " Wrong Answer, run 'diff $out $tmp' to see the differences"
        else
            accepted=$((accepted + 1))
        fi
    else
        echo " Runtime Error, failed to generate LLVM for '$inp'"
    fi
}

if [[ -d meta4 ]]; then
    for inp in meta4/*.java; do
        [[ -e "$inp" ]] || continue
        run_meta4_test "$inp"
    done
fi

echo "Accepted: $accepted / $total"