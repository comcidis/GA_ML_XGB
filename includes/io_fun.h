#ifndef __IO_FUN_H__
#define __IO_FUN_H__

#include "../includes/ga-dl_fun.h"
using namespace std;

int dataRead(const char* inFileName, double *accuracy, StartParam param); /* DEPRECATED !!*/

int getAccuracy(const char* inFileName, double *accuracy, StartParam param, const int generation);
int getAccuracy(const char* inFileName, double *accuracy, StartParam param);
int getTestResult(const char* inFileName, double *energy, double *time);
int configParam(const char* configFileName, StartParam *param);

//-----------------------------------------/* DEPRECATED !!*/-------------------------------------------------------------------------------------------------

void dataRead(const char* inFileName, int *target_count, int *sol_count, const double velocity, double *BEST_SOLUTION, double ***target_data); //read data from input file (deprecated!!) DEPRECATED
void dataRead(const char* inFileName, int *target_count, double ***target_data); //read data from input file
void printRound(int i); //print on the terminal the number o the current running iteration 
void show_population(int **population, const int pop_size, const int target_count); 
void show_population(int **population, const int pop_size, const int target_count, double *result_fitness);
void show_population(int **population, const int pop_size, const int target_count, double *result_fitness, const double velocity, double **target_data);
void show_best_solution(int *population, const int target_count, double length);
void show_best_solution(int *population, const int target_count, double **target_data, double length);
void show_individual(int *individual, const int target_count, double length);

#endif