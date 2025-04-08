#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));

    // Open the hash file
    FILE *hashes = fopen(hashFilename, "r");

    //Check for errors
    if (!hashes) {
        printf("Error opening file");
        free(hash);
        exit(1);
    }

    char line[255];
    // Loop through the hash file, one line at a time.
    while (fgets(line, 255, hashes) != NULL) {
        line[strcspn(line, "\n")] = 0;
        //printf("Line: %s\n", line);
        //printf("Hash: %s\n", hash);
        if (strcmp(line, hash) == 0) {
            //printf("Found it\n");
            fclose(hashes);
            free(hash);
            return strdup(line);
        }
    }

    // Before returning, do any needed cleanup:
    //   Close files?
    fclose(hashes);
    //   Free memory?
    free(hash);

    // If there is a match, you'll return the hash.
    // If not, return NULL.
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // These two lines exist for testing. When you have
    // tryWord working, it should display the hash for "hello",
    // which is 5d41402abc4b2a76b9719d911017c592.
    // Then you can remove these two lines and complete the rest
    // of the main function below.
    char *found = tryWord("hello", "hashes00.txt");
    printf("%s %s\n", found, "hello");


    // Open the dictionary file for reading.
    FILE *dict = fopen(argv[2], "r");

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    int count = 0;
    char line[255];
    char *result;
    while (fgets(line, 255, dict) != NULL) {
        line[strcspn(line, "\n")] = 0;
        result = tryWord(line, argv[1]);
        if (result != NULL) {
            count++;
            printf("%s %s\n", result, line);
        }
    }
    
    // Close the dictionary file.
    fclose(dict);

    // Display the number of hashes that were cracked.
    printf("Found %d many matches\n", count);
    
    // Free up any malloc'd memory?
    free(result);
}