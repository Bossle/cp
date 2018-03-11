#!/bin/bash

name=$1
testdir=$(dirname $name)

checkStatus() {
  eval $1
  ret=$?
  if [ $ret != 0 ]; then
    echo Fail with code $ret\: $1
    exit 1
  fi
}

mkdir -p log/$testdir
checkStatus "bin/$testdir/solver_debug < $name.in > log/$name.out 2> log/$name.log"
if [ ! -f $name.sol ]; then
  touch $name.sol
fi
checkStatus "bin/$testdir/checker_debug $name.in $name.sol < log/$name.out > log/$name""_checker.out 2> log/$name""_checker.log"
echo "[$(date +'%Y-%m-%dT%H:%M:%S%z')]: Success" > log/$name\_success

