#!/bin/bash

if [[ $# != 3 ]]; then
  echo "Usage: $0 problem solution status-file"
  echo "Where bin/problem/solution[_debug] is the solution to test"
  echo "And status-file is where the final judgement should be stored"
  exit 2
fi

mkdir -p "log/$1"
touch "log/$1/$2_judge.log"
exec > >(tee "log/$1/$2_judge.log") 2>&1

# Returns:
# 0) Accepted
# 1) Wrong Answer
# 2) Runtime Error
# 3) Time Limit Exceeded
# 4) Presentation Error
# 5) Protocol Violation
# 6) Protocol Limit Exceeded
# 127) Judge Error
# TODO: MLE / Restricted Function / Output Limit Exceeded / Idleness Limit Exceeded
#   https://github.com/contester/runlib should help
#   or docker or cgroups+iptables?
judge() {
  exec > >(tee >(cat >&2))
  problem="$1"
  attempt="$2"
  test_case="$3"
  echo >&2
  echo -n "Testing $problem/$attempt against $test_case:" >&2
  mkdir -p "log/$problem/$attempt"
  touch "log/$problem/$attempt/$test_case.in"
  touch "log/$problem/$attempt/$test_case.out"
  coproc timeout -s KILL ${CP_TIMEOUT:-1} "bin/src/$problem/$attempt" \
    < <(tee "log/$problem/$attempt/$test_case.in") \
    > >(tee "log/$problem/$attempt/$test_case.out") \
    2> "log/$problem/$attempt/$test_case.log"
  coproc_pid=$COPROC_PID
  time "bin/test/$problem/judge_debug" "test/$problem/$test_case.in" "test/$problem/$test_case.sol" \
    <&${COPROC[0]} >&${COPROC[1]} \
    2> "log/$problem/$attempt/${test_case}_judge.log"
  judge_ret=$?
  wait $coproc_pid
  case $? in
    0) ;;
    137) echo "Time Limit Exceeded"; return 3;;  # TODO: make "exit 137" also RTE
    *) echo "Runtime Error ($?)"; return 2;;
  esac
  case $judge_ret in
    0) echo "Accepted";;
    1) echo "Wrong Answer"; return 1;;
    2) echo "Presentation Error"; return 4;;
    3) echo "Protocol Violation"; return 5;;
    4) echo "Protocol Limit Exceeded"; return 6;;
    *) echo "Judge Error ($judge_ret)"; return 127;;
  esac
}

failed=0
total=0
first_failure=""
final_judgement="Accepted"
for test_case in $(basename -s .in $(find "test/$1/" -name *.in ) ); do
  total=$((total + 1))
  judgement=$(judge "$1" "$2_debug" "$test_case")
  judge_ret=$?
  if [[ $judge_ret == 3 ]]; then  # TLE, try with release version
    judgement=$(judge "$1" "$2" "$test_case")
    judge_ret=$?
  fi
  case $judge_ret in
    0) ;;
    127) exit 2;;
    *) failed=$((failed + 1))
      if [[ $failed = 1 ]]; then
        first_failure=$test_case
        final_judgement=$judgement
      fi;;
  esac
done

echo
echo "Finished judging $1/$2:"
if [[ $total = 0 ]]; then
  echo "No test cases"
  final_judgement="Can't Judge"
elif [[ $failed = 0 ]]; then
  echo "All $total tests passed"
else
  echo "Failed $failed out of $total cases"
  echo "First failed: $first_failure"
fi

echo $final_judgement
echo $final_judgement > "$3"
