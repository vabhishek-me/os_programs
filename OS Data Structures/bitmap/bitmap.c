#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

void toggle_bit(uint32_t *bitmap, int index) {
    bitmap[index / BIT_SIZE] ^= (1 << (index % BIT_SIZE));
}

int get_bit(uint32_t *bitmap, int index) {
    return 1 & (bitmap[index / BIT_SIZE] >> (index % BIT_SIZE));
}

int main() {
	int size = 10;
	uint32_t *bitmap = (uint32_t *)calloc(getBitmapSize(size), sizeof(uint32_t));
	
	for(int i=0; i<size; i++)
		printf("\n%d -> %d", i, get_bit(bitmap, i));

	printf("\n\n Setting bits 2, 3, 5, 7 and toggling bit 1\n");
	set_bit(bitmap, 2);
	set_bit(bitmap, 3);
	set_bit(bitmap, 5);
	set_bit(bitmap, 7);
	toggle_bit(bitmap, 1);
	
	for(int i=0; i<size; i++)
		printf("\n%d -> %d", i, get_bit(bitmap, i));
	printf("\n\n");
	
	free(bitmap);
	return 0;
}
