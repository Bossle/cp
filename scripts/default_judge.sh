#!/bin/bash

cat $1
diff $2 -
exit $?

