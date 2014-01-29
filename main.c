/*Written by Chad Miller for CS 4400, Oct. 2013.*/
#include <stdio.h>
#include <assert.h>
#include <byteswap.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "struct.h"
#include "funcs.h"

/*Three groups of tests*/
void test_s1(void);
void test_s2(void);
void test_s3(void);

/*Misc helper funcs*/
struct s1 get_s1(unsigned char f0, long f1, unsigned char f2,
		 unsigned int f3, int f4, long long f5);
void test_endian_swap_s1(struct s1 a, struct s1 a_swapped);
void s2p(char *s2_arr, struct s2 s);
void s2p_alt(char *s2_arr, struct s2_packed s);
struct s2 get_s2(unsigned long long f0, long f1,
		     int f2, unsigned long f3, unsigned short f4, unsigned int f5);
struct s2_packed get_s2_alt(unsigned long long f0, long f1,
		 int f2, unsigned long f3, unsigned short f4, unsigned int f5);

void test_pack_s2(char *s2_packed, char *s2);
struct s3 get_s3(long f0, unsigned long long f1,
		 unsigned char f2, int f3, unsigned int f4, unsigned char f5);

struct s3_bitfield get_s3_alt(long f0, unsigned long long f1,
			      unsigned char f2, int f3, unsigned int f4, unsigned char f5);
void s3p(char *s3_arr, struct s3 s);
void s3p_alt(char *s3_arr, struct s3_bitfield s);
void test_pack_s3(char *s3_packed, char *s3);
void unix_error(char *msg); /* unix-style error */
void *Malloc(size_t size);

int main (void)
{
   test_s1();
   test_s2();
   test_s3();
  
   return 0;
}


void test_s1(void){

  struct s1 a, b, c, d, e;
  struct s1 a_swapped, b_swapped, c_swapped, d_swapped, e_swapped;

  a = get_s1(0x01, 0x000EEF00, 0x01,
  		     0x000EEF00, 0x000EEF00, 0x000000EEF00000000LL);
  b = get_s1(0x01, 0x01000000, 0x01,
  		     0x01000000, 0x01000000, 0x0100000000000000LL);
        
  c = get_s1(0x01, 0x00100000, 0x01,
  		     0x00100000, 0x00100000, 0x0010000000000000LL);

  d = a;
  e = b;
  a_swapped = endian_swap_s1_shift(a);
  b_swapped = endian_swap_s1_shift(b);
  c_swapped = endian_swap_s1_shift(c);

  /*Three tests for bit shift swap*/
  test_endian_swap_s1(a, a_swapped);
  test_endian_swap_s1(b, b_swapped);
  test_endian_swap_s1(c, c_swapped);

  d_swapped = endian_swap_s1_ptr(d);
  e_swapped = endian_swap_s1_ptr(e);

  /*Two tests for pointer swap*/
  test_endian_swap_s1(d, d_swapped);
  test_endian_swap_s1(e, e_swapped);

}

void test_s2(void){

  struct s2 s1, s2, s3;
  struct s2_packed s4, s5;
  char *f;
  char  *f_packed;
   
  f = Malloc(sizeof(struct s2));
  f_packed = Malloc(sizeof(struct s2_packed));
     
  s1 = get_s2(0x1000000000000000ULL, 0x10000000, 0x10000000,
	     0x10000000, 0x1000,  0x10000000);
    
  s2 = get_s2(0x0100000000000000ULL, 0x01000000, 0x01000000,
	     0x01000000, 0x0100,  0x01000000);
    
  s3 = get_s2(0x0010000000000000ULL, 0x00100000, 0x00100000,
	     0x00100000, 0x0010,  0x00100000);    
    
  s4 = get_s2_alt(0x00010000000000000ULL, 0x000100000, 0x000100000,
	     0x000100000, 0x0001,  0x00010000);    
  
  s5 = get_s2_alt(0x000010000000000000ULL, 0x0000100000, 0x0000100000,
	     0x0000100000, 0x0001,  0x000010000);       


  /*Three tests for s2 pack*/   
   s2p(f, s1);
   pack_s2(f_packed, f);
   test_pack_s2(f_packed, f);

   s2p(f, s2);
   pack_s2(f_packed, f);
   test_pack_s2(f_packed, f);

   s2p(f, s3);
   pack_s2(f_packed, f);
   test_pack_s2(f_packed, f);

   
   /*Two tests for s2 unpack*/
   s2p_alt(f_packed, s4);
   unpack_S2(f, f_packed);
   test_pack_s2(f_packed, f);

   s2p_alt(f_packed, s5);
   unpack_S2(f, f_packed);
   test_pack_s2(f_packed, f);

   free(f);
   free(f_packed);

}


