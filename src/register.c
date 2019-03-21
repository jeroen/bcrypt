#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

extern SEXP R_bcrypt_pbkdf(SEXP, SEXP, SEXP, SEXP);
extern SEXP R_encode_salt(SEXP, SEXP);
extern SEXP R_hashpw(SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"R_bcrypt_pbkdf", (DL_FUNC) &R_bcrypt_pbkdf, 4},
  {"R_encode_salt",  (DL_FUNC) &R_encode_salt,  2},
  {"R_hashpw",       (DL_FUNC) &R_hashpw,       2},
  {NULL, NULL, 0}
};

attribute_visible void R_init_bcrypt(DllInfo *dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
