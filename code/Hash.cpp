#include "Hash.h"

// implemented for you - don't change this one
unsigned int DJB2(string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
  unsigned int b = hashcode % cap;
  return b;
}

// constructor, initialize class variables and pointers here if need.
Hash::Hash(){
  // your code here
}

//deconstructor,
Hash::~Hash(){
}

shared_ptr<hash_table> Hash::InitTable(unsigned int cap){
  shared_ptr<hash_table> ret(new hash_table);
  // your code here
  ret->capacity = cap;
  ret->size = 0;
  ret->occupied = 0;
  ret->table = shared_ptr<htable>(new htable(cap));
  ret->hash_func = DJB2;
  ret->bucket_func = ModuloBucketFunc;
  return ret;
}

shared_ptr<hash_node> Hash::InitNode(string key, unsigned int hashcode, string val){
  shared_ptr<hash_node> ret(new hash_node);
  // your code here
  ret->key = key;
  ret->hashcode = hashcode;
  ret->deleted = false;
  ret->value = val;

  return ret;
}

bool Hash::SetKVP(shared_ptr<hash_table> tbl, string key, string value) {
    // Calculate the hash code for the key using the hash function
    unsigned int hashcode = tbl->hash_func(key);

    // Get the index in the table using the bucket function
    unsigned int index = tbl->bucket_func(hashcode, tbl->capacity);

    // Search for the key in the table
    for (unsigned int i = 0; i < tbl->capacity; i++) {
      unsigned int curr_index = (index + i) % tbl->capacity;
      shared_ptr<hash_node> node = (*tbl->table)[curr_index];
      if (node == nullptr || (node->key == key && !node->deleted)) {
        // If the slot is empty or the node with the same key is found and not marked deleted
        // Set or update the value
        if (node == nullptr) {
          (*tbl->table)[curr_index] = InitNode(key, hashcode, value);
          tbl->size++;
          tbl->occupied++; // Increment the occupied count when adding a new node
        } else {
          node->value = value;
        }
        return true;
        }
    }

    // No available slot found
    return false;
}



float Hash::Load(shared_ptr<hash_table> tbl){
  // your code here
  float occupied = 0;
    for (unsigned int i = 0; i < tbl->capacity; i++) {
      shared_ptr<hash_node> node = (*tbl->table)[i];
      if (node != nullptr && !node->deleted) {
        occupied++;
      }
    }
    return occupied / tbl->capacity;
}


string Hash::GetVal(shared_ptr<hash_table> tbl, string key){
  // Calculate the hash code for the key using the hash function
  unsigned int hashcode = tbl->hash_func(key);

  // Get the index in the table using the bucket function
  unsigned int index = tbl->bucket_func(hashcode, tbl->capacity);

  // Search for the key in the table
  for (unsigned int i = 0; i < tbl->capacity; i++) {
    unsigned int curr_index = (index + i) % tbl->capacity;
      shared_ptr<hash_node> node = (*tbl->table)[curr_index];
      if (node != nullptr && node->key == key && !node->deleted) {
        // Found the node with the same key and it is not marked deleted
        return node->value;
      }
  } 
  return "";
}

bool Hash::Contains(shared_ptr<hash_table> tbl, string key){
  // your code here
  // Calculate the hash code for the key using the hash function
  unsigned int hashcode = tbl->hash_func(key);

  // Get the index in the table using the bucket function
  unsigned int index = tbl->bucket_func(hashcode, tbl->capacity);

  // Search for the key in the table
  for (unsigned int i = 0; i < tbl->capacity; i++) {
    unsigned int curr_index = (index + i) % tbl->capacity;
      shared_ptr<hash_node> node = (*tbl->table)[curr_index];
      if (node != nullptr && node->key == key && !node->deleted) {
        // Found the node with the same key and it is not marked deleted
        return true;
      }
  }
  return false;
}

bool Hash::Remove(shared_ptr<hash_table> tbl, string key) {
    // Calculate the hash code for the key using the hash function
    unsigned int hashcode = tbl->hash_func(key);

    // Get the index in the table using the bucket function
    unsigned int index = tbl->bucket_func(hashcode, tbl->capacity);

    // Search for the key in the table
    for (unsigned int i = 0; i < tbl->capacity; i++) {
      unsigned int curr_index = (index + i) % tbl->capacity;
      shared_ptr<hash_node> node = (*tbl->table)[curr_index];
      if (node != nullptr && node->key == key && !node->deleted) {
        // Found the node with the same key and it is not marked deleted
        node->deleted = true;
        tbl->size--;
        return true;
      } 
      else if (node != nullptr && node->deleted) {
          // Decrement the occupied counter only if a deleted node replaces a non-deleted node
          tbl->occupied--;
        }
    }

    // Key not found
    return false;
}




void Hash::Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity){
  // Create a new table with the new capacity
  shared_ptr<htable> new_table = shared_ptr<htable>(new htable(new_capacity));

  // Rehash the existing data into the new table
  for (unsigned int i = 0; i < tbl->capacity; i++) {
    shared_ptr<hash_node> node = (*tbl->table)[i];
    if (node != nullptr && !node->deleted) {
      unsigned int new_index = tbl->bucket_func(node->hashcode, new_capacity);
      for (unsigned int j = 0; j < new_capacity; j++) {
        unsigned int curr_index = (new_index + j) % new_capacity;
        if ((*new_table)[curr_index] == nullptr) {
          (*new_table)[curr_index] = node;
          break;
        }
      }
    }
  }

    // Update the table with the new capacity and new table
  tbl->capacity = new_capacity;
  tbl->table = new_table;

}

// implemented for you - feel free to change this one if you like
void Hash::PrintTable(shared_ptr<hash_table> tbl){
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << Load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (!tbl->table->at(i)) {
        cout << "<empty>" << endl;
      } else if (tbl->table->at(i)->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}



