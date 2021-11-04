#include <openssl/ssl.h>
#include <openssl/err.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#ifndef CERT_PATH
# define CERT_PATH
#endif

SSL_CTX *Init() {
  SSL_library_init();
  SSL_load_error_strings();
  ERR_load_BIO_strings();
  OpenSSL_add_all_algorithms();
  SSL_CTX *sslctx;
  assert (sslctx = SSL_CTX_new(TLSv1_method()));
  /* These two file were created with this command:
      openssl req -x509 -newkey rsa:512 -keyout server.key -out server.pem -days 9999 -nodes -subj /CN=a/
  */
  assert(SSL_CTX_use_certificate_file(sslctx, "server.pem", SSL_FILETYPE_PEM));
  assert(SSL_CTX_use_PrivateKey_file(sslctx, "server.key", SSL_FILETYPE_PEM));
  return sslctx;
}

int main() {
  static SSL_CTX *sslctx = Init();
  SSL *ssl = SSL_new(sslctx);
  BIO *rbio = BIO_new(BIO_s_mem());
  BIO *wbio = BIO_new(BIO_s_mem());
  SSL_set_bio(ssl, rbio, wbio);
  SSL_set_accept_state(ssl);

  #ifdef __AFL_HAVE_MANUAL_CONTROL
    __AFL_INIT();
  #endif

  uint8_t data[100] = {0};
  size_t size = read(STDIN_FILENO, data, 100);
  if (size == -1) {
    printf("Failed to read from stdin\n");
    return(-1);
  }
  BIO_write(rbio, data, size);

  SSL_do_handshake(ssl);
  SSL_free(ssl);
  return 0;
}
