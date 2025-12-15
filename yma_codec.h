#ifndef YMA_CODEC_H
#define YMA_CODEC_H

/*
	Encode and decode algorithms for
	Yamaha ADPCM-A
	
	2019 by superctr.
*/

#include <stdint.h>

/**
 * Given (len) amount of PCM samples in buffer,
 * return encoded ADPCM samples in outbuffer.
 * Output buffer should be at least (len/2) elements large.
 * Set anti_overflow to 1 to prevent overflows in the encoded data.
 */
void yma_encode(int16_t *buffer,uint8_t *outbuffer,long len, uint8_t anti_overflow);

/**
 * Given ADPCM samples in (buffer), return (len) amount of
 * decoded PCM samples in (outbuffer).
 * Output buffer should be at least (len*2) elements large.
 */
void yma_decode(uint8_t *buffer,int16_t *outbuffer,long len);

#endif
