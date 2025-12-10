#include "html_templater.h"
#include <string.h>
#include <stdio.h>

#define MAX_KEY_LENGTH 255

void replace_in_file(FILE *file, const char *key, list_node *replacements)
{
    while (replacements != NULL)
    {
        if (strcmp(replacements->key, key) == 0)
        {
            fputs(replacements->value, file);
            return;
        }
        replacements = replacements->next;
    }
    fputs(key, file); // not found
}

int copy_template_to_html(const char *template_filename, FILE *output_file)
{
    FILE *template_fp = fopen(template_filename, "r");
    if (template_fp == NULL)
    {
        return -1;
    }
    char read_char;
    while ((read_char = getc(template_fp)) != EOF)
    {
        fputc(read_char, output_file);
    }
    fclose(template_fp);
    return 0;
}

int write_to_html(const char *template_filename, FILE *output_file, list_node *replacements)
{
    FILE *template_fp = fopen(template_filename, "r");
    if (template_fp == NULL)
    {
        return -1;
    }
    
    char read_char;
    while ((read_char = getc(template_fp)) != EOF)
    {
        if (read_char == '{')
        {
            char buffer[MAX_KEY_LENGTH + 1];
            int i;
            int found_closing_brace = 0;
            
            for (i = 0; i < MAX_KEY_LENGTH; ++i)
            {
                read_char = getc(template_fp);
                
                if (read_char == EOF)
                {
                    // Unexpected EOF - output { and what we read
                    fputc('{', output_file);
                    buffer[i] = '\0';
                    fputs(buffer, output_file);
                    fclose(template_fp);
                    return 0;
                }
                
                if (read_char == '}')
                {
                    buffer[i] = '\0';
                    found_closing_brace = 1;
                    break;
                }
                
                buffer[i] = read_char;
            }
            
            if (!found_closing_brace)
            {
                // Key too long or no closing brace - output as literal text
                fputc('{', output_file);
                buffer[MAX_KEY_LENGTH] = '\0';
                fputs(buffer, output_file);
                
                // Continue reading until we find } or EOF
                while ((read_char = getc(template_fp)) != EOF && read_char != '}')
                {
                    fputc(read_char, output_file);
                }
                if (read_char == '}')
                {
                    fputc('}', output_file);
                }
            }
            else
            {
                replace_in_file(output_file, buffer, replacements);
            }
        }
        else
        {
            fputc(read_char, output_file);
        }
    }
    fclose(template_fp);
    return 0;
}