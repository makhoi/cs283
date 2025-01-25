#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SZ 100

// Function prototypes
void usage(char *);
void print_buff(char *, int);
int setup_buff(char *, char *, int);
int count_words(char *, int, int);
void reverse_string(char *, int);
void print_words(char *, int);

int setup_buff(char *buff, char *user_str, int len) {
    char *src = user_str;
    char *dest = buff;
    int count = 0;
    int space_flag = 1;  // To skip leading spaces

    // Process input and remove extra spaces
    while (*src != '\0' && count < len) {
        if (isspace(*src)) {
            if (!space_flag) {
                *dest++ = ' ';
                count++;
                space_flag = 1;
            }
        } else {
            *dest++ = *src;
            count++;
            space_flag = 0;
        }
        src++;
    }

    while (isspace(*src)) {
    src++;  // Skip leading spaces
}

    // Remove trailing spaces
    if (count > 0 && *(dest - 1) == ' ') {
        dest--;
        count--;
    }

    // Fill the remaining buffer space with dots
    while (count < len - 1) {  
    if (*dest == '\0') {
        *dest++ = '.';
    }
    count++;
}


    *dest = '\0';  // Null-terminate the string

    return count;

    printf("Original Input: [%s]\n", user_str);
    printf("Processed Buffer (after cleanup): [%s]\n", buff);
}


int count_words(char *buff, int len, int str_len) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; i < str_len; i++) {
        if (buff[i] == ' ' || buff[i] == '.') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
            printf("Word detected at index %d\n", i);
        }
    }
    printf("Final word count: %d\n", count);
    return count;
}


void reverse_string(char *buff, int str_len) {
    char *start = buff;
    char *end = buff + str_len - 1;
    char temp;

    // Reverse only the actual user string, ignore dots
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    printf("Buffer:  [");  // Ensure two spaces after 'Buffer:'
    for (int i = 0; i < BUFFER_SZ; i++) {
        putchar(buff[i]);
    }
    printf("]\n");
}

void print_words(char *buff, int str_len) {
    int index = 1;
    char *start = buff;
    int word_count = 0;

    printf("Word Print\n----------\n");

    while (*start && (start - buff) < str_len) {
        // Skip leading spaces
        while (*start == ' ' && (start - buff) < str_len) start++;

        if (*start && *start != '.') {
            printf("%d. ", index++);
            char *word_start = start;

            while (*start != ' ' && *start != '.' && (start - buff) < str_len) {
                putchar(*start++);
            }

            printf("(%ld)\n", start - word_start);
            word_count++;
        }
        start++;
    }

    printf("\nNumber of words returned: %d\n", word_count);
    printf("Buffer:  [");
    for (int i = 0; i < BUFFER_SZ; i++) {
        putchar(buff[i]);
    }
    printf("]\n");
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
        exit(1);
    }

    if (argv[1][0] != '-' || (argv[1][1] != 'h' && argv[1][1] != 'c' && argv[1][1] != 'r' && argv[1][1] != 'w' && argv[1][1] != 'x')) {
        usage(argv[0]);
        exit(1);
    }

    if (argv[1][1] == 'h') {
        usage(argv[0]);
        exit(0);
    }

    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }

    char *buff = (char *)malloc(BUFFER_SZ);
    if (!buff) {
        printf("Memory allocation failed\n");
        exit(99);
    }

    int user_str_len = setup_buff(buff, argv[2], BUFFER_SZ);
    if (user_str_len < 0) {
        printf("Error setting up buffer, error = %d\n", user_str_len);
        free(buff);
        exit(2);
    }

    switch (argv[1][1]) {
        case 'c':
            printf("Word Count: %d\n", count_words(buff, BUFFER_SZ, user_str_len));
            printf("Buffer: [");
            for (int i = 0; i < BUFFER_SZ; i++) {
                putchar(buff[i]);
            }
            printf("]\n");
            break;
        case 'r':
            reverse_string(buff, user_str_len);
            break;
        case 'w':
            print_words(buff, user_str_len);
            break;
        case 'x':
            printf("Not Implemented!\n");
            free(buff);
            exit(3);
            break;
        default:
            usage(argv[0]);
            free(buff);
            exit(1);
    }

    print_buff(buff, BUFFER_SZ);
    free(buff);
    return 0;
}

void usage(char *exename) {
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

void print_buff(char *buff, int len) {
    printf("Buffer:  ");
    for (int i = 0; i < len; i++) {
        putchar(buff[i]);
    }
    putchar('\n');
}

