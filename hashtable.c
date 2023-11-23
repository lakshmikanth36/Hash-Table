
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the size of the hash table
#define TABLE_SIZE 100

// Define the structure for key-value pairs
struct KeyValue {
    char* key;
    char* value;
    struct KeyValue* next;
};

// Define the hash table structure
struct HashTable {
    struct KeyValue* table[TABLE_SIZE];
};

// Hash function
unsigned int hash(char* key) {
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = 31 * hash + key[i];
    }
    return hash % TABLE_SIZE;
}

// Initialize the hash table
void initializeHashTable(struct HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// Insert a key-value pair into the hash table
void insert(struct HashTable* ht, char* key, char* value) {
    unsigned int index = hash(key);

    // Create a new key-value pair
    struct KeyValue* newPair = (struct KeyValue*)malloc(sizeof(struct KeyValue));
    newPair->key = strdup(key);
    newPair->value = strdup(value);
    newPair->next = NULL;

    // If the bucket is empty, insert the pair
    if (ht->table[index] == NULL) {
        ht->table[index] = newPair;
    } else {
        // If the bucket is not empty, handle collisions by chaining
        struct KeyValue* current = ht->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPair;
    }
}

// Look up a value by key
char* lookup(struct HashTable* ht, char* key) {
    unsigned int index = hash(key);
    struct KeyValue* current = ht->table[index];

    // Traverse the chain in the bucket to find the key
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value; // Key found
        }
        current = current->next;
    }

    return NULL; // Key not found
}

// Demonstrate and explain the points
int main() {
    // 1. O(1) runtime for value lookup
    // The lookup function has constant time complexity since it directly computes the index using the hash function.

    // 2. Suitability of the chosen hash function
    // The chosen hash function is a basic one, which sums up the ASCII values of characters in the key and takes the modulo of the table size.
    // While simple, it may not be suitable for all cases (e.g., not resistant to certain types of collisions). 
    // In production, a more sophisticated hash function would be needed.

    // 3. Resizing of the hash table when adding/removing key-value pairs
    // This implementation does not handle resizing for simplicity. In a real-world scenario, you would need to implement resizing
    // to maintain a good load factor and avoid performance degradation. Resizing involves creating a new larger table,
    // rehashing all existing elements into the new table, and updating the hash table reference.

    struct HashTable ht;
    initializeHashTable(&ht);

    // Adding key-value pairs
    insert(&ht, "name", "John");
    insert(&ht, "age", "25");
    insert(&ht, "city", "New York");

    // Looking up values
    printf("Name: %s\n", lookup(&ht, "name"));
    printf("Age: %s\n", lookup(&ht, "age"));
    printf("City: %s\n", lookup(&ht, "city"));
    printf("Invalid Key: %s\n", lookup(&ht, "invalid_key"));

    return 0;
}
