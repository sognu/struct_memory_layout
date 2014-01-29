/*
 * return a struct containing the same values as the argument struct
 * except that each field has its byte order reversed
 *
 * RESTRICTION: this function must not use arrays or pointers at all;
 * accomplish the byte swapping using shift operators
 */
struct s1 endian_swap_s1_shift (struct s1);

/*
 * return a struct containing the same values as the argument struct
 * except that each field has its byte order reversed
 *
 * RESTRICTION: this function must not use shift operators;
 * accomplish the byte swapping using pointers and/or arrays
 */
struct s1 endian_swap_s1_ptr (struct s1);

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
void pack_s2 (char *, char *);

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
void unpack_S2 (char *, char *);

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
int pack_s3 (char *, char *);

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
void unpack_s3 (char *, char *);
