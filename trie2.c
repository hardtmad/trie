#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int MAX_WORD_LEN = 45;

// Define trie_node_t
typedef struct trie_node {
  char key;
  struct trie_node * next[26];
  int counter;
}trie_node_t;

// Function to insert new nodes into trie if necessary
void trie_insert(char ch, trie_node_t * trie)
{
  if(trie->next[ch-'a'] == NULL)
    {
      trie_node_t* new_node = malloc(sizeof(trie_node_t));
      new_node->key = ch;
      int i;
      for(i=0; i<26; i++)
        {
          new_node->next[i] = NULL;
        } //for
      new_node->counter = 0;	
    } //if
} //trie_insert

int main(int argc, char ** argv)
{
  printf("here1\n");
  time_t start_time = time(NULL);

  // File initialization
  FILE * input_fp;
  FILE * output_fp;
  printf("here");
  input_fp = fopen(argv[1], "r");

  output_fp = fopen("results.txt", "w");

  char * word = malloc(MAX_WORD_LEN);
  size_t word_len;
  int file_read;

  // Declare trie and initialize trie root
  trie_node_t * my_trie = calloc(1, sizeof(trie_node_t));
  trie_node_t * my_trie_head = my_trie;

  int highest_word_count = 0;
  char * most_common_word = malloc(MAX_WORD_LEN);
  int lowest_word_count = 0; 
  char * least_common_word = malloc(MAX_WORD_LEN);

  // Read words until the end of file 
	
  while(file_read = fscanf(input_fp, "%s", word) != EOF)
    {
      word_len = strlen(word);

      // For each word traverse trie and add nodes where necessary
      int word_index;
      for (word_index=0;word_index<word_len-1;word_index++)
        {
          trie_insert(word[word_index], my_trie);
          my_trie = my_trie->next[word[word_index+1]];
        } //for

      trie_insert(word[word_index], my_trie);
      my_trie->counter++;
		
      if(my_trie->counter > highest_word_count)
        {
          highest_word_count = my_trie->counter;
          most_common_word = word;
        }
      if(my_trie->counter < lowest_word_count || lowest_word_count ==0)
        {
          lowest_word_count = my_trie->counter;
          least_common_word = word;
        }
      my_trie = my_trie_head;
    }
  return 0;
} //main


