#include <stdio.h>
#include "htab.h"

#define BUCKET_COUNT 100
#define WORD_LENGHT 255

int loadWords(char buffer[], int bufferSize) {
    int c;
    int index = 0;
    while ((c = getchar()) != ' ' && c!= EOF && c!='\n') {
        if (index < bufferSize - 1) { // -1 to account for null terminator
            buffer[index++] = (char)c;
        }
    }
    buffer[index] = '\0';

    if (feof(stdin)) {
        return 0;
    }

    return 1;
}

void printPair(htab_pair_t *pair){
    printf("%s\t%d\n",pair->key,pair->value);
}

int main() {
    htab_t *t=htab_init(BUCKET_COUNT);
    char word[WORD_LENGHT];
    while(loadWords(word,WORD_LENGHT)){
        htab_lookup_add(t,word);
    }
    htab_for_each(t,printPair);
    htab_free(t);
    t=NULL;
    return 0;
}
