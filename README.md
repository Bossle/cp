# bossle/cp

## C++ code meant for competitive programming

### What you can find here

`template/` contains my personal library of code for CP
`doc/` contains tutorials on CP
`src/` contains solutions to problems
`test/` contains data for judging problems
And a bunch more stuff

Further information is in `doc/`, check it out


#### Compilation

`bin/` contains the compiled binaries. Currently a file `src/stuff.cpp` generates `bin/src/stuff` and `bin/src/stuff_debug`.

`build/` contains temporary files for compilation. Currently a file `src/stuff.cpp` generates `build/src/stuff.d`, which is used by Makefile to know that `stuff` must be rebuilt when one of the headers it uses changes.

##### Makefile

`Makefile` contains the 
