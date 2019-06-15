#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "aes.h"

#define BLOCK_SIZE 16

/* encryption function for aes*/
void aes_encrypt(char *filename, uint8_t *key) {
	/* two fd's for one file, to read and write simultaneously */
	int in = open(filename, O_RDONLY);
	if(in < 0) {
		perror("Open Failed");
		exit(1);
	}
	
	uint8_t buf[BLOCK_SIZE];
	size_t bytes_read;
	/* reads 16 bytes at a time, encrypts and writes to file */
	while((bytes_read = read(in, buf, BLOCK_SIZE)) > 0) {
		uint8_t *input = buf;
		input[bytes_read] = 0;
		uint8_t output[BLOCK_SIZE+1];
		output[BLOCK_SIZE] = 0;
		
		AES128_ECB_encrypt(input, key, output);

		write(out, output, BLOCK_SIZE);
	}

	close(in);

}
/* decryption function using aes */
void aes_decrypt(char *filename, uint8_t *key) {
	int in = open(filename, O_RDONLY);
	if(in < 0) {
		perror("Open Failed");
	}
	
	uint8_t buf[BLOCK_SIZE];
	size_t bytes_read;
	/* read 16 bytes at time, decrypts and outputs to stdout */
	while((bytes_read = read(in, buf, BLOCK_SIZE)) > 0) {
		uint8_t *input = buf;
		input[bytes_read] = 0;
		uint8_t output[bytes_read];
		
		AES128_ECB_decrypt(input, key, output);
		output[bytes_read] = 0;
		printf("%s", output);
	}

	close(in);

}

int main(int argc, char **argv) {
	/* ensures  proper arguments are passed */
	if(argc != 4) {
		printf("Usage: ./encrypt [mode] [filename] [key]\n");
		return 1;
	}
	/* reads user's inputs */
	char *option = argv[1];
	char *file = argv[2];
	char *charKey = argv[3];
	/* key casted to an array of uint8_t's */
	uint8_t *key = (uint8_t *) charKey;
	/* encrypt for -e option, decrypt for -d option */
	if(strcmp(option, "-e") == 0) {
		printf("encrypting %s...\nkey: %s\n", file, key);
		aes_encrypt(file, key);
	}
	else if(strcmp(option, "-d") == 0) {
		printf("decrypting %s...\nkey: %s\n", file, key);
		aes_decrypt(file, key);
	}
	else {
		printf("Option not recognized\n");
		return 1;
	}

}
