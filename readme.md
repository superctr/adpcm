### adpcm

ADPCM encoder/decoder.

#### Compiling

	gcc -o adpcm adpcm.c bs_codec.c ct_codec.c oki_codec.c

#### Usage

	adpcm <command> <input> <output>
	
#### Commands

| Command | Format | Description |
| --- | --- | ---
| bd      | Brian Schmidt | Decode |
| be      | Brian Schmidt | Encode |
| od      | OKI | Decode |
| oe      | OKI | Encode |
| yd      | Yamaha YMZ280B | Decode |
| ye      | Yamaha YMZ280B | Encode |

#### Copyright

Ian Karlsson 2019.

Public domain.
