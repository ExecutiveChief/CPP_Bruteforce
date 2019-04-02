/**
 * checkHashes - controleert de MD5-hash van elke regel van stdin
 *					met de ingelezen hashes van een opgegeven file.
 *
 *	gebruik : checkHash <hash-file-naam>
 *              met : redirect of pipe voor stdin !
 *
 * De codefile gebruikt dezelfde crypto routine als de md5.cpp file !
 *      bij problemen met compileren : zie commentaar in md5.cpp
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <openssl/evp.h>

const std::string DIGEST_TYPE = "MD5";
EVP_MD_CTX *mdctx;
const EVP_MD *md;
unsigned char md_value[EVP_MAX_MD_SIZE];

/**
 * hulp routine voor een efficiente implementatie van de MD5 hash routine.
 */
void initMD5(){
	md = EVP_get_digestbyname( DIGEST_TYPE.c_str() );
}

/**
 * Bereknd de MD5 hash van een string en geeft het resultaat in hex-notatie
 * @param  bron         de te hashen string
 * * @return            de MD5-hash in HEX
 */
std::string calcMD5( std::string bron ) {

	unsigned int md_len;

	mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, bron.c_str(), bron.length() );
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);

	// we hebben nu de hash (als bytes)
	//		nu converteren naar een HEX string
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (size_t i = 0; i < (size_t) md_len; i++) {
		ss << std::setw(2) << (int) md_value[i];
	}
	return ss.str();
}

/**
 * hulp routine voor een efficiente implementatie van de MD5 hash routine.
 */
void exitMD5(){
	EVP_cleanup();
}

/**
 * inlezen van de hashes.
 *              dit zijn de hashes waarvan we de bron (=wachtwoord) willen bepalen.
 *              we lezen deze in vanuit een tekst-bestand. 1 hash per regel.
 * @param filenm        de filenaam v/d hash-file
 *                                      met relatief path .
 * @return              een vector<string> met de hashes
 */
std::vector<std::string> readhashes( std::string filenm ){
	std::vector<std::string> hashes;
	std::ifstream hashfile( filenm );
	if ( !hashfile.is_open() ) {
		std::cout << "File kan niet worden geopend: " + filenm << std::endl;
		std::cout << "exit !"<< std::endl;
		exit(EXIT_FAILURE);
	}
	for( std::string regel; getline( hashfile, regel); ) {
		hashes.push_back(regel);
	}
	return hashes;
}

/**
 * main
 *              het programma lees een aantal hashes in vanuit een file.
 *              vervolgens worden per regels die via stdin wordt aangeboden
 *                      een MD5 hash bepaald. deze wordt vergeleken met de inelezen hashes.
 *                      Bij een match wordt een regel naar output geschreven.
 * @param  argc         moet gelijk zijn aan 1
 * @param  argv         moet de naam van de hashes file bevatten ( met relatief path)
 * @return              Exit_FAILURE als een fout optreedt , anders 0;
 */
int main(int argc, char const *argv[]) {
	// read all hashes from file
	if (argc != 2) {
		std::cout << "geef 1 argument op : hash-file"<< std::endl;
		std::cout << "exit !"<< std::endl;
		exit(EXIT_FAILURE);
	}

	// lees alle hashes in een vector, argv-1 geeft de filenaam voor de hashes.
	std::vector<std::string> hashes = readhashes( std::string( argv[1] ) );

	// eerst MD5 initialiseren
	initMD5();

	// lees stdin regel voor regel en bepaal de md5 hash. vergelijk deze met hashes in lijst
	std::string regel;
	std::string hash;
	while( getline(std::cin, regel) ) {
		hash = calcMD5(regel);
		if ( std::find(hashes.begin(), hashes.end(), hash) != hashes.end() ) {
			// SUCCES !! geef hash met wachtwoord in stdout.
			std::cout << "hash: " << hash << " - " << regel << std::endl;
		}
	}
	// MD5 afsluiten
	exitMD5();

	return 0;
}
