/*
	Build with
	gcc -o adpcm adpcm.c bs_codec.c ct_codec.c oki_codec.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "adpcm_codec.h"
#include "ct_codec.h"
#include "oki_codec.h"

void encode(uint8_t *source,uint8_t *dest,long length,int adpcm_mode)
{
	if(adpcm_mode == 0)
		bs_encode((int16_t*)source,dest,length);
	else if(adpcm_mode == 1)
		ct_encode((int16_t*)source,dest,length);
	else if(adpcm_mode == 2)
		oki_encode((int16_t*)source,dest,length);
	else
		exit(-1);
}

void decode(uint8_t *source,uint8_t *dest,long length,int adpcm_mode)
{
	if(adpcm_mode == 0)
		bs_decode(source,(int16_t*)dest,length);
	else if(adpcm_mode == 1)
		ct_decode(source,(int16_t*)dest,length);
	else if(adpcm_mode == 2)
		oki_decode(source,(int16_t*)dest,length);
	else
		exit(-1);
}

int main(int argc, char* argv [])
{

	unsigned long i;

	printf("PCM <-> ADPCM conversion tool\n");
	printf("2018-2019 by ctr\n");
	printf("Input format: signed 16 bit PCM little endian\n");
		
	if(argc<4)
	{
		printf("Usage: <be|bd|ye|yd|oe|od> <file> <destination file> \n");
		exit(EXIT_FAILURE);
	}

	char* mode = argv[1];
	char* file1 = argv[2];
	char* file2 = argv[3];

	int res;

	FILE* sourcefile;
	/* Load sample file */
	sourcefile = fopen(file1,"rb");
	if(!sourcefile)
	{
		printf("Could not open %s\n",file1);
		exit(EXIT_FAILURE);
	}
	fseek(sourcefile,0,SEEK_END);
	unsigned long sourcefile_size = ftell(sourcefile);
	rewind(sourcefile);
	uint8_t* source = (uint8_t*)malloc(sourcefile_size+1);
	uint8_t* dest = (uint8_t*)malloc(sourcefile_size*4+1);
	res = fread(source,1,sourcefile_size,sourcefile);
	if(res != sourcefile_size)
	{
		printf("Reading error\n");
		exit(EXIT_FAILURE);
	}
	fclose(sourcefile);

	int length;
	int adpcm_mode = -1;

	if(*mode == 'b')
	{
		adpcm_mode = 0;
		printf("Using Brian Schmidt algorithm\n");
		mode++;
	}
	else if(*mode == 'y')
	{
		adpcm_mode = 1;
		printf("Using YMZ280B algorithm\n");
		mode++;
	}
	else if(*mode == 'o')
	{
		adpcm_mode = 2;
		printf("Using OKI algorithm\n");
		mode++;
	}
	else
	{
		printf("Please specify algorithm\n");
		exit(-1);
	}

	if(*mode == 'e')
	{
		length = sourcefile_size/2;
		if(length & 1)
			length++;	// make the size even
		printf("encoding... (len= %d)\n",length);
		encode(source,dest,length,adpcm_mode);
		length /= 2;
	}
	
	else if(*mode == 'd')
	{
		length = sourcefile_size*2;
		printf("decoding... (len= %d)\n",length);
		decode(source,dest,length,adpcm_mode);
		length *= 2;
	}

	FILE *destfile;
	destfile = fopen(file2,"wb");
	if(!destfile)
	{
		printf("Could not open %s\n",file2);
		exit(EXIT_FAILURE);
	}
	for(i=0;i<length;i++)
	{
		putc(*((uint8_t*)dest+i),destfile);
	}
	fclose(destfile);
	printf("write ok %lu\n",length);

	free(source);
}
