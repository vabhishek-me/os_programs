# BITMAP Data Structure

A BITMAP is a indexing technique using bits rather than bytes. It is also known as BIT ARRAY or BITMAP INDEX.

BITMAP saves memory because you need bits, not bytes or int datatypes i.e., 4 bytes.

## Functions

 - ` getBitmapSize(size) ` - returns size for bitmap allocation using calloc
 - ` set_bit(index) ` - sets bitmap at index to 1
 - ` clear_bit(index) ` - sets bitmap at index to 0
 - ` toggle_bit(index) ` - toggles bit at index
 - ` get_bit(index) ` - returns bitmap value (0/1) at index

---
#### BITMAP Learning Resources

 - [Bitmap Wiki](https://en.wikipedia.org/wiki/Bitmap)
 - [Bit Manipulation Tactics](https://www.geeksforgeeks.org/bits-manipulation-important-tactics/)
 - <https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit>
 - [Bitmap Using Macros](https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit/263738#263738)
