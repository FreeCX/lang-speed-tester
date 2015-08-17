# lang-speed-tester
### How to use

Compile available languages
```
$ make gcc g++ clang rust ...
```
Or `all` for compile with `gcc`, `clang`, `rust`, `dmd`, `ldc`, `gdc`, `nim` compilators
```
$ make all
```
Strip debug information
```
$ make strip
```
Run *info* tool and *tests* with `<number-of-iterations>` (ex: 1000)
```
$ ./system-info
$ ./tester 1000
```
And wait results!
