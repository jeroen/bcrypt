#include <Rinternals.h>
#include <string.h>
#include "pybc_blf.h"

/* Imported from OpenBSD */
int pybc_bcrypt(const char *, const char *, char *, size_t);
void encode_salt(char *, u_int8_t *, u_int16_t, u_int8_t);

/* Wrapper for R */
SEXP R_encode_salt(SEXP csalt_, SEXP log_rounds_){
  if(TYPEOF(csalt_) != RAWSXP)
    error("Argument csalt must be raw vector of length 16");
  if(!isInteger(log_rounds_))
    error("Argument log_rounds must be integer");
  char ret[64];
  Rbyte *csalt = RAW(csalt_);
  int csaltlen = LENGTH(csalt_);
  int log_rounds = asInteger(log_rounds_);

  if (csaltlen != 16)
    error("Invalid salt length");

  if (log_rounds < 4 || log_rounds > 31)
    error("Invalid number of rounds");

  encode_salt(ret, csalt, csaltlen, log_rounds);
  return mkString(ret);
}

SEXP R_hashpw(SEXP password_, SEXP salt_){
  if(!isString(password_) || !isString(salt_))
    error("Password and salt arguments must be strings");

  const char *password = CHAR(STRING_ELT(password_, 0));
  const char *salt = CHAR(STRING_ELT(salt_, 0));

  int password_len = LENGTH(STRING_ELT(password_, 0));
  int salt_len = LENGTH(STRING_ELT(salt_, 0));

  if (password_len < 0 || password_len > 65535)
    error("unsupported password length");

  if (salt_len < 0 || salt_len > 65535)
    error("unsupported salt length");

  char hashed[128];
  int ret = pybc_bcrypt(password, salt, hashed, sizeof(hashed));

  if (ret != 0 || strlen(hashed) < 32)
    error("Invalid salt");

  return mkString(hashed);
}
