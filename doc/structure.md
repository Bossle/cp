`bin`: Contains compiled binaries. `<folder>/<file>.cpp` gets compiled into `bin/<folder>/<file>_debug` and `bin/<folder>/<file>`

`build`: Contains intermediate files used in compilation.
- `<folder>/<file>.cpp` creates a `build/<folder>/<file>.d` makefile for its particular dependencies
- `<folder>/<file>.cpp` creates a `build/<folder>/<file>.cpp` which is the result of preprocessing it

`dist/`: Contains single-file solutions to problems, ready to be submitted to external judges. `<folder>/<file>.cpp` becomes `dist/<folder>/<file>.cpp`

`doc`: Contains purely human-readable documentation
- files describing the project as a whole go on the root
- problem descriptions and tutorials go inside `doc/problems/<problem>/`
- tutorials on CP concepts and library files go in `doc/cp-tutorial`
- a printable, compiled notebook goes in `doc/notebook`
- online judge specifics go into their respective folders

`judge`: Contains the status of attempts on problems. Files are `judge/<problem>/<attempt>`, and contain only plain judgements, such as `Accepted`

`log`: Contains miscellaneous outputs, described in [Judging](judging.md)

`scripts`: Contains miscellaneous scripts
- makefile `.mk` files
- `run_judge.sh` does the entire judging logic for one attempt
- online judge specific scripts go in their respective folders

`src`: Contains cpp solutions to problems. The subfolder name represents the problem

`template`: Contains a code library for CP relevant algorithms and data structures

`test`: Contains data and code for judging solutions, described in [Judging](judging.md)