void test_s3(void){

  struct s3 s1, s2, s3;
  struct s3_bitfield s4, s5;
  char *f;
  char *f_bitfield;
   
  f = Malloc(sizeof(struct s3));
  f_bitfield = Malloc(sizeof(struct s3_bitfield));
     
     s1 = get_s3(0x001, 0x000001, 0x01, 0xFFFFFFFF, 0x00001 , 0x01);
   
     s2 = get_s3(0xFF, 0x00FF0, 0x10, 0xFFFFFFFF, 0x00010 , 0x10);

     s3 = get_s3(0x010, 0x000010, 0x10, 0x0, 0x00010 , 0x10);

     s4 = get_s3_alt(0xF1, 0x0000F1, 0x31,
     	             0x1, 0x000F1 , 0x71);
    
     s5 = get_s3_alt(0xEFF, 0xEEFF, 0x3F,
     	             0x1, 0xEFF , 0x7F);
    
  /*Three tests for s2 pack*/   
   s3p(f, s1);  
   if(pack_s3(f_bitfield, f) == 0)
   test_pack_s3(f_bitfield, f);
   
   s3p(f, s2); 
   if(pack_s3(f_bitfield, f) == 0)
   test_pack_s3(f_bitfield, f);
   
   s3p(f, s3); 
   if(pack_s3(f_bitfield, f) == 0)
   test_pack_s3(f_bitfield, f);
   

   /*Two tests for s2 unpack*/
   s3p_alt(f_bitfield, s4);
   unpack_s3(f, f_bitfield);
   test_pack_s3(f_bitfield, f);
 
   s3p_alt(f_bitfield, s5);
   unpack_s3(f, f_bitfield);
   test_pack_s3(f_bitfield, f);

  
   /*Signed too wide*/
   s1 = get_s3(0xFFEFFFFF, 0x00FF0, 0x10, 0xFFFFFFFF, 0x00010 , 0x10);
   s3p(f, s1); 
   assert(pack_s3(f_bitfield, f) == -1);
 
 
   /*Unsigned too wide*/  
   s2 = get_s3(0x01000000, 0x0100000000000000ULL, 0x01,
   	      0x01000000, 0x01000000 , 0x01);
   s3p(f, s2); 
   assert(pack_s3(f_bitfield, f) == -1);  
 
   s3 = get_s3(0x00100000, 0x0010000000000000ULL, 0x10,
   	      0x00100000, 0x00100000 , 0x10);
   s3p(f, s3);  
   assert(pack_s3(f_bitfield, f) == -1);

   free(f);
   free(f_bitfield);

}



/****Helper function for test_s1****/
struct s1 get_s1(unsigned char f0, long f1, unsigned char f2,
	         unsigned int f3, int f4, long long f5){

  struct s1 s1_test;
  s1_test.f0 = f0;
  s1_test.f1 = f1;
  s1_test.f2 = f2;
  s1_test.f3 = f3;
  s1_test.f4 = f4;
  s1_test.f5 = f5;
  return s1_test;
}


