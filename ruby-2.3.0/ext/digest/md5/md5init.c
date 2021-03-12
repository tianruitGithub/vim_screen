/* $RoughId: md5init.c,v 1.2 2001/07/13 19:49:10 knu Exp $ */
/* $Id: md5init.c 52694 2015-11-21 04:35:57Z naruse $ */

#include <ruby/ruby.h>
#include "../digest.h"
#if defined(MD5_USE_OPENSSL)
#include "md5ossl.h"
#elif defined(MD5_USE_COMMONDIGEST)
#include "md5cc.h"
#else
#include "md5.h"
#endif

static const rb_digest_metadata_t md5 = {
    RUBY_DIGEST_API_VERSION,
    MD5_DIGEST_LENGTH,
    MD5_BLOCK_LENGTH,
    sizeof(MD5_CTX),
    (rb_digest_hash_init_func_t)MD5_Init,
    (rb_digest_hash_update_func_t)MD5_Update,
    (rb_digest_hash_finish_func_t)MD5_Finish,
};

/*
 * A class for calculating message digests using the MD5
 * Message-Digest Algorithm by RSA Data Security, Inc., described in
 * RFC1321.
 */
void
Init_md5(void)
{
    VALUE mDigest, cDigest_Base, cDigest_MD5;

    rb_require("digest");

#if 0
    mDigest = rb_define_module("Digest"); /* let rdoc know */
#endif
    mDigest = rb_path2class("Digest");
    cDigest_Base = rb_path2class("Digest::Base");

    cDigest_MD5 = rb_define_class_under(mDigest, "MD5", cDigest_Base);

#undef RUBY_UNTYPED_DATA_WARNING
#define RUBY_UNTYPED_DATA_WARNING 0
    rb_iv_set(cDigest_MD5, "metadata",
	      Data_Wrap_Struct(0, 0, 0, (void *)&md5));
}
