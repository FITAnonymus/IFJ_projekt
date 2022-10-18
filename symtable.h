//length of table
unsigned const int LENGTH = 1024;

//Definition of Item of table 
typedef struct item {
    char* key;
    char* value;
    //TODO add type
    struct item *next;
} Item;

// Pointer to Item
typedef Item *ItemPtr;

// Definition of the hash table
typedef struct hash_table {
    Item** items;
    int size;
}Hash_table;

typedef Hash_table *Hash_table_ptr;