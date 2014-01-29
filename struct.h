struct s1 {
  unsigned char f0;
  long f1;
  unsigned char f2;
  unsigned int f3;
  int f4;
  long long f5;
};

struct s2 {
  unsigned long long f0;
  long f1;
  int f2;
  unsigned long f3;
  unsigned short f4;
  unsigned int f5;
};

#pragma pack (1)
struct s2_packed {
  unsigned long long f0;
  long f1;
  int f2;
  unsigned long f3;
  unsigned short f4;
  unsigned int f5;
};
#pragma pack ()

struct s3 {
  long f0;
  unsigned long long f1;
  unsigned char f2;
  int f3;
  unsigned int f4;
  unsigned char f5;
};

struct s3_bitfield {
  long f0 : 12;
  unsigned long long f1 : 29;
  unsigned char f2 : 6;
  int f3 : 1;
  unsigned int f4 : 20;
  unsigned char f5 : 7;
};

