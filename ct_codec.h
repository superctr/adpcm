#ifndef CT_CODEC_H
#define CT_CODEC_H

/*
	Encode and decode algorithms for
	YMZ280B
	
	2018 by superctr.
*/

#include <stdint.h>

/**
 * Given (len) amount of PCM samples in buffer,
 * return encoded ADPCM samples in outbuffer.
 * Output buffer should be at least (len/2) elements large.
 */
void ct_encode(int16_t *buffer,uint8_t *outbuffer,long len);

/**
 * Given ADPCM samples in (buffer), return (len) amount of
 * decoded PCM samples in (outbuffer).
 * Output buffer should be at least (len*2) elements large.
 */
void ct_decode(uint8_t *buffer,int16_t *outbuffer,long len);

#endif
