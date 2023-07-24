#ifndef HASH_H__
#define HASH_H__

#include <string>
#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Advice for approaching this assignment:
//
// Many of the unit tests depend on more than one function. For
// example, the [hash func] test requires init_table to work. Because
// of this I recommend you proceed in this order:
//
// 1. init node
// 2. init table
// 3. hash func
// 4. bucket func
// 5. set
//
// Once you're there, you can take on the rest: load, get, contains,
// remove, and (if you're feeling saucy) resize.
//
// resize has less credit compared to other ones, you can ignore it if you are happy with a grade above 90.

// hash_node represents the contents of an individual bucket in your
// hash table.
struct hash_node {
  // deleted indicates if the node was marked as removed from the hash
  // table. it should be initialized to false.
  bool deleted;

  // key is the key the user provides to associate with a value.
  string key;

  // hashcode is the hashcode computed by the hash table's hash_func
  // on the key. it is stored to avoid having to re-compute it.
  unsigned int hashcode;

  // value is the user value associated with the key.
  string value;
};

// you can define your custom types like this one
// this is a vector where each index has a pointer to a hash_node object
// htable is used in hash_table struct bellow, you can define a table dynamically for ex:
//
//     //dynamically create a has_table object first
//     shared_ptr<hash_table> myhashtable(new hash_table);
//     // then create the htable for the size you like (say mysize)
//     myhashtable->table = shared_ptr<htable>(new htable(mysize));
//
// you can also use resize() property of vector to resize your table later
//
//     myhashtable->table.resize(new_size);
typedef vector<shared_ptr<hash_node>> htable;

// hash_table is the structure that holds your hashed data and
// associated metadata and hash function references.
struct hash_table {
  // capacity current number of addressable buckets in table. kept up-to-date.
  unsigned int capacity;

  // number of actual (not deleted) entries. kept up-to-date.
  unsigned int size;

  // number of non-null buckets. (so all hash_nodes, deleted or
  // otherwise). kept up-to-date.
  unsigned int occupied;

  // table points to dynamic array of hash_node pointers (read comments for htable above). it should be
  // initialized to a dynamic array of pointers to hash_node
  // structs. those pointers shoudl all initially be NULL.
  shared_ptr<htable> table;

  // hash_func is the currently in-use hash function. it should be
  // initialized to the djb2 hash function.
  //
  // to assign this, simply do:
  //
  // mytable->hash_func = djb2; // any function with signature like djb2 works.
  //
  // to use this:
  //
  // unsigned int hashcode_of_foo = mytable->hash_func("foo");
  unsigned int (*hash_func)(string);

  // bucket_func is the currently in-use bucket indexing function. it
  // should be initialized to the modulo_bucket_func function. assign
  // and use similarly to hash_func.
  unsigned int (*bucket_func)(unsigned int hashcode, unsigned int capacity); 
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


struct node {
  string data;               // data: the value of this node
  shared_ptr<node> next;  // next: pointer to the next node in the list, or NULL if this is the last node.
};

// Linked List Invariant: following the 'next' links in a linked list
// node must eventually lead to a NULL reference signifying the end of
// the list. (E.g. no circular references are allowed.)
class LinkedList {
public:
  // constructor, initialize class variables and pointers here if need.
  // Initially set top pointer to a null shared_ptr of node
  LinkedList();

  //deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~LinkedList();

  // init_node creates a new node structure from heap memory. It points
  // to NULL and holds the provided integer. The function returns a
  // pointer to that new node.
  shared_ptr<node> InitNode(string data);

  // report creates a space-separated string representing the contents
  // of the list, in the same order they are found beginning from the
  // top of the list. return that string object.  For example, this
  // might return "" (the empty string) if the list is empty, or it
  // might return "1 7 3 " (note the space at the end).
  string Report();

  // append_data adds a node onto the end of the list pointed to by
  // top. the resulting list is one element longer, and the newly
  // appended node has the given data value. consider using the 'append'
  // function to help.
  void AppendData(string data);

  // append is the same as append_data, except we're adding a node, rather
  // than a value. 
  void Append(shared_ptr<node> new_node);

  // insert_data inserts a new node that contains the given data value,
  // such that the new node occupies the offset indicated. Any nodes
  // that were already in the list at that offset and beyond are shifted
  // down by one. For example if the list contains 23, 74, 93, and we
  // insert 42 at index 1, the resulting list should be 23, 42, 74, 93.
  //
  // If an offset is beyond the end of the list, this function should
  // have no effect.
  //
  // Inserting at the end of the list should have the same effect as
  // appending.
  void InsertData(int offset, string data);

