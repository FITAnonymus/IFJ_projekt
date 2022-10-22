/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

///#define CHAR_SIZE_IN_BYTES 8 ///constant used for allocating new space to buffer todo remove

/**
 * @struct Structure for storing unknown amount of characters.
 * Used in scanner for processing strings and numbers.
 *
 */
 typedef struct {
     char *buf;
     unsigned long lenght;
     unsigned long size;
 }Buffer;

 /**
  * Initialize empty buffer.
  *
  * @param buf Pointer to newly initialized buffer
  * @return 0 if the operation was successful, ERR_INTERNAL in case of failed allocation
  */
 int init_buffer(Buffer *buf);

 /**
  * Adding a char to buffer
  *
  * @param c Char for adding to buffer
  * @param buf Buffer destination
  * @return 0 if the operation was successful, ERR_INTERNAL in case of failed allocation
  */
 int add_to_buffer(char c, Buffer *buf);

 /**
  * Comparing buffer and constant string
  *
  * @param str Constant string to compare
  * @param buf Buffer to compare
  * @return  0 if the two strings are equal, less than 0 if str1 compares less than str2,
  * and greater than 0 if str1 compares greater than str2 (the same as strcmp()), ERR_INTERNAL in case of failed allocation
  */
 int cmp_string_buffer(char str[], Buffer *buf);

 /**
  * Copying buffer
  *
  * @param src Source buffer
  * @param dst Destination buffer
  * @return 0 if the operation was successful, 1 in case of error
  */
 int copy_buffer(Buffer *src, Buffer *dst);

/**
 * Free allocated memory for buffer and destroys its structure
 *
 * @param buf Pointer to buffer for deallocation
 *
 */
void free_buffer(Buffer *buf);

 ///maybe other functions needed //todo remove
 // buffer clear
 // buffer add string