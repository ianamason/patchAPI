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