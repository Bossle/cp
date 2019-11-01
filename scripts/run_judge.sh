#!/bin/bash

# judge_ret = AC / WA / PE / Protocol Violation / Protocol Limit Exceeded
# TODO: TLE
# TODO: MLE / Restricted Function / Output Limit Exceeded / Idleness Limit Exceeded
#   https://github.com/contester/runlib should help

if [[ $# != 2 ]]; then
  echo "Usage: $0 problem solution"
fi

problem="$1"
for attempt in "$2_debug" "$2"; do
  for test_case in $(basename $(find "test/$problem/" -name *.in ) .in ); do
    echo "Testing $problem/$attempt against $test_case:"
    mkdir -p "log/$problem/$attempt"
    touch "log/$problem/$attempt/$test_case.in"
    touch "log/$problem/$attempt/$test_case.out"
    coproc "bin/src/$problem/$attempt" \
      < <(tee "log/$problem/$attempt/$test_case.in") \
      > >(tee "log/$problem/$attempt/$test_case.out") \
      2> "log/$problem/$attempt/$test_case.log"
    "bin/test/$problem/judge_debug" "test/$problem/$test_case.in" "test/$problem/$test_case.sol" <&${COPROC[0]} >&${COPROC[1]} 2> "log/$problem/$attempt/${test_case}_judge.log"
    judge_ret=$?
    wait $COPROC_PID || { echo "Runtime Error"; exit 1; }
    case $judge_ret in
      0) echo "Accepted";;
      1) echo "Wrong Answer"; exit 1;;
      2) echo "Presentation Error"; exit 1;;
      3) echo "Protocol Violation"; exit 1;;
      4) echo "Protocol Limit Exceeded"; exit 1;;
      *) echo "Judge Error"; exit 1;;
    esac;
  done
done

mkdir -p "log/$problem/$2"
echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: Success" > "log/$problem/$2/success"

