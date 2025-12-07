#ifndef RM_CALCULATOR_H
#define RM_CALCULATOR_H

#include "html_templater.h"

double calculate_epley(double weight, int reps);
double calculate_brzycki(double weight, int reps);
double calculate_1rm(double weight, int reps);
void double_to_string(double value, char *buffer, int precision);
void int_to_string(int value, char *buffer);
list_node* create_exercise_chain(char *name, double weight, int reps, double one_rm, char *name_buf, char *weight_buf, char *reps_buf, char *rm_buf);
void free_chain(list_node *head);

#endif