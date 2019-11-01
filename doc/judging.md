## Judging

For every `<problem>`, we can have multiple `<test>`s and multiple `<solution>`s

A test is composed of an input, `test/<problem>/<test>.in`, and an expected output, `test/<problem>/<test>.sol`

The solution is the file `src/<problem>/<solution>.cpp`

Typically, judging happens by passing the input as `stdin` to the solution, then `diff`'ing its `stdout` output to the expected output

The output produced by the solution goes into `log/<problem>/<attempt>/<test>.out` The `diff` goes into `log/<problem>/<attempt>/<test>_judge.log`
The stderr produced by the solution goes into `log/<problem>/<attempt>/<test>.log`
Here `<attempt>` is typically `<solution>_debug`, however, for any tests where the `_debug` solution times out, judging also happens with `<attempt>` being `<solution>`

The file `log/<problem>/<attempt>/success` is produced when the judging passes

### Custom judge

If the default judge, `scripts/default_judge.sh`, is not appropriate, you can create a custom judge at `test/<problem>/judge.cpp`

In that case, judging happens by running `<judge>_debug` with parameters being the `.in` and the `.sol` files, with `stdin` being the `stdout` of the `<attempt>`, and with `stdin` being the `stdout` of the `<attempt>`
Note that the `.in` and `.sol` may be anything, since the actual input and judgement is entirely up to the custom judge

The actual input that the solution sees goes into `log/<problem>/<attempt>/<test>.in`
The judge's `stderr` goes into `log/<problem>/<attempt>/<test>_judge.log`

Return codes from the judge are specified under `template/base-judge.cpp` and `scripts/?`
