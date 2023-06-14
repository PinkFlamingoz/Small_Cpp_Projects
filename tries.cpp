#include <iostream>

using namespace std;
// - Tries
//  - Insertion is complex - a lot of dynamic memory allocation, but gets easier as you go
//  - Deletion is easy - just free a node
//  - Lookup is fast - not quite as fast as an array, but almost
//  - Already sorted - sorts as you build in almost all situations
//  - Rapidly becomes huge, even with very little data present, not great if space is at a premium
//
// Tries combine structures and pointers together to store data in an interesting way.
// - The data to be searched for in the trie is now a roadmap.
// - If you can follow the map from beginning to end, the data exists in the trie.
// - If you can't, it doesn't.
// - Unlike with a hash table, there are no collisions, and no two pieces of data (unless they are identical) have the same path.