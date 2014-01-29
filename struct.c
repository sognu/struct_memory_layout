/*Written by Chad Miller for CS 4400, Oct. 2013.*/
#include "struct.h"
#include "funcs.h"
#include "string.h"
#include <stdint.h>
#include <stdio.h>

uint16_t swap_endian_2_bytes(uint16_t x);
uint16_t swap_endian_2_bytes_alt(uint16_t x);
uint32_t swap_endian_4_bytes(uint32_t x);
uint32_t swap_endian_4_bytes_alt(uint32_t x);
uint64_t swap_endian_8_bytes(uint64_t x);
uint64_t swap_endian_8_bytes_alt(uint64_t x);
uint64_t l2u (long long l);
long long u2l (uint64_t u);
uint32_t i2u (int i);
int u2i (uint32_t u);
int long_2wide(long f0);
int ulong_long_2wide(unsigned long long f1);
int uchar_2wide(unsigned char f2);
int uchar_2wide_alt(unsigned char f2);
int int_2wide(int f3);
int uint_2wide(unsigned int f4);
void* memcpy_alt(void* dest, const void* src, size_t count);
int sign_bit (long f0);


/*
 * return a struct containing the same values as the argument struct
 * except that each field has its byte order reversed
 *
 * RESTRICTION: this function must not use arrays or pointers at all;
 * accomplish the byte swapping using shift operators
 */
struct s1 endian_swap_s1_shift (struct s1 a){

  a.f1 = u2i(swap_endian_4_bytes(i2u(a.f1)));
  a.f3 = swap_endian_4_bytes(a.f3);
  a.f4 = u2i(swap_endian_4_bytes(i2u(a.f4)));
  a.f5 = u2l(swap_endian_8_bytes(l2u(a.f5)));

  return a;
}


/*
 * return a struct containing the same values as the argument struct
 * except that each field has its byte order reversed
 *
 * RESTRICTION: this function must not use shift operators;
 * accomplish the byte swapping using pointers and/or arrays
 */
struct s1 endian_swap_s1_ptr (struct s1 a){

  a.f1 = u2i(swap_endian_4_bytes_alt(i2u(a.f1)));
  a.f3 = swap_endian_4_bytes_alt(a.f3);
  a.f4 = u2i(swap_endian_4_bytes_alt(i2u(a.f4)));
  a.f5 = u2l(swap_endian_8_bytes_alt(l2u(a.f5)));

  return a;
}

/*
 * convert a standard (padded) struct into a packed struct containing
 * the same fields
 *
 * the first argument points to a struct s2_packed, the second
 * argument points to a struct s2
 *
 * therefore, your job is to copy data referenced by the second
 * argument into space referenced by the first argument
 *
 * RESTRICTION: all data movement must be through pointer/array
 * operations, no actual struct code is permitted
 */
void pack_s2 (char *s2_packed, char *s2){

  int k;    
  for(k = 0; k < 8; k++)
    s2_packed[k] = s2[k];
  for(; k < 12; k++)
    s2_packed[k] = s2[k];
  for(; k < 16; k++)
    s2_packed[k] = s2[k];
  for(; k < 20; k++)
    s2_packed[k] = s2[k];
  for(; k < 22; k++)
    s2_packed[k] = s2[k];
  for(; k < 26; k++)
    s2_packed[k] = s2[k+2];
}


/*
 * convert a packed struct into a stanard (padded) struct containing
 * the same fields
 *
 * the first argument points to a struct s2, the second
 * argument points to a struct s2_packed
 *
 * therefore, your job is to copy data referenced by the second
 * argument into space referenced by the first argument
 *
 * RESTRICTION: all data movement must be through pointer/array
 * operations, no actual struct code is permitted
 */
void unpack_S2 (char *s2, char *s2_packed){

  int k;
  for(k = 0; k < 8; k++)  
    s2[k] = s2_packed[k]; 
  for(; k < 12; k++)
    s2[k] = s2_packed[k];
  for(; k < 16; k++)
    s2[k] = s2_packed[k];
  for(; k < 20; k++)
    s2[k] = s2_packed[k];
  for(; k < 22; k++)
    s2[k] = s2_packed[k];
  for(; k < 26; k++)
    s2[k+2] = s2_packed[k];
}



/*
 * convert a struct with full-width fields into a struct containing
 * bitfields
 *
 * the first argument points to a struct s3_bitfield, the second
 * argument points to a struct s3
 *
 * therefore, your job is to copy data referenced by the second
 * argument into space referenced by the first argument
 *
 * RETURN VALUE: if the value in any full-width field cannot be
 * represented in its corresponding bitfield, return -1; otherwise
 * return 0
 *
 * RESTRICTION: all data movement must be through pointer/array/shift
 * operations, no actual struct code is permitted
 */
