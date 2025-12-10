#ifndef HTML_TEMPLATER_H
#define HTML_TEMPLATER_H

#include <stdio.h>
typedef struct list_node {
    char *key;
    char *value;
    struct list_node *next;
}list_node; 


int copy_template_to_html(const char *template_filename, FILE *output_file);
int write_to_html(const char *template_filename, FILE* output_file, list_node *replacements);

#endif // HTML_TEMPLATER_H
