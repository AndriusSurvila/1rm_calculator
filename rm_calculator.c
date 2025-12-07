#include "rm_calculator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double calculate_epley(double weight, int reps)
{
    if (reps <= 0) return weight;
    return weight * (1.0 + 0.0333 * reps);
}

double calculate_brzycki(double weight, int reps)
{
    if (reps <= 0 || reps >= 37) return weight;
    return weight * (36.0 / (37.0 - reps));
}

double calculate_1rm(double weight, int reps)
{
    double epley = calculate_epley(weight, reps);
    double brzycki = calculate_brzycki(weight, reps);
    return (epley + brzycki) / 2.0;
}

void double_to_string(double value, char *buffer, int precision)
{
    if (precision == 0) {
        sprintf(buffer, "%.0f", value);
    } else if (precision == 1) {
        sprintf(buffer, "%.1f", value);
    } else if (precision == 2) {
        sprintf(buffer, "%.2f", value);
    } else {
        sprintf(buffer, "%g", value);
    }
}

void int_to_string(int value, char *buffer)
{
    sprintf(buffer, "%d", value);
}

list_node* create_exercise_chain(char *name, double weight, int reps, double one_rm, char *name_buf, char *weight_buf, char *reps_buf, char *rm_buf)
{
    list_node *node1 = (list_node*)malloc(sizeof(list_node));
    list_node *node2 = (list_node*)malloc(sizeof(list_node));
    list_node *node3 = (list_node*)malloc(sizeof(list_node));
    list_node *node4 = (list_node*)malloc(sizeof(list_node));
    
    if (!node1 || !node2 || !node3 || !node4) {
        return NULL;
    }
    
    strcpy(name_buf, name);
    double_to_string(weight, weight_buf, 0);
    int_to_string(reps, reps_buf);
    double_to_string(one_rm, rm_buf, 0);
    
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

void free_chain(list_node *head)
{
    while (head != NULL) {
        list_node *temp = head;
        head = head->next;
        free(temp);
    }
}