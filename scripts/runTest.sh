#!/bin/bash

name=$1
testdir=$(dirname $name)

checkStatus() {
  eval $1
  ret=$?
  if [ $ret != 0 ]; then
    echo Fail with code $ret\: $1
    rm log/$name\_success 2> /dev/null
    exit 1
  fi
}

mkdir -p log/$testdir
fifodir=$(mktemp -d)
input=$fifodir/t.in
output=$fifodir/t.out
mkfifo $input
mkfifo $output
checkStatus "bin/$testdir/solver_debug < $input 2> log/$name.log | tee $output > log/$name.out" &
checkStatus "bin/$testdir/checker_debug $name.in < $output 2> log/$name""_checker.log | tee $input > log/$name.in"
wait $!
if [ $? != 0 ]; then
  exit 1
fi
echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: Success" > log/$name\_success

