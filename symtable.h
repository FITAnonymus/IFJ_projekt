//length of table inspired by https://planetmath.org/goodhashtableprimes
unsigned const int LENGTH = 1543;

//Definition of Item of table 
typedef struct item {
    char* key;
    char* value;
    char* type;
    struct item *next;
} Item;

// Pointer to Item
typedef Item *ItemPtr;

// Definition of the hash table
typedef struct hash_table {
    Item** items;
    int size;
}Hash_table;

// Pointer to Hash_table
typedef Hash_table *Hash_table_ptr;
/*
//Definition of FunctionItem of table 
typedef struct fitem {
    Item params;
    Item ret_val;
    int num_of_items;
    struct fitem *next;
} fItem;

// Pointer to fItem
typedef fItem *fItemPtr;

// Definition of the hash table for functions
typedef struct fhash_table {
    fItem** fitems;
    int size;
}fHash_table;

// Pointer to fHash_table
typedef fHash_table *fHash_table_ptr;*/