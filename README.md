To build you need to set the three environment variables `DYNINST`, `BOOST`, and
`TBB` to the install directories of these three dependencies.


For example, if you `spack` installed `dyninst` you could do:


```
export DYNINST=`spack location --install-dir dyninst`
export BOOST=`spack location --install-dir boost`
export TBB=`spack location --install-dir tbb`
```

Then to build and test:

```
make test
```

The fact that one never sees:
```
NoopSnippet.generate: inserting a no op
```
in the output is the issue at hand.

There is also a hybrid approach described in `hybrid_main.cpp` and the corresponding `make target`

```
make hybrid_test
```
which does seem to work. Still no clue why the original doesn't work. Or whether, if it worked, it would
patch the binary in the same way.