  // insert is the same as insert_data, except we're inserting a node,
  // rather than a value.
  void Insert(int offset, shared_ptr<node> new_node);

  // remove removes the node indicated by the given offset and frees its
  // memory. For example if our list contains 23, 74, 93, and we remove
  // offset 1, the resulting list should then contain 23, 93.
  //
  // If an invalid offset is given (e.g. negative or beyond the end of
  // the list), this function has no effect.
  void Remove(int offset);

  // size returns the number of nodes in the linked list reachable by
  // head before (but not including) the terminating NULL link. E.g., an
  // empty list has size 0, a list with one item has size 1, etc.
  int Size();

  // contains returns true if the linked list pointed to by head
  // contains a node with the specified value, false otherwise.
  bool Contains(string data);

  // This function is implemented for you
  // Returns the top pointer
  shared_ptr<node> GetTop();

  // This function is implemented for you
  // sets a given pointer as the top pointer
  void SetTop(shared_ptr<node> top_ptr);

  // you can add more public member variables and member functions here if you need

private:
  shared_ptr<node> top_ptr_;

  // you can add add more private member variables and member functions here if you need



};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


// DJB2 is a hash function that hashes strings and gives an unsigned
// integer hash code that could take on any value in the 32-bit
// unsigned integer range. It is implemented for you.
unsigned int DJB2(string key);

// ModuloBucketFunc simply returns hashcode % cap. It is provided
// here as a separate function because you *could* write your own hash
// function for putting keys into buckets. It is implemented for you.
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap);


class Hash {
public:
  Hash();

  // deconstructor, if you are using shared_pointers you don't need to keep track of
  // freeing memory and you can leave this blank
  ~Hash();

  // InitTable creates and initializes a hash_table structure and
  // returns a pointer to it. see the hash_table documentation for
  // details on the fields and their expected default values.
  shared_ptr<hash_table> InitTable(unsigned int cap);

  // InitNode creates and initializes a hash_node that will occupy a
  // hash table bucket. see the hash_node documentation for more info.
  shared_ptr<hash_node> InitNode(string key, unsigned int hashcode, string val);

  // SetKVP establishes a mapping between the given key and value pair
  // in the provided hash table. if the key (as identified by its hash
  // code) is already in the hash table, its value is potentially
  // updated. otherwise a new key/value pair is added to the hash table.
  //
  // on exit, the size and occupancy of the hash table is increased if a
  // new key/value pair was added.
  //
  // if there is no room in the hash table, return false. do not resize
  // the table.
  //
  // the return value should be true unless there was no room in the
  // hash table.
  bool SetKVP(shared_ptr<hash_table> tbl, string key, string value);

  // Load returns a load factor describing how 'full' the table
  // is. because we are using linear probing, which leaves 'deleted'
  // hash nodes sitting around, it is reasonable to use occupied divided
  // by capacity. you can alternately use size divided by capacity,
  // which is a more canonical definition of hashtable load. either will
  // work with the unit tests.
  float Load(shared_ptr<hash_table> tbl);

  // GetVal returns the value associated with the provded key in the
  // table, or the empty string "" if no such mapping exists (or if
  // there is a mapping but it is deleted).
  string GetVal(shared_ptr<hash_table> tbl, string key);

  // Contains returns true if the table has a non-deleted node whose
  // hashcode matches the given key's hashcode.
  bool Contains(shared_ptr<hash_table> tbl, string key);

  // Remove marks as 'deleted' any existing non-deleted hash_node with
  // the same hashcode as the provided key's hashcode. if it finds such
  // a hash node, it decrements the table's size (but not occupancy) and
  // returns true. it returns false otherwise.
  bool Remove(shared_ptr<hash_table> tbl, string key);

  // Resize creates a new underlying backing array (tbl->table) with the
  // provided new capacity, rehashes the existing backing array into the
  // new array. on exit, the hash table's fields and functions
  // accurately reflect the hash table's current state.
  void Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity);

  // PrintTable is a debugging function. It is implemented for you.
  // Feel free use or to change this for your debugging needs. It is not
  // unit tested.
  //
  // It might help you understand how the hash_table and hash_node
  // structs might be used in your code.
  void PrintTable(shared_ptr<hash_table> tbl);

  // you can add add more public member variables and member functions here if you need

private:
  // you can add add more private member variables and member functions here if you need
};

#endif  // HASH_H__





