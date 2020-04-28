#!/bin/bash

if [[ $# != 1 ]]; then
  echo "Usage: $0 problem-name"
  exit 1
fi

mkdir "src/$1"
cp src/example/ac.cpp "src/$1/main.cpp"
gedit "src/$1/main.cpp"

mkdir "test/$1"
cp template/judge/judge-default.cpp "test/$1/judge.cpp"
temp=$(mktemp)
for (( i=1; ; i++ )); do
  echo "Input $i:"
  cat > $temp
  cp $temp "test/$1/t$i.in"
  echo "Solution $i:"
  cat > $temp
  cp $temp "test/$1/t$i.sol"
done
