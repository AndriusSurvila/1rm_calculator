#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html_templater.h"
#include "rm_calculator.h"

#define MAX_EXERCISES 20

list_node* create_exercise_nodes(Exercise *exercise, char *name_buf, char *weight_buf, char *reps_buf, char *rm_buf)
{
    list_node *node1 = (list_node*)malloc(sizeof(list_node));
    list_node *node2 = (list_node*)malloc(sizeof(list_node));
    list_node *node3 = (list_node*)malloc(sizeof(list_node));
    list_node *node4 = (list_node*)malloc(sizeof(list_node));
    
    if (!node1 || !node2 || !node3 || !node4) {
        return NULL;
    }
    
    strcpy(name_buf, exercise->name);
    double_to_string(exercise->weight, weight_buf, 0);
    int_to_string(exercise->reps, reps_buf);
    double_to_string(exercise->one_rm, rm_buf, 0);
    
    node1->key = "name";
    node1->value = name_buf;
    node1->next = node2;
    
    node2->key = "weight";
    node2->value = weight_buf;
    node2->next = node3;
    
    node3->key = "reps";
    node3->value = reps_buf;
    node3->next = node4;
    
    node4->key = "rm";
    node4->value = rm_buf;
    node4->next = NULL;
    
    return node1;
}

void free_nodes(list_node *head)
{
    while (head != NULL) {
        list_node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    Exercise exercises[MAX_EXERCISES];
    int count;
    
    count = read_exercises(exercises, MAX_EXERCISES);
    
    if (count <= 0) {
        printf("Error\n");
        return 1;
    }
    
    FILE *output_file = fopen("output.html", "w");
    if (output_file == NULL) {
        printf("Error: could not create output file\n");
        return 1;
    }
    
    if (copy_template_to_html("start.html", output_file) != 0) {
        printf("Error: could not read start.html template\n");
        fclose(output_file);
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        char name_buf[50];
        char weight_buf[20];
        char reps_buf[20];
        char rm_buf[20];
        
        list_node *nodes = create_exercise_nodes(&exercises[i], name_buf, 
                                                   weight_buf, reps_buf, rm_buf);
        
        if (nodes == NULL) {
            printf("Error: memory allocation failed\n");
            fclose(output_file);
            return 1;
        }
        
        if (write_rm_to_html("row_template.html", output_file, nodes) != 0) {
            printf("Error: could not write exercise row\n");
            free_nodes(nodes);
            fclose(output_file);
            return 1;
        }
        
        free_nodes(nodes);
    }
    
    if (copy_template_to_html("end.html", output_file) != 0) {
        printf("Error: could not read end.html template\n");
        fclose(output_file);
        return 1;
    }
    
    fclose(output_file);
    
    printf("\nOK. HTML report generated: output.html\n");
    printf("Total exercises processed: %d\n", count);
    
    return 0;
}