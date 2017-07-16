# bcrypt

##### *Blowfish Password Hashing Algorithm*

[![Build Status](https://travis-ci.org/jeroen/bcrypt.svg?branch=master)](https://travis-ci.org/jeroen/bcrypt)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/jeroen/bcrypt?branch=master&svg=true)](https://ci.appveyor.com/project/jeroen/bcrypt)
[![Coverage Status](https://codecov.io/github/jeroen/bcrypt/coverage.svg?branch=master)](https://codecov.io/github/jeroen/bcrypt?branch=master)
[![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/bcrypt)](http://cran.r-project.org/package=bcrypt)
[![CRAN RStudio mirror downloads](http://cranlogs.r-pkg.org/badges/bcrypt)](http://cran.r-project.org/web/packages/bcrypt/index.html)
[![Github Stars](https://img.shields.io/github/stars/jeroen/bcrypt.svg?style=social&label=Github)](https://github.com/jeroen/bcrypt)

> An R interface to the OpenBSD 'blowfish' password hashing algorithm,
  as described in "A Future-Adaptable Password Scheme" by Niels Provos. The
  implementation is derived from the 'py-bcrypt' module for Python which is a
  wrapper for the OpenBSD implementation.

## See Also

This package is mostly to work with existing `bcrypt` hashes. For new applications consider using scrypt as implemented in `sodium::password_store` or the `script` package.

## Hello World

```r
# Secret message as a string
passwd <- "supersecret"

# Create the hash
hash <- hashpw(passwd)
hash

# To validate the hash
identical(hash, hashpw(passwd, hash))

# Or use the wrapper
checkpw(passwd, hash)

# Use varying complexity:
hash11 <- hashpw(passwd, gensalt(11))
hash12 <- hashpw(passwd, gensalt(12))
hash13 <- hashpw(passwd, gensalt(13))

# Takes longer to verify (or crack)
system.time(checkpw(passwd, hash11))
system.time(checkpw(passwd, hash12))
system.time(checkpw(passwd, hash13))

```

## Installation

The `libbcrypt` source code is currently bundled with the package:

```r
install.packages("bcrypt")
```
