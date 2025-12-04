#include "html_templater.h"
#include <string.h>
#include <stdio.h>

int copy_template_to_html(const char *template_filename, const char *output_filename)
{
	FILE *template_fp = fopen(template_filename, "r");
	if (template_fp == NULL)
	{
		return -1;
	}
	FILE *output_fp = fopen(output_filename, "a");
	if (output_fp == NULL)
	{
		fclose(template_fp);
		return -1;
	}
	char read_char;
	while ((read_char = getc(template_fp)) != EOF)
	{
		fputc(read_char, output_fp);
	}
	fclose(template_fp);
	fclose(output_fp);
	return 0;
}

int write_rm_to_html(const char *template_filename, const char *output_filename, rm_data *replacements)
{
	FILE *template_fp = fopen(template_filename, "r");
	if (template_fp == NULL)
	{
		return -1;
	}
	FILE *output_fp = fopen(output_filename, "a");
	if (output_fp == NULL)
	{
		fclose(template_fp);
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
			if (strcmp(buffer, "name") == 0)
			{
				fprintf(output_fp, "%s", replacements->name);
			}
			else if (strcmp(buffer, "weight") == 0)
			{
				fprintf(output_fp, "%d", replacements->weight);
			}
			else if (strcmp(buffer, "reps") == 0)
			{
				fprintf(output_fp, "%d", replacements->reps);
			}
			else if (strcmp(buffer, "rm") == 0)
			{
				fprintf(output_fp, "%.2f", replacements->rm);
			}
		}
		else
		{
			fputc(read_char, output_fp);
		}
	}
	fclose(template_fp);
	fclose(output_fp);
	return 0;
}
