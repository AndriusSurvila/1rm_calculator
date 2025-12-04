#ifndef HTML_TEMPLATER_H
#define HTML_TEMPLATER_H

typedef struct rm_data
{
    char *name;
    int weight;
    int reps;
    float rm;
} rm_data;

int copy_template_to_html(const char *template_filename, const char *output_filename);
int write_rm_to_html(const char *template_filename, const char *output_filename, rm_data *replacements);

#endif // HTML_TEMPLATER_H
