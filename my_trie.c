/*An implementation of a trie in C to read a .txt file and find the words occurs most and least often */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int MAX_WORD_LEN = 45;

// Define node_t
typedef struct node{
  char key;
  struct node * child[26];
  int counter;
}node_t;


/* Function to return new node_t with key ch and pointer array initialized to
   NULL */
node_t* make_node(char ch) {
  node_t* new_node = (node_t*) malloc(sizeof(node_t));
  new_node->key = ch;
  int i;
  for(i=0;i<26;i++)
    {
      new_node->child[i] = NULL;
    }
  return new_node;
} //make_node

/* Function to insert new words into trie if necessary 
   Returns number of instances of word so far*/
int insert(char* word, node_t* trie)
{
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
  return trie->counter;
} //insert

/* Function to delete words from the trie */
void delete(char* word, node_t* trie)
{
  int index = 0;
  int word_len = strlen(word);
  char current;
  if(trie->child[current] == NULL)
    {
      free(trie);
    }
  else
    {
      delete((word+sizeof(char)), trie->child[current]);
    }
} //delete

/* Function to search for word in trie
   Returns 1 if found, 0 if not found */
int search(char * word, node_t * trie)
{
  int index;
  int word_len = strlen(word);
  for(index=0;index<word_len;index++) {
      if(trie->child[word[index]-'a'] == NULL) {
          return 0;
        }
      trie = trie->child[word[index]-'a'];
  }
  return 1;
} //search

void run_insert_test(node_t* trie, FILE* output)
{
  /*Test time taken to insert*/
  struct timeval s_insert;
  struct timeval e_insert;
  gettimeofday(&s_insert, NULL);
  insert("theeeeeeeee", trie);
  gettimeofday(&e_insert, NULL);
  suseconds_t insert_micro_taken = e_insert.tv_usec - s_insert.tv_usec;
  suseconds_t insert_milli_taken = ((e_insert.tv_sec - s_insert.tv_sec)*1000) +
    ((e_insert.tv_usec - s_insert.tv_usec)/1000);
  fprintf(output, "Time taken to insert in milliseconds: %lld\n",
          insert_milli_taken);
  fprintf(output, "Time taken to insert in microseconds: %lld\n",
          insert_micro_taken);
}

void run_delete_test(char* word, node_t* trie, FILE* output)
{
  /*Test time taken to delete*/
  struct timeval s_del;
  struct timeval e_del;
  gettimeofday(&s_del, NULL);
  delete("the", trie);
  gettimeofday(&e_del, NULL);
  suseconds_t del_micro_taken = e_del.tv_usec - s_del.tv_usec;
  suseconds_t del_milli_taken = ((e_del.tv_sec - s_del.tv_sec)*1000) +
    ((e_del.tv_usec - s_del.tv_usec)/1000);
  fprintf(output, "Time taken to delete in milliseconds: %lld\n",
          del_milli_taken);
  fprintf(output, "Time taken to delete in microseconds: %lld\n",
          del_micro_taken);
  
}



int main(int argc, char** argv)
{
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);

  // File initialization
  FILE* input_fp;
  FILE* output_fp;
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
  char* most_common_word = malloc(MAX_WORD_LEN);
  int lowest_word_count = 0; 
  char* least_common_word = malloc(MAX_WORD_LEN);
  int cur_word_count;

  // Read words until the end of file 
  while(file_read = fscanf(input_fp, "%s", word) != EOF)
    {
    word_len = strlen(word);
    // Insert each word into the trie
    cur_word_count = insert(word, my_trie);
      
    // Check if word is most or least common
    if(cur_word_count > highest_word_count)
      {
      highest_word_count = cur_word_count;
      strcpy(most_common_word, word);
    }
    else if(cur_word_count <= lowest_word_count || lowest_word_count == 0)
      {
      lowest_word_count = cur_word_count;
      strcpy(least_common_word, word);
      }
    my_trie = my_trie_head;
    }

  gettimeofday(&end, NULL);
  suseconds_t millisecs_taken = ((end.tv_sec - start.tv_sec)*1000) +
    ((end.tv_usec - start.tv_usec)/1000);

  fprintf(output_fp, "Least common word %s occurs %d times.\n",
          least_common_word, lowest_word_count);
  fprintf(output_fp, "Most common word %s occurs %d times.\n",
          most_common_word, highest_word_count);
  fprintf(output_fp, "Time taken to build trie in milliseconds: %lld\n",
          millisecs_taken);

  /* words2.txt testing*/
  //run_insert_test(my_trie, output_fp);
  //run_delete_test("the", my_trie, output_fp);
  /*Test time taken to search for likely*/
  struct timeval s;
  struct timeval e;
  // search likely
  gettimeofday(&s, NULL);
  search("likely", my_trie);
  gettimeofday(&e, NULL);
  suseconds_t search_milli = ((e.tv_sec - s.tv_sec)*1000) +
    ((e.tv_usec - s.tv_usec)/1000);
  suseconds_t search_micro = e.tv_usec - s.tv_usec;
  fprintf(output_fp, "Time taken to search for likely in milliseconds: %lld\n",
          search_milli);
  fprintf(output_fp, "Time taken to search for likely in microseconds: %lld\n",
          search_micro);

  // insert hyphenation
  gettimeofday(&s, NULL);
  insert("hyphenation", my_trie);
  gettimeofday(&e, NULL);
  suseconds_t insert_milli = ((e.tv_sec - s.tv_sec)*1000) +
    ((e.tv_usec - s.tv_usec)/1000);
  suseconds_t insert_micro = e.tv_usec - s.tv_usec;
  fprintf(output_fp, "Time taken to insert hyphenation in milliseconds: %lld\n",
          search_milli);
  fprintf(output_fp, "Time taken to insert hyphenation in microseconds: %lld\n",
          search_micro);

  // delete brisk
  gettimeofday(&s, NULL);
  delete("brisk", my_trie);
  gettimeofday(&e, NULL);
  suseconds_t delete_milli = ((e.tv_sec - s.tv_sec)*1000) +
    ((e.tv_usec - s.tv_usec)/1000);
  suseconds_t delete_micro = e.tv_usec - s.tv_usec;
  fprintf(output_fp, "Time taken to delete brisk in milliseconds: %lld\n",
          delete_milli);
  fprintf(output_fp, "Time taken to delete brisk in microseconds: %lld\n",
          delete_micro);

  /*End of testing*/
  
  free(word);
  free(most_common_word);
  free(least_common_word);
  fclose(input_fp);
  fclose(output_fp);
  
  return 0;
} //main


/*
  References:
  http://www.cs.loyola.edu/~jglenn/702/S2008/Projects/P3/time.html
  http://www.geeksforgeeks.org/trie-insert-and-search/
  http://www.cs.grinnell.edu/~walker/courses/161.sp14/modules/getting-started/quarts-annotated.shtml
  https://www.cs.bu.edu/teaching/c/file-io/intro/
  http://cs.smith.edu/~thiebaut/classes/C_Tutor/node126.html
  http://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
  http://www.tutorialspoint.com/cprogramming/c_file_io.htm
  http://www.gnu.org/software/libc/manual/html_node/Time-Functions-Example.html
*/
