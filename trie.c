/*An implementation of a trie in C to read a .txt file and find the words occurs most and least often */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int MAX_WORD_LEN = 45;

// Define trie_node_t
typedef struct trie_node {
	char key;
	struct trie_node * next;
	int counter;
}trie_node_t;

// Function to insert new nodes into trie if necessary
void trie_insert(char ch, trie_node_t * trie)
{
	if(trie->next == NULL)
	{
		trie_node_t new_node;
		new_node.key = ch;
		new_node.next = NULL;
		new_node.counter = 0;	
	} //if
} //trie_insert

int main()
{
	// Check time
	time_t start_time = time(NULL); 
	
	// File initialization
	FILE * input_fp;
	FILE * output_fp;
	input_fp = fopen("text_file.txt", "r");

	output_fp = fopen("results.txt", "w");
	
	char * word = malloc(MAX_WORD_LEN);
	size_t word_len;
	int file_read;
	
	// Declare trie and initialize trie root
	trie_node_t * my_trie;
	trie_node_t * my_trie_head = my_trie;
	my_trie->key = '\0';
	my_trie->next = NULL;
	my_trie->counter = 0;
	
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
		for (word_index=0;word_index<word_len;word_index++)
		{
			trie_insert(word[word_index], my_trie);
			my_trie = my_trie->next;
		} //for
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
	
	time_t end_time = time(NULL);
	
	time_t time_taken = end_time - start_time;
	
	fprintf(output_fp, "Least common word %s occurs %d times.\n", least_common_word, lowest_word_count);
	fprintf(output_fp, "Most common word %s occurs %d times.\n", most_common_word, highest_word_count);
	fprintf(output_fp, "Time taken in seconds: %ld", time_taken);
	
	
	free(word);
	free(most_common_word);
	free(least_common_word);
	fclose(input_fp);
	fclose(output_fp);

	return 0;
} //main

/*
References:
http://www.cs.grinnell.edu/~walker/courses/161.sp14/modules/getting-started/quarts-annotated.shtml
https://www.cs.bu.edu/teaching/c/file-io/intro/
http://cs.smith.edu/~thiebaut/classes/C_Tutor/node126.html
http://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
http://www.tutorialspoint.com/cprogramming/c_file_io.htm
http://www.gnu.org/software/libc/manual/html_node/Time-Functions-Example.html
*/
