#!/bin/bash

cat $1
diff ${1%.*}.sol -
exit $?

