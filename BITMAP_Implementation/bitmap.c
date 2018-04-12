#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define bitmapSIZE 900
#define BIT_SIZE 32

long long getBitmapSize(long long size) {
	return ( size/BIT_SIZE + (!!(size%BIT_SIZE)) );
}

void set_bit(uint32_t *bitmap, int index) {
    bitmap[index / BIT_SIZE] |= 1 << (index % BIT_SIZE);
}

void clear_bit(uint32_t *bitmap, int index) { 
    bitmap[index / BIT_SIZE] &= ~(1 << (index % BIT_SIZE));
}

int get_bit(uint32_t *bitmap, int index) {
    return 1 & (bitmap[index / BIT_SIZE] >> (index % BIT_SIZE));
}

int main() {
	uint32_t *bitmap = (uint32_t *)calloc(getBitmapSize(bitmapSIZE), sizeof(uint32_t));

	// bitmap working
	
	free(bitmap);
}
