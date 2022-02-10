#include "woody.h"

uint64_t		keygen(void)
{	
	return ((((uint64_t) rand() <<  0) & 0x000000000000FFFFull) | 
			(((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) | 
			(((uint64_t) rand() << 32) & 0x0000FFFF00000000ull) |
			(((uint64_t) rand() << 48) & 0xFFFF000000000000ull));
}

static uint64_t	rotate_key(uint64_t key)
{
	//return ((key << 8) & (key >> 56));
	return (key * 3);
}

void			encrypt(t_woody *woody, t_segments *seg)
{
	uint64_t	key_tmp;
	size_t		deb;
	size_t		end;

	key_tmp = woody->key;
	deb = seg->code_off;
	end = seg->code_off + seg->code_len;
	while (deb < end)
	{
		woody->bindest[deb] ^= (char)key_tmp;
		key_tmp = rotate_key(key_tmp);
		deb++;
	}
}
