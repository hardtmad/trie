/*An implementation of a trie in C to read a .txt file and find the words occurs most and least often */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int MAX_WORD_LEN = 45;

// Define node_t
typedef struct node{
  char key;
  struct node * child[26];
  int counter;
}node_t;

// Return new node_t with key ch and pointer array initialized to NULL
node_t* make_node(char ch) {
  node_t *new_node = NULL;
  new_node = (node_t*) malloc(sizeof(node_t));
  new_node->key = ch;
  int i;
  for(i=0;i<26;i++)
    {
      new_node->child[i] = NULL;
    }
  return new_node;
}

// Function to insert new words into trie if necessary
void insert(char * word, node_t * trie) {
  // Follow the word down the trie until there is a node missing
  int index = 0;
  int word_len = strlen(word);
  char current;
  for(index=0; index<word_len; index++) {
    current = word[index];
      if(trie->child[current-'a'] == NULL) {
        trie->child[current-'a'] = make_node(current);
        }//if there's not a child node for current ch, make one
      trie = trie->child[current-'a'];
    }//for each char in word
  
  trie->counter++; //increment counter for this word
} //insert


// Function to search for word in trie
// Returns 1 if found, 0 if not found
int search(char * word, node_t * trie) {
  int index;
  int word_len = strlen(word);
  for(index=0;index<word_len;index++) {
      if(trie->child[word[index]-'a'] == NULL) {
          return 0;
        }
      trie = trie->child[word[index]-'a'];
    }
  return 1;
}

int main(int argc, char ** argv) {
  time_t start_time = time(NULL);

  // File initialization
  FILE * input_fp;
  FILE * output_fp;
  input_fp = fopen(argv[1], "r");

  output_fp = fopen("results.txt", "w");

  char* word = malloc(MAX_WORD_LEN);
  size_t word_len;
  int file_read;

  // Declare my_trie and initialize dummy trie root
  node_t* my_trie = make_node('\0');
  node_t* my_trie_head = my_trie;

  // Declare counters for most and least common word
  int highest_word_count = 0;
  char * most_common_word = malloc(MAX_WORD_LEN);
  int lowest_word_count = 0; 
  char * least_common_word = malloc(MAX_WORD_LEN);

  // Read words until the end of file 

  int word_count = 0;
  while(file_read = fscanf(input_fp, "%s", word) != EOF) {
      word_len = strlen(word);

      // Insert each word into the trie
      insert(word, my_trie);
      
      // Check if word is most or least common
      if(my_trie->counter > highest_word_count) {
          highest_word_count = my_trie->counter;
          most_common_word = word;
        }
      if(my_trie->counter < lowest_word_count || lowest_word_count ==0) {
          lowest_word_count = my_trie->counter;
          least_common_word = word;
        }
      
      my_trie = my_trie_head;
      word_count++;
    }
  
  time_t end_time = time(NULL);
  time_t time_taken = end_time - start_time;

  fprintf(output_fp, "Least common word %s occurs %d times.\n", least_common_word, lowest_word_count);
  fprintf(output_fp, "Most common word %s occurs %d times.\n", most_common_word, highest_word_count);
  
  fprintf(output_fp, "done %d\n", word_count);
  fprintf(output_fp, "s time: %lld\n", start_time);
  fprintf(output_fp, "e time: %lld\n", end_time);
  fprintf(output_fp, "time taken: %lld\n", time_taken);

  free(word);
  free(most_common_word);
  free(least_common_word);
  fclose(input_fp);
  fclose(output_fp);
  
  return 0;
} //main


/*
  References:
  http://www.geeksforgeeks.org/trie-insert-and-search/
  http://www.cs.grinnell.edu/~walker/courses/161.sp14/modules/getting-started/quarts-annotated.shtml
  https://www.cs.bu.edu/teaching/c/file-io/intro/
  http://cs.smith.edu/~thiebaut/classes/C_Tutor/node126.html
  http://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
  http://www.tutorialspoint.com/cprogramming/c_file_io.htm
  http://www.gnu.org/software/libc/manual/html_node/Time-Functions-Example.html
*/