int pack_s3 (char *s3_bitfield, char *s3){
 
  long f0 = 0;
  unsigned long long f1 = 0;
  unsigned char f2 = 0;
  int f3 = 0;
  unsigned int f4 = 0;
  unsigned char f5 = 0;
 
  memcpy_alt(&f0, &s3[0], 4);  
  if(long_2wide(f0))
    return -1;
  else if (sign_bit(f0))
    f0 = f0 & 0xFFF;
  memcpy_alt(&f1, &s3[4], 8);  
  if(ulong_long_2wide(f1))
    return -1;  
  memcpy_alt(&f2, &s3[12], 1);   
  if(uchar_2wide(f2)) 
    return -1; 
  memcpy_alt(&f3, &s3[16], 4);   
  if(int_2wide(f3)) 
    return -1; 
  memcpy_alt(&f4, &s3[20], 4);   
  if(uint_2wide(f4))
    return -1;
  memcpy_alt(&f5, &s3[24], 1);   
  if(uchar_2wide_alt(f5))
    return -1;

 s3_bitfield[0] = f0 & 0xFF;;
 s3_bitfield[1] = ((f0 & 0xF00) >>8); 
 s3_bitfield[1] |= ((f1 & 0xF) <<4); 
 s3_bitfield[2] = ((f1 & 0xFF0) >>4); 
 s3_bitfield[3] = ((f1 & 0xFF000) >>12); 
 s3_bitfield[4] = ((f1 & 0xFF00000) >>20); 
 s3_bitfield[5] = ((f1 & 0x10000000) >>28);
 s3_bitfield[5] |= ((f2 & 0x3F) << 1);
 s3_bitfield[5] |= ((f3 & 0x1) << 7);
 /*There are padding bytes thrown in here*/
 s3_bitfield[8] = (f4 & 0xFF);
 s3_bitfield[9] = ((f4 & 0xFF00) >>8);
 s3_bitfield[10] = ((f4 & 0xF0000) >>16);
 s3_bitfield[11] = (f5 & 0x7F);
       
  return 0; /*all data fields fit*/
}

/*
 * convert a struct with bitfields into a struct containing
 * full-width fields
 *
 * the first argument points to a struct s3, the second
 * argument points to a struct s3_bitfield
 *
 * therefore, your job is to copy data referenced by the second
 * argument into space referenced by the first argument
 *
 * RESTRICTION: all data movement must be through pointer/array/shift
 * operations, no actual struct code is permitted
 */
void unpack_s3 (char *s3, char *s3_bitfield){

  long f0 = 0;
  unsigned long long f1 = 0;
  unsigned char f2 = 0;
  int f3 = 0;
  unsigned int f4 = 0;
  unsigned char f5 = 0;
   
  f0 =  s3_bitfield[0] & 0xFF;
  f0 |= ((s3_bitfield[1] & 0xF) <<8); 
  f1 = (s3_bitfield[1] & 0xF0) >>4;
  f1 |= (s3_bitfield[2] & 0xFF) <<4;
  f1 |= (s3_bitfield[3] & 0xFF) <<12;
  f1 |= (s3_bitfield[4] & 0xFF) <<20;
  f1 |= (s3_bitfield[5] & 0x1)  <<28;
  f2 = (s3_bitfield[5] & (0x3F<<1))>>1;
  f3 |= (s3_bitfield[5] & 0x80) >>7;
  f4 = (s3_bitfield[8] & 0xFF);  
  f4 |= (s3_bitfield[9] & 0xFF) <<8;
  f4 |= (s3_bitfield[10] & 0xF) <<16;
  f5 = (s3_bitfield[11] & 0x7F);

  s3[0] = f0 & 0xFF;
  if(f0 & 0x800){      /*sign extend*/
    s3[1] =  (((f0 & 0xF00) >>8) ^ 0xF0); 
    s3[2] = 0xFF;
    s3[3] = 0xFF;                        
  } 
  else{                /*2 bytes empty space*/
  s3[1] = ((f0 & 0xF00) >>8); 
  s3[2] = 0x0;
  s3[3] = 0x0; 
  }
  s3[4] = f1 & 0xFF;
  s3[5] = (f1 & 0xFF00) >>8;
  s3[6] = (f1 & 0xFF0000) >>16;
  s3[7] = (f1 & 0x1F000000) >>24;
  /*4 bytes empty space*/ 
  s3[8] = 0x0;
  s3[9] = 0x0;
  s3[10] = 0x0;
  s3[11] = 0x0;
  s3[12] = f2 & 0x3F;
  /*3 bytes of padding*/
  /* s3[16] = f3 & 0x1;   */
  if(f3){               /*sign extend*/
    s3[16] = 0xFF;
    s3[17] = 0xFF;               
    s3[18] = 0xFF;
    s3[19] = 0xFF;
   }
  else { /*3 bytes of empty space*/
    s3[16] = 0x0;
    s3[17] = 0x0;
    s3[18] = 0x0;
    s3[19] = 0x0;
  }
  s3[20] = f4 & 0xFF;
  s3[21] = (f4 & 0xFF00) >>8;
  s3[22] = (f4 & 0xF0000) >> 16;
  /*1 byte of empty space*/ 
  s3[24] = f5 & 0x7F;
  /*3 bytes of padding*/

}

