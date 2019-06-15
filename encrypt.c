#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "aes.h"

#define BLOCK_SIZE 16

void aes_encrypt(char *filename, uint8_t *key) {
	int in = open(filename, O_RDONLY);
	int out = open(filename, O_WRONLY);
	if(in < 0 || out < 0) {
		perror("Open Failed");
	}
	
	uint8_t buf[BLOCK_SIZE];
	size_t bytes_read;
	
	int fd = open("test", O_CREAT | O_TRUNC | O_WRONLY);
	if(fd < 0) {
		perror("Test Open Failed");
	}

	while((bytes_read = read(in, buf, BLOCK_SIZE)) > 0) {
		uint8_t *input = buf;
		input[bytes_read] = 0;
		uint8_t output[bytes_read];
		
		AES128_ECB_encrypt(input, key, output);
		printf("%s", output);
		write(fd, output, bytes_read);
	
	}


	close(fd);
	close(in);
	close(out);
}

void aes_decrypt(char *filename, uint8_t *key) {
	int in = open(filename, O_RDONLY);
	if(in < 0) {
		perror("Open Failed");
	}
	
	uint8_t buf[BLOCK_SIZE];
	size_t bytes_read;

	while((bytes_read = read(in, buf, BLOCK_SIZE)) > 0) {
		uint8_t *input = buf;
		input[bytes_read] = 0;
		uint8_t output[bytes_read];
		//printf("Input:		%s\n", input);
		
		AES128_ECB_decrypt(input, key, output);
		output[bytes_read] = 0;
		printf("%s", output);
	}

	close(in);
}

int main(int argc, char **argv) {

	if(argc != 4) {
		printf("Usage: ./encrypt [mode] [filename] [key]\n");
		return 1;
	}
	char *option = argv[1];
	char *file = argv[2];
	char *key = argv[3];

	char *name = "Vineet Ramareddi";
	uint8_t *keyy = (uint8_t *) name;

	if(strcmp(option, "-e") == 0) {
		//printf("encrypting %s...\nkey: %s\n", file, key);
		aes_encrypt(file, keyy);
	}
	else if(strcmp(option, "-d") == 0) {
		printf("decrypting %s...\nkey: %s\n", file, key);
		aes_decrypt(file, keyy);
	}
	else {
		printf("Option not recognized\n");
		return 1;
	}

}
