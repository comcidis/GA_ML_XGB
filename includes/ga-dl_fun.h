#ifndef __GA_DL_FUN_H__
#define __GA_DL_FUN_H__

struct startParam{
   
   int pop_size;
   int initType;
   int elit;
   int crossoverType;
   int mutationType;
   int fitnessType;
   double pc;
   double pm;
   int max_gen;
   double wScore;
   double wTime;
   double wEnergy;

};

#define ALPHA 4.0

typedef struct startParam StartParam;

//=========================================================== - XGBoost Global Functions - ===================================================================================

int generateIndividual(int** cromosome, const int length);
int generatePopulation(int ***population, const int length, StartParam param);

int sortPopulation(int **population, StartParam param, double *result_fitness);  /* DEPRECATED !!*/
int sortPopulation(int **population, StartParam param, double *result_fitness, double *accuracy); /* DEPRECATED !!*/
int sortPopulation(int **population, StartParam param, double *result_fitness, double *score, double *energy, double *time);

int parentSelection(int **population, double *result_fitness, StartParam param, int *A, int *B);
int crossover_func(int *parentA, int *parentB, int *offspring_A, int *offspring_B, StartParam param, const int length);
int mutation_func(int *offspring, const int length, StartParam param);
int newGeneration(int **population, double *result_fitness, const int length, StartParam param);

//=========================================================== - End XGBoost Global Functions - ===================================================================================


//=========================================================== - XGBoost Clasification Functions - ===================================================================================

int xgbcFitness(int **population, double *result_fitness, StartParam param, const int generation, double *score, double *time, double *energy);
int xgbcFitness(int **population,  double *result_fitness, StartParam param, double *score, double *time, double *energy);
int xgbcTestPopulation(int **population, double *time, double *energy, StartParam param, const int generation);
int xgbcTestPopulation(int **population, double *time, double *energy, StartParam param);


int testPopulation(int **population, double *accuracy, StartParam param, const int generation); /* DEPRECATED !!*/
int testPopulation(int **population, double *accuracy, StartParam param); /* DEPRECATED !!*/
 
int fitness(int **population, double *result_fitness, StartParam param); /* DEPRECATED !!*/
int fitness2(int **population, double *result_fitness, StartParam param, const int generation, double *accuracy); /* DEPRECATED !!*/
int fitness2(int **population,  double *result_fitness, StartParam param, double *accuracy); /* DEPRECATED !!*/

//=========================================================== - End XGBoost Clasification Functions - ===================================================================================


//=========================================================== - XGBoost Regression Functions - ===================================================================================

int xgbrFitness(int **population, double *result_fitness, StartParam param, const int generation, double *score, double *time, double *energy);
int xgbrFitness(int **population,  double *result_fitness, StartParam param, double *score, double *time, double *energy);
int xgbrTestPopulation(int **population, double *time, double *energy, StartParam param, const int generation);
int xgbrTestPopulation(int **population, double *time, double *energy, StartParam param);

//=========================================================== - End XGBoost Regression Functions - ===================================================================================


//=========================================================== - Temporary -==================================================================================================

int getETA(int *individual, float * eta);
int getN_JOBS(int *individual, int * n_jobs);
int getN_Estimators(int *individual, int * n_estimators);
int getMAX_DEPTH(int *individual, int * max_depth);

//=========================================================== - /* DEPRECATED !!*/ - ===================================================================================

//int* generateIndividual2(StartParam param, int target_count, double **target_data); /* DEPRECATED !!*/

//void sortPopulation(int **population, double **target_data, const int target_count, StartParam param, double *result_fitness);   /* DEPRECATED !!*/

//void newGeneration(int **population, int **offspring, double *result_fitness, int target_count, double **target_data, StartParam param);  /* DEPRECATED !!*/

//int mutation_func(int *offspring, int target_count, StartParam param);  /* DEPRECATED !!*/
//void parentSelection(int **population, double *result_fitness, StartParam param, int *A, int *B);  /* DEPRECATED !!*/
//void crossover_func(int *parentA, int *parentB, int *offspring_A, int *offspring_B, StartParam param, int target_count);   /* DEPRECATED !!*/

//void fitness2(int **population, int target_count, double **target_data, double **result_fitness, StartParam param);  /* DEPRECATED !!*/
//void fitness2(double **round_results, int nRounds, int target_count, double **target_data);  /* DEPRECATED !!*/

//void fitness3(int **population, int target_count, double **target_data, double **result_fitness, StartParam param);  /* DEPRECATED !!*/
//void fitness4(int **population, int target_count, double **target_data, double **result_fitness, StartParam param);  /* DEPRECATED !!*/
//void fitness5(int **population, int target_count, double **target_data, double **result_fitness, StartParam param);  /* DEPRECATED !!*/


#endif