/*** Helper functions for endian_swap_s1_shift****/
uint16_t swap_endian_2_bytes(uint16_t x){

  return ((x & 0x00FF) << 8) | ((x & 0xFF00) >> 8);
}

uint32_t swap_endian_4_bytes(uint32_t x){

  return ((x & 0x000000FF) << 24) |
         ((x & 0x0000FF00) << 8) |
         ((x & 0x00FF0000) >> 8) |
         ((x & 0xFF000000) >> 24);
}

uint64_t swap_endian_8_bytes(uint64_t x){

  return ((x & 0x00000000000000FFLL) << 56) |
         ((x & 0x000000000000FF00LL) << 40) |
         ((x & 0x0000000000FF0000LL) << 24) |
         ((x & 0x00000000FF000000LL) << 8)  |
         ((x & 0x000000FF00000000LL) >> 8)  |
         ((x & 0x0000FF0000000000LL) >> 24) |
         ((x & 0x00FF000000000000LL) >> 40) |
         ((x & 0xFF00000000000000LL) >> 56);
}


/*** Helper functions for endian_swap_s1_ptr****/
uint16_t swap_endian_2_bytes_alt(uint16_t x){

  uint16_t swapped;

  ((char*)&swapped)[0] = ((char*)&x)[1];
  ((char*)&swapped)[1] = ((char*)&x)[0];
  
return swapped;
}



uint32_t swap_endian_4_bytes_alt(uint32_t x){

  uint32_t swapped;

  ((char*)&swapped)[0] = ((char*)&x)[3];
  ((char*)&swapped)[1] = ((char*)&x)[2];
  ((char*)&swapped)[2] = ((char*)&x)[1];
  ((char*)&swapped)[3] = ((char*)&x)[0];
  
return swapped;
}



uint64_t swap_endian_8_bytes_alt(uint64_t x){

  uint64_t swapped;

  ((char*)&swapped)[0] = ((char*)&x)[7];
  ((char*)&swapped)[1] = ((char*)&x)[6];
  ((char*)&swapped)[2] = ((char*)&x)[5];
  ((char*)&swapped)[3] = ((char*)&x)[4];
  ((char*)&swapped)[4] = ((char*)&x)[3];
  ((char*)&swapped)[5] = ((char*)&x)[2];
  ((char*)&swapped)[6] = ((char*)&x)[1];
  ((char*)&swapped)[7] = ((char*)&x)[0];

return swapped;
}

/****Helper functions for both swap_endian_s1_shift and swap_endian_s1_ptr****/
int u2i (uint32_t u)
{
  int i;
  memcpy (&i, &u, 4);
  return i;
}

uint32_t i2u (int i)
{
  uint32_t u;
  memcpy (&u, &i, 4);
  return u;
}

long long u2l (uint64_t u)
{
  long long l;
  memcpy (&l, &u, 8);
  return l;
}

uint64_t l2u (long long l)
{
  uint64_t u;
  memcpy (&u, &l, 8);
  return u;
}


/****Helper functions for pack_s3****/
int long_2wide(long f0){
 
  if(sign_bit(f0)){
    return !((f0 & 0xFFFFF800) == 0xFFFFF800);
   
  }                             
  else return !!(f0 & 0x7FFFF000); /*unsigned too wide*/
}

int sign_bit (long f0){

  return !!(((f0 & 0x80000000) >>31) & 0x1);
}

int ulong_long_2wide(unsigned long long f1){

  return !!(f1 & 0xFFFFFFFFE0000000LL);
}

int uchar_2wide(unsigned char f2){

  return !!(0xC0 & f2);
}

int int_2wide(int f3){
  
  return (f3 != 0xFFFFFFFF && f3 != 0x00000000);
  /* return !!(0xFE & f3); */
}

int uint_2wide(unsigned int f4){
 
  return !!(0xFFFF0000 & f4);
}

int uchar_2wide_alt(unsigned char f2){

  return !!(0x80 & f2);
}

/*Our own memcpy*/
void* memcpy_alt(void* dest, const void* src, size_t count) {
  char* dst8 = (char*)dest;
  char* src8 = (char*)src;

  while (count--) {
    *dst8++ = *src8++;
  }
  return dest;
}