void test_endian_swap_s1(struct s1 a, struct s1 a_swapped){

  struct s1 c = endian_swap_s1_shift(endian_swap_s1_shift(a));
  assert(a.f1 == c.f1); 
  assert(a.f3 == c.f3); 
  assert(a.f4 == c.f4); 
  assert(a.f5 == c.f5); 
  
  struct s1 d = endian_swap_s1_ptr(a);
  assert(a_swapped.f1 == d.f1); 
  assert(a_swapped.f3 == d.f3); 
  assert(a_swapped.f4 == d.f4); 
  assert(a_swapped.f5 == d.f5);   
  
  assert(a_swapped.f1 == __bswap_constant_32(a.f1));
  assert(a_swapped.f3 == __bswap_constant_32(a.f3));
  assert(a_swapped.f4 == __bswap_constant_32(a.f4));
  assert(a_swapped.f5 == __bswap_constant_64(a.f5));
 
}

/****Helper functions for test_s2****/
void s2p(char *s2_arr, struct s2 s){

  int len = sizeof(struct s2);
  memcpy(s2_arr, &s, len);
}


void s2p_alt(char *s2_arr, struct s2_packed s){

  int len = sizeof(struct s2_packed);
  memcpy(s2_arr, &s, len);
}


struct s2 get_s2(unsigned long long f0, long f1,
		     int f2, unsigned long f3, unsigned short f4, unsigned int f5){

  struct s2 s;
  s.f0 = f0;
  s.f1 = f1;
  s.f2 = f2;
  s.f3 = f3;
  s.f4 = f4;
  s.f5 = f5;
  return s;
}


struct s2_packed get_s2_alt(unsigned long long f0, long f1,
		     int f2, unsigned long f3, unsigned short f4, unsigned int f5){

  struct s2_packed s;
  s.f0 = f0;
  s.f1 = f1;
  s.f2 = f2;
  s.f3 = f3;
  s.f4 = f4;
  s.f5 = f5;
  return s;
}


void test_pack_s2(char *s2_packed, char *s2){


  struct s2 s;
  struct s2_packed s_p;
  memcpy(&s, s2, sizeof(struct s2));
  memcpy(&s_p, s2_packed, sizeof(struct s2_packed));
  assert(s_p.f0 == s.f0);
  assert(s_p.f1 == s.f1);
  assert(s_p.f2 == s.f2);
  assert(s_p.f3 == s.f3);
  assert(s_p.f4 == s.f4);
  assert(s_p.f5 == s.f5);

}

/****Helper functions for test_s3****/
struct s3 get_s3(long f0, unsigned long long f1,
		     unsigned char f2, int f3, unsigned int f4, unsigned char f5){

  struct s3 s;
  s.f0 = f0;
  s.f1 = f1;
  s.f2 = f2;
  s.f3 = f3;
  s.f4 = f4;
  s.f5 = f5;
  return s;
}


struct s3_bitfield get_s3_alt(long f0, unsigned long long f1,
		     unsigned char f2, int f3, unsigned int f4, unsigned char f5){

  struct s3_bitfield s;
  s.f0 = f0;
  s.f1 = f1;
  s.f2 = f2;
  s.f3 = f3;
  s.f4 = f4;
  s.f5 = f5;
  return s;
}


void s3p(char *s3_arr, struct s3 s){

  int len = sizeof(struct s3);
  memcpy(s3_arr, &s, len);
}


void s3p_alt(char *s3_arr, struct s3_bitfield s){

  int len = sizeof(struct s3_bitfield);
  memcpy(s3_arr, &s, len);
 }


void test_pack_s3(char *s3_bitfield, char *s3){

  struct s3 s;
  struct s3_bitfield s_b;
  memcpy(&s, s3, sizeof(struct s3));
  memcpy(&s_b, s3_bitfield, sizeof(struct s3_bitfield));
  assert(s_b.f0 == s.f0);
  assert(s_b.f1 == s.f1);
  assert(s_b.f2 == s.f2);
  assert(s_b.f3 == s.f3);
  assert(s_b.f4 == s.f4);
  assert(s_b.f5 == s.f5);

}

/*Error handling*/
void unix_error(char *msg) /* unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/* Wrapper for dynamic storage */
void *Malloc(size_t size) 
{
    void *p;

    if ((p  = malloc(size)) == NULL)
	unix_error("Malloc error");
    return p;
}
