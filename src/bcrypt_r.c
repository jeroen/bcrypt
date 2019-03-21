#include <Rinternals.h>
#include <string.h>
#include "pybc_blf.h"

/* Imported from OpenBSD */
int pybc_bcrypt(const char *, const char *, char *, size_t);
void encode_salt(char *, u_int8_t *, u_int16_t, u_int8_t);

/* Wrapper for R */
SEXP R_encode_salt(SEXP csalt_, SEXP log_rounds_){
  if(TYPEOF(csalt_) != RAWSXP)
    Rf_error("Argument csalt must be raw vector of length 16");
  if(!Rf_isInteger(log_rounds_))
    Rf_error("Argument log_rounds must be integer");
  char ret[64];
  Rbyte *csalt = RAW(csalt_);
  int csaltlen = LENGTH(csalt_);
  int log_rounds = Rf_asInteger(log_rounds_);

  if (csaltlen != 16)
    Rf_error("Invalid salt length");

  if (log_rounds < 4 || log_rounds > 31)
    Rf_error("Invalid number of rounds");

  encode_salt(ret, csalt, csaltlen, log_rounds);
  return Rf_mkString(ret);
}

SEXP R_hashpw(SEXP password_, SEXP salt_){
  if(!Rf_isString(password_) || !Rf_isString(salt_))
    Rf_error("Password and salt arguments must be strings");

  const char *password = CHAR(STRING_ELT(password_, 0));
  const char *salt = CHAR(STRING_ELT(salt_, 0));

  int password_len = LENGTH(STRING_ELT(password_, 0));
  int salt_len = LENGTH(STRING_ELT(salt_, 0));

  if (password_len < 0 || password_len > 65535)
    Rf_error("unsupported password length");

  if (salt_len < 0 || salt_len > 65535)
    Rf_error("unsupported salt length");

  char hashed[128];
  int ret = pybc_bcrypt(password, salt, hashed, sizeof(hashed));

  if (ret != 0 || strlen(hashed) < 32)
    Rf_error("Invalid salt");

  return Rf_mkString(hashed);
}

SEXP R_bcrypt_pbkdf(SEXP pass, SEXP salt, SEXP rounds, SEXP size){
  int len = Rf_asInteger(size);
  SEXP key = PROTECT(Rf_allocVector(RAWSXP, len));
  if(bcrypt_pbkdf(RAW(pass), Rf_length(pass), RAW(salt), Rf_length(salt),
               RAW(key), Rf_length(key), Rf_asInteger(rounds)) != 0){
    Rf_error("Failure in bcrypt key-derivation");
  }
  UNPROTECT(1);
  return key;
}
