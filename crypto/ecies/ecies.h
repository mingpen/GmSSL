/* crypto/ecies/ecies.h */
/* ====================================================================
 * Copyright (c) 2007 - 2015 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 */


#ifndef HEADER_ECIES_H
#define HEADER_ECIES_H

#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/asn1.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 KDFSet ALGORITHM ::= {
	{ OID x9-63-kdf PARMS HashAlgorithm } |
	{ OID nist-concatenation-kdf PARMS HashAlgorithm } | 
	{ OID tls-kdf PARMS HashAlgorithm } |
	{ OID ikev2-kdf PARMS HashAlgorithm }
 }
*/

typedef struct ecies_params_st {
	int                  kdf_nid;
	const EVP_MD        *kdf_md;
	const EVP_CIPHER    *sym_cipher;
	int                  mac_nid;
	const EVP_MD        *mac_md;
	const EVP_CIPHER    *mac_cipher;
} ECIES_PARAMS;

typedef struct ecies_ciphertext_value_st {
	ASN1_OCTET_STRING   *ephem_point;
	ASN1_OCTET_STRING   *ciphertext;
	ASN1_OCTET_STRING   *mactag;
} ECIES_CIPHERTEXT_VALUE;

DECLARE_ASN1_FUNCTIONS(ECIES_CIPHERTEXT_VALUE)

int i2d_ECIESParameters(const ECIES_PARAMS *param, unsigned char **out);
ECIES_PARAMS *d2i_ECIESParameters(ECIES_PARAMS **param, const unsigned char **in, long len);

int ECIES_set_parameters(EC_KEY *ec_key, const ECIES_PARAMS *param);
ECIES_PARAMS *ECIES_get_parameters(const EC_KEY *ec_key);
ECIES_CIPHERTEXT_VALUE *ECIES_do_encrypt(const ECIES_PARAMS *param,
	const unsigned char *in, size_t inlen, EC_KEY *ec_key);
int ECIES_do_decrypt(const ECIES_CIPHERTEXT_VALUE *cv,
	const ECIES_PARAMS *param, unsigned char *out, size_t *outlen, 
	EC_KEY *ec_key);
int ECIES_encrypt(unsigned char *out, size_t *outlen,
	const ECIES_PARAMS *param, const unsigned char *in, size_t inlen,
	EC_KEY *ec_key);
int ECIES_decrypt(unsigned char *out, size_t *outlen,
	const ECIES_PARAMS *param, const unsigned char *in, size_t inlen,
	EC_KEY *ec_key);


void ERR_load_ECIES_strings(void);

/* Error codes for the ECIES functions. */

/* Function codes. */
#define ECIES_F_I2D_ECIESPARAMETERS	100
#define ECIES_F_D2I_ECIESPARAMETERS	101
#define ECIES_F_ECIES_SET_PARAMETERS	102
#define ECIES_F_ECIES_GET_PARAMETERS	103
#define ECIES_F_ECIES_DO_ENCRYPT	104
#define ECIES_F_ECIES_DO_DECRYPT	105
#define ECIES_F_ECIES_ENCRYPT		106
#define ECIES_F_ECIES_DECRYPT		107

/* Reason codes. */
#define ECIES_R_BAD_DATA		100
#define ECIES_R_UNKNOWN_CIPHER_TYPE	101
#define ECIES_R_ENCRYPT_FAILED		102
#define ECIES_R_DECRYPT_FAILED		103
#define ECIES_R_UNKNOWN_MAC_TYPE	104
#define ECIES_R_GEN_MAC_FAILED		105
#define ECIES_R_VERIFY_MAC_FAILED	106
#define ECIES_R_ECDH_FAILED		107
#define ECIES_R_BUFFER_TOO_SMALL	108

#ifdef __cplusplus
}
#endif
#endif

