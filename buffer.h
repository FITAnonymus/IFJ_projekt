/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

/**
 * @struct Structure for storing unknown amount of characters.
 * Used in scanner for processing strings and numbers.
 *
 */
 typedef struct {
     char *buf;
     unsigned long lenght;// same size as unsigned int //TODO poradi fci
     unsigned long size;
 }Buffer;

 /**
  * Initialize empty buffer.
  *
  * @param buf Pointer to newly initialized buffer
  * @return 0 if the operation was successful, 1 in case of error
  */
 int init_buffer(Buffer *buf);

 /**
  * Free allocated memory for buffer and destroys its structure
  *
  * @param buf Pointer to buffer for deallocation
  * @return 0 if the operation was successful, 1 in case of error
  */
 int free_buffer(Buffer *buf);

 /**
  * Adding a char to buffer
  *
  * @param c Char for adding to buffer
  * @param buf Buffer destination
  * @return 0 if the operation was successful, 1 in case of error
  */
 int add_to_buffer(char c, Buffer *buf);

 /**
  * Comparing buffer and constant string
  *
  * @param str Constant string to compare
  * @param buf Buffer to compare
  * @return 0 in case of match or (int) number of unmatching characters
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

 ///maybe other functions needed //todo
 // buffer clear
 // buffer add string