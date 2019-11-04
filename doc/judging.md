## Judging

This is the explanation of `scripts/run_judge.sh`

For every `<problem>`, we can have multiple `<test>`s and multiple `<solution>`s

A test is composed of an input, `test/<problem>/<test>.in`, and an expected output, `test/<problem>/<test>.sol`

The solution is the file `src/<problem>/<solution>.cpp`

Typically, judging happens by passing the input as `stdin` to the solution, then checking that its `stdout` output matches the expected output

The output produced by the solution goes into `log/<problem>/<attempt>/<test>.out`
The stderr produced by the solution goes into `log/<problem>/<attempt>/<test>.log`
A description of what was correct and incorrect goes into `log/<problem>/<attempt>/<test>_judge.log`
Here `<attempt>` is typically `<solution>_debug`, however, for any tests where the `_debug` solution times out, judging also happens with `<attempt>` being `<solution>`

The file `judge/<problem>/<attempt>` contains the final judgement, and is the target you should `make`.
There's also the target `judge-all`, which judges all new and outdated attempts

Finally, if you want to check the output of `run_judge.sh` (what you see when running the make targets) on `log/<problem>/<attempt>_judge.log`

### Custom judge

The judge should be placed at `test/<problem>/judge.cpp`.
By default, it should be `template/judge/judge-default.cpp`

Judging happens by running `<judge>_debug` with parameters being the `.in` and the `.sol` files, with `stdin` being the `stdout` of the `<attempt>`, and with `stdin` being the `stdout` of the `<attempt>`
Note that the `.in` and `.sol` may be anything, since the actual input and judgement is entirely up to the custom judge

The actual input that the solution sees goes into `log/<problem>/<attempt>/<test>.in`
The judge's `stderr` goes into `log/<problem>/<attempt>/<test>_judge.log`

Return codes from the judge are specified under `template/judge-base.cpp`
