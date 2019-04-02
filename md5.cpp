/**
 *	TEST programma voor de openssl lib's
 *	------------------------------------
 *	op de meeste LINUX systemen zal openssl geinstaleerd zijn.
 *	maar voor het gebruik van de crypto functionaliteit in code
 *      moeten we de 'develop' variant geinstalleerd hebben !
 *
 *	Je kunt dit doen met :
 *              sudo apt-get install libssl-dev
 *
 *	ter controle kun je deze codefile compileren met :
 *        g++ -Wall -std=c++11 -o md5 md5.cpp -lcrypto
 *
 *        merk op : '-lcrypto' aan het einde !!
 *
 *  source : https://www.openssl.org/docs/man1.0.2/crypto/EVP_DigestInit.html
   ------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char *argv[])
{
	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	char mess1[] = "Test Message\n";
	char mess2[] = "Hello World\n";
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len, i;

	OpenSSL_add_all_digests();

	if(!argv[1]) {
		printf("Usage: mdtest digestname\n");
		exit(1);
	}

	md = EVP_get_digestbyname(argv[1]);

	if(!md) {
		printf("Unknown message digest %s\n", argv[1]);
		exit(1);
	}

	mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
	EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);

	printf("Digest is: ");
	for(i = 0; i < md_len; i++)
		printf("%02x", md_value[i]);
	printf("\n");

	/* Call this once before exit. */
	EVP_cleanup();
	exit(0);
}
