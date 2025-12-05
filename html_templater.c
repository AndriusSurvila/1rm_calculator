#include "html_templater.h"
#include <string.h>
#include <stdio.h>

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

int write_rm_to_html(const char *template_filename, FILE *output_file, list_node *replacements)
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
			char buffer[20];
			for (int i = 0; i < 19; ++i)
			{
				read_char = getc(template_fp);
				if (read_char == '}')
				{
					buffer[i] = 0;
					break;
				}
				buffer[i] = read_char;
			}
			replace_in_file(output_file, buffer, replacements);	

		}
		else
		{
			fputc(read_char, output_file);
		}
	}
	fclose(template_fp);
	return 0;
}
