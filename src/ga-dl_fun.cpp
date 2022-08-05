//#include "../commons/tspio.h"
//#include "../commons/tspcommon.h"
#include "../includes/ga-dl_fun.h"
#include "../includes/io_fun.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
using namespace std;

//=========================================================== - XGBoost Global Functions - ===================================================================================

int generateIndividual(int** cromosome, const int length)
{
   int i;

   cromosome[0] = (int*)malloc(sizeof(int)*length);
   
   for(i = 0; i < length; i++)
   {
      cromosome[0][i] = (rand() % 2);
   }
/*
   for(i = 0; i < length; i++)
   {
      printf("%d, ",cromosome[0][i]);
   }   
   putchar('\n');
*/   
   return 0;
}

int generatePopulation(int ***population, const int length, StartParam param)
{
   int err = 0;

//printf("func current line %d\n", __LINE__);

   population[0] = (int**)malloc(sizeof(int*)* param.pop_size);

//printf("func current line %d\n", __LINE__);   

   for(int i = 0; i < param.pop_size; i++)
   {
      err = generateIndividual(&population[0][i], length);
   }

//printf("func current line %d\n", __LINE__);

   return err;

}

int sortPopulation(int **population, StartParam param, double *result_fitness) /* DEPRECATED !!*/
{
   double temp;
   int *aux;
   
   for(int i = 0; i < (param.pop_size-1); i++)
   {
      for(int j = 0; j < (param.pop_size-(i+1)); j++)
      {
         if(result_fitness[j] < result_fitness[j+1])
         {
            temp = result_fitness[j];
            result_fitness[j] = result_fitness[j+1];
            result_fitness[j+1] = temp;
            aux = population[j];
            population[j] = population[j+1];
            population[j+1] = aux;
         }

      }
   }

//    free(length);
//   cout << "sortPopulation checkpoint 5" <<endl;
   return 0;
}

int sortPopulation(int **population, StartParam param, double *result_fitness, double *accuracy) /* DEPRECATED !!*/
{
   double temp;
   int *aux;
   
   for(int i = 0; i < (param.pop_size-1); i++)
   {
      for(int j = 0; j < (param.pop_size-(i+1)); j++)
      {
         if(result_fitness[j] < result_fitness[j+1])
         {
            temp = result_fitness[j];
            result_fitness[j] = result_fitness[j+1];
            result_fitness[j+1] = temp;
            temp = accuracy[j];
            accuracy[j] = accuracy[j+1];
            accuracy[j+1] = temp;
            aux = population[j];
            population[j] = population[j+1];
            population[j+1] = aux;
         }

      }
   }

//    free(length);
//   cout << "sortPopulation checkpoint 5" <<endl;
   return 0;
}

int sortPopulation(int **population, StartParam param, double *result_fitness, double *score, double *energy, double *time)
{
   double temp;
   int *aux;
   
   for(int i = 0; i < (param.pop_size-1); i++)
   {
      for(int j = 0; j < (param.pop_size-(i+1)); j++)
      {
         if(result_fitness[j] < result_fitness[j+1])
         {
            temp = result_fitness[j];
            result_fitness[j] = result_fitness[j+1];
            result_fitness[j+1] = temp;

            temp = score[j];
            score[j] = score[j+1];
            score[j+1] = temp;

            temp = energy[j];
            energy[j] = energy[j+1];
            energy[j+1] = temp;

            temp = time[j];
            time[j] = time[j+1];
            time[j+1] = temp;

            aux = population[j];
            population[j] = population[j+1];
            population[j+1] = aux;
         }

      }
   }

//    free(length);
//   cout << "sortPopulation checkpoint 5" <<endl;
   return 0;
}

int parentSelection(int **population, double *result_fitness, StartParam param, int *A, int *B)
{
   double *wheel, x;
   int i, k;
   
   wheel = (double*)malloc(sizeof(double)*(param.pop_size + 1));
   wheel[0] = 0;



   for (i = 0; i < param.pop_size; i++)  /*sets up the Roulette wheel*/
      wheel[i+1] = result_fitness[i] + wheel[i];


   long _rnd = rand();



   if (_rnd == 0)
      _rnd++;



   x = wheel[param.pop_size] * (double)_rnd / RAND_MAX; 
   printf("Parent A x = %.6lf\n", x);



   k = 0;
   while (!((wheel[k] <= x) && (x <= wheel[k+1])))
      k++;
   A[0] = k;
 
   do
   {
      long _rnd = rand();

      if (_rnd == 0)
	 _rnd++;

      x = wheel[param.pop_size] * (double)_rnd / RAND_MAX; 
printf("Parent B x = %.6lf\n", x);

      k = 0;
      while (!((wheel[k] <= x) && (x <= wheel[k+1])))
	 k++;
      B[0] = k;

   }while(A[0] == B[0]);
  
   free(wheel);

   return 0;
}

int crossover_func(int *parentA, int *parentB, int *offspring_A, int *offspring_B, StartParam param, const int length)
{
   double crossVal, crossProb;
   bool crossover = false;
   int crosspoint;

   crossProb = param.pc;

   crossVal = 100.0f * (double)rand()/RAND_MAX;
   if(crossVal <= crossProb)
   {
      crosspoint = (rand()%3);
      int aux[3] = {3,7,16};

      for(int i = 0; i < aux[crosspoint]; i++)
      {
         //printf("%d no cross\n", i);
         offspring_A[i] = parentA[i];
         offspring_B[i] = parentB[i];
      }
      for (int i = aux[crosspoint]; i < length; i++)
      {
         //printf("%d cross\n", i);
         offspring_A[i] = parentB[i];
         offspring_B[i] = parentA[i];
      }
      

   }
   else
   {
      for (int i = 0; i < length; i++)
      {
         //printf("no crossover \n");
         offspring_A[i] = parentA[i];
         offspring_B[i] = parentB[i];
      }
      
   }


   // for(int i = 0; i < length; i++)
   // {
   //    crossVal = 100.0f * (double)rand()/RAND_MAX;
   //    if(crossVal <= crossProb)
   //    {
   //       crossover = !crossover;
   //       crossProb = crossProb/2;
   //       printf("%d crossInv, crossProb = %.2lf\n", i, crossProb);
   //    }

   //    if(crossover)
   //    {
   //       printf("%d cross\n", i);
   //       offspring_A[i] = parentB[i];
   //       offspring_B[i] = parentA[i];
   //    }
   //    else
   //    {
   //       printf("%d no cross\n", i);
   //       offspring_A[i] = parentA[i];
   //       offspring_B[i] = parentB[i];
   //    }
   // }

   return 0;
}

int mutation_func(int *offspring, const int length, StartParam param)
{
   double mutation;

   for(int i = 0; i < length; i++)
   {
      double pm = param.pm;
      mutation = 100.0f * (double)rand()/RAND_MAX;
      if(mutation < pm)
      {
         pm = pm/2;
         //printf("mutation %d\n", i);
         if (offspring[i])
         {
            offspring[i] = 0;
         }
         else
         {
            offspring[i] = 1;
         }
         
      }

   }

   return 0;
}

int newGeneration(int **population, double *result_fitness, const int length, StartParam param)
{
   int **offspring, pool = (param.pop_size - param.elit);
   int *offspring_A, *offspring_B, parentA, parentB, err, *aux;

   offspring = (int**)malloc(sizeof(int*) * (pool+1));
   for(int i = 1; i < pool+1; i++)
   {
      offspring[i] = (int*)malloc(sizeof(int) * length);
   }

   int j = 0;

   while (j < pool)
   {
      err = parentSelection(population, result_fitness, param, &parentA, &parentB);
      if(err)
      {
         printf("parente select fail!!\n\n");
         return err;
      }

      printf("parent A = %d, fitness %.6lf, parent B = %d, fitness %.6lf\n", parentA, result_fitness[parentA], parentB, result_fitness[parentB]);

      offspring_A = (int*)malloc(sizeof(int)*length);
      offspring_B = (int*)malloc(sizeof(int)*length);

      err = crossover_func(population[parentA], population[parentB], offspring_A, offspring_B, param, length);
      if(err)
      {
         printf("crossover fail!!\n\n");
         return err;
      }

      err = mutation_func(offspring_A, length, param);
      if(err)
      {
         printf("mutation A fail!!\n\n");
         return err;
      }
      err = mutation_func(offspring_B, length, param);
      if(err)
      {
         printf("mutation B fail!!\n\n");
         return err;
      }

      offspring[j] = offspring_A;
      offspring[j+1] = offspring_B;

      j += 2;
   }


   for(int j = 0; j < pool; j++)
   {
//       printf("current line %d, j = %d\n", __LINE__, j);
      aux = population[j+param.elit];
      population[j+param.elit] = offspring[j];
      offspring[j] = aux;

   }
   for(int i = 1; i < pool+1; i++)
   {
      free(offspring[i]);
   }
   free(offspring);

   return 0;
}

int getETA(int *individual, float *eta)
{
   eta[0] = (float)((individual[0]*32) + (individual[1]*16) + (individual[2]*8) + (individual[3]*4) + (individual[4]*2) + individual[5] + 1) /100.0f;

   return 0;
}
int getN_JOBS(int *individual, int *n_jobs)
{
   n_jobs[0] = individual[6]*8 + individual[7]*4 + individual[8]*2 + individual[9] + 1;

   return 0;
}
int getN_Estimators(int *individual, int *n_estimators)
{
   n_estimators[0] = individual[10]*256 + individual[11]*128 + individual[12]*64 + individual[13]*32 + individual[14]*16 + 
                     individual[15]*8 + individual[16]*4 + individual[17]*2 + individual[18] + 9;

   return 0;
}
int getMAX_DEPTH(int *individual, int *max_depth)
{
   max_depth[0] = (individual[19]*4) + (individual[20]*2) + individual[21] + 3;

   return 0;
}

//=========================================================== - End XGBoost Global Functions - ===================================================================================


//=========================================================== - XGBoost Clasification Functions - ===================================================================================

int xgbcFitness(int **population, double *result_fitness, StartParam param, const int generation, double *score, double *time, double *energy)
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};
   double alpha, beta, gama, wt;
   double Sn = 0, Tn = 0, En = 0;
   
   wt = param.wScore + param.wTime + param.wEnergy;
   alpha = param.wScore/wt;
   beta = param.wEnergy/wt;
   gama = param.wTime/wt;

   printf("alpha = %.3lf, beta = %.3lf, gama = %.3lf\n", alpha, beta, gama);

   err = getAccuracy(inFileName, score, param, generation);

   for(int i = 0; i < param.pop_size; i++)
   {
      //Sn += score[i];
      Tn += time[i];
      En += energy[i];
   }

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = alpha*((score[i]*100)) + beta*(1/(energy[i]/En)) + gama*(1/(time[i]/Tn));
   }

   return 0;
}
int xgbcFitness(int **population,  double *result_fitness, StartParam param, double *score, double *time, double *energy)
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};
   double alpha, beta, gama, wt;
   double Sn = 0, Tn = 0, En = 0;

   wt = param.wScore + param.wTime + param.wEnergy;
   alpha = param.wScore/wt;
   beta = param.wEnergy/wt;
   gama = param.wTime/wt;

   printf("alpha = %.3lf, beta = %.3lf, gama = %.3lf\n", alpha, beta, gama);


   err = getAccuracy(inFileName, score, param);

   for(int i = 0; i < param.pop_size; i++)
   {
      //Sn += score[i];
      Tn += time[i];
      En += energy[i];
   }

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = alpha*((score[i]*100)) + beta*(1/(energy[i]/En)) + gama*(1/(time[i]/Tn));
   }

   return 0;
}

int xgbcTestPopulation(int **population, double *time, double *energy, StartParam param, const int generation)
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   int start = 0, err;
   if(generation)
   {
      start = param.elit;
   }

   for(int i = start; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      //sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //            max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"/mnt/storage/andre/GA-CNN/PySrc/monitor.sh  python3.8  /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d",
               max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      err = getTestResult("PerfResult.dat", &energy[i], &time[i]);
      printf("energy = %.2lf, time = %.3lf\n", energy[i], time[i]);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}

int xgbcTestPopulation(int **population, double *time, double *energy, StartParam param)
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   int err;

   for(int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      // sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //             max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"/mnt/storage/andre/GA-CNN/PySrc/monitor.sh  python3.8  /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
               max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      err = getTestResult("PerfResult.dat", &energy[i], &time[i]);
      printf("energy = %.2lf, time = %.3lf\n", energy[i], time[i]);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}




int fitness(int **population,  double *result_fitness, StartParam param) /* DEPRECATED !!*/
{
   //double *accuracy;
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};

   //accuracy = (double*)malloc(sizeof(double)*param.pop_size);

   err = dataRead(inFileName, result_fitness, param);

   return 0;
}

int fitness2(int **population,  double *result_fitness, StartParam param, const int generation, double *accuracy) /* DEPRECATED !!*/
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};

   err = getAccuracy(inFileName, accuracy, param, generation);

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = 1/accuracy[i];
   }

   return 0;
}

int fitness2(int **population,  double *result_fitness, StartParam param, double *accuracy) /* DEPRECATED !!*/
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};

   err = getAccuracy(inFileName, accuracy, param);

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = 1/accuracy[i];
   }

   return 0;
}

int testPopulation(int **population, double *accuracy, StartParam param, const int generation) /* DEPRECATED !!*/
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   int start = 0;
   if(generation)
   {
      start = param.elit;
   }

   for(int i = start; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      //sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //            max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"python3.8  /mnt/storage/andre/GA-CNN/PySrc/XGBRegression_4.py %d %.2f %d %d", 
                  max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}

int testPopulation(int **population, double *accuracy, StartParam param) /* DEPRECATED !!*/
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   

   for(int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      // sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //             max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"python3.8  /mnt/storage/andre/GA-CNN/PySrc/XGBRegression_4.py %d %.2f %d %d", 
                  max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}

//=========================================================== - End XGBoost Clasification Functions - ===================================================================================

//=========================================================== - XGBoost Regression Functions - ===================================================================================

int xgbrFitness(int **population, double *result_fitness, StartParam param, const int generation, double *score, double *time, double *energy)
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};
   double alpha, beta, gama, wt;
   double Sn = 0, Tn = 0, En = 0;

   wt = param.wScore + param.wTime + param.wEnergy;
   alpha = param.wScore/wt;
   beta = param.wEnergy/wt;
   gama = param.wTime/wt;

   printf("alpha = %.3lf, beta = %.3lf, gama = %.3lf\n", alpha, beta, gama);


   err = getAccuracy(inFileName, score, param, generation);

   for(int i = 0; i < param.pop_size; i++)
   {
      Sn += score[i];
      Tn += time[i];
      En += energy[i];
   }

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = alpha*(1/(score[i]/Sn)) + beta*(1/(energy[i]/En)) + gama*(1/(time[i]/Tn));
   }

   return 0;
}
int xgbrFitness(int **population,  double *result_fitness, StartParam param, double *score, double *time, double *energy)
{
   int err = 0;
   char inFileName[24] = {"accuracy.dat"};
   double alpha, beta, gama, wt;
   double Sn = 0, Tn = 0, En = 0;

   wt = param.wScore + param.wTime + param.wEnergy;
   alpha = param.wScore/wt;
   beta = param.wEnergy/wt;
   gama = param.wTime/wt;

   printf("alpha = %.3lf, beta = %.3lf, gama = %.3lf\n", alpha, beta, gama);


   err = getAccuracy(inFileName, score, param);

   for(int i = 0; i < param.pop_size; i++)
   {
      Sn += score[i];
      Tn += time[i];
      En += energy[i];
   }

   for(int i = 0; i < param.pop_size; i++)
   {
      //result_fitness[i] = pow((((1/(pow((1/accuracy[i]), 2)-1))-1)*100),4);
      result_fitness[i] = alpha*(1/(score[i]/Sn)) + beta*(1/(energy[i]/En)) + gama*(1/(time[i]/Tn));
   }

   return 0;
}

int xgbrTestPopulation(int **population, double *time, double *energy, StartParam param, const int generation)
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   int start = 0, err;
   if(generation)
   {
      start = param.elit;
   }

   for(int i = start; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      //sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //            max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"exec /mnt/storage/andre/GA-CNN/PySrc/monitor.sh  python3.8  /mnt/storage/andre/GA-CNN/PySrc/XGBRegression_4.py %d %.2f %d %d", 
               max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      err = getTestResult("PerfResult.dat", &energy[i], &time[i]);
      printf("energy = %.2lf, time = %.3lf\n", energy[i], time[i]);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}

int xgbrTestPopulation(int **population, double *time, double *energy, StartParam param)
{
   char command[256];
   float eta;
   int n_jobs, n_estimators, max_depth;
   int err;

   for(int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      // sprintf(command,"python3.8 /mnt/storage/andre/Teste/ML-From-Scratch/mlfromscratch/examples/XGBoost_real_v3.py %d %.2f %d %d", 
      //             max_depth, eta, n_jobs, n_estimators);
      sprintf(command,"exec /mnt/storage/andre/GA-CNN/PySrc/monitor.sh  python3.8  /mnt/storage/andre/GA-CNN/PySrc/XGBRegression_4.py %d %.2f %d %d", 
               max_depth, eta, n_jobs, n_estimators);
      printf("\nRunning test XGBoost %d\n",i);
      system(command);
      err = getTestResult("PerfResult.dat", &energy[i], &time[i]);
      printf("energy = %.2lf, time = %.3lf\n", energy[i], time[i]);
      printf("End test XGBoost %d\n", i);
   }


   return 0;
}


//=========================================================== - End XGBoost Regression Functions - ===================================================================================

//===================================================================================================================================================================================


// int* generateIndividual2(StartParam param, int target_count, double **target_data)   /* NEW !!*/
// {
//    int *cromosomo, i, j, k;
//    bool *visited;
//    double *edge_time, **route_data, *t_prob, *strength, x, t_dist = 0, r_dist = 0, h_dist = 0;
//    double *h_data;

//    t_prob = (double*)malloc(sizeof(double)*target_count);
//    strength = (double*)malloc(sizeof(double)*(target_count+1));
//    edge_time = (double*)malloc(sizeof(double)*target_count);
//    route_data = (double**)malloc(sizeof(double*)*target_count);
   
//    for(int i = 0; i < target_count; i++)
//    {
//       route_data[i] = (double*)malloc(sizeof(double)*2);
//    }
//    for(i = 0; i < target_count; i++)
//    {
//       route_data[i][0] = target_data[i][0];
//       route_data[i][1] = target_data[i][1];
//    }
   
//    h_data = (double*)malloc(sizeof(double)*3);
//    h_data[0] = route_data[0][0];
//    h_data[1] = route_data[0][1];
//    h_data[2] = param.velocity;

//    cromosomo = (int*)malloc(sizeof(int)*(target_count+1));
//    visited = (bool*)malloc(sizeof(bool)*target_count);
   
// /* Initialise tour */
//    for (i=0; i<target_count; i++)
//    {
//       visited[i] = false;
//       cromosomo[i] = -1;
//    }
   
//    /* Tour always starts at position 0 */
//    cromosomo[target_count] = cromosomo[0] = 0;
//    visited[0] = true;
//    h_data[0] = target_data[0][0];
//    h_data[1] = target_data[0][1];
   
//    /* j marks where we are in constructing the tour, 
//       k is the next node to visit */
//    for (j=1; j<target_count; j++)
//    {

//    /* Get transition probabilities - cannot choose a 
//       node that has previously been used */
//       for (i=0; i<target_count; i++)
//       {
//          t_prob[i] = 0.0;
//          if (visited[i] == false)
//          {
//             t_prob[i] = 1/pow((h_data[2]*getInterceptTime(route_data[i], target_data[i][3], target_data[i][2], h_data)), 2);
//          }
//          else
//          {
//             t_prob[i] = 0.0;
//          }
//       }

//       /* Roulette wheel selection - equivalent to probability-
//          based selection of next city. The index of the next 
//          city on the tour is given in k */
//       strength[0] = 0;

//       for (i=0; i<target_count; i++)
//       {
//          strength[i+1] = t_prob[i] + strength[i];
//       }
//       long _rnd = rand();
//       if (_rnd == 0)
//          _rnd++;
      
//       x = strength[target_count] * (double)_rnd / RAND_MAX; 

//       k = 0;
//       while (!((strength[k] <= x) && (x <= strength[k+1])))
//       {
//          k++;
//       }

//       cromosomo[j] = k;
//       visited[k] = true;

//       edge_time[j-1] = getInterceptTime(route_data[k], target_data[k][3], target_data[k][2], h_data);
//       r_dist += edge_time[j-1]*param.velocity;

//       for(i = 0; i < target_count; i++)
//       {
//          double vt[2];
//          getVt(target_data[i][3], target_data[i][2], vt);

//          route_data[i][0] += edge_time[j-1] * vt[0];
//          route_data[i][1] += edge_time[j-1] * vt[1];
//       }

//       h_data[0] = route_data[k][0];
//       h_data[1] = route_data[k][1];
      
//       h_dist = param.velocity * getInterceptTime(route_data[0], target_data[0][3], target_data[0][2], h_data);
      
//       t_dist = r_dist + h_dist;
//       if(t_dist > param.autonomy)
//       {
// 	 cromosomo[j] = 0;
// 	 break;
//       }
      
//    }
   
// //    show_individual(cromosomo, target_count, 12345.6789);
// /*// printf("current line %d\n", __LINE__);
// //    cout<<"New population Individual ";
// //    for( j = 0; j < target_count; j++)
// //    {
// //       printf("%s%d%s", j == 0 ? "| " : " ", cromosomo[j], j == target_count-1 ? " |\n" : "");
// //    }
// // */   
// //    free(h_data);
// // // printf("current line %d\n", __LINE__);
// //    double length = routeLength(cromosomo);
// // // printf("current line %d\n", __LINE__);
// //    cout << "total distance: " << length <<endl;
// //    
// //    sleep(10);

//    free(t_prob);
//    free(strength);
//    free(visited);
//    free(edge_time);
//    for(int i = 0; i < target_count; i++)
//    {
//       free(route_data[i]);
//    }
//    free(route_data);
//    free(h_data);
//    return cromosomo;                          
// }




// int mutation_func(int *offspring, int target_count)
// {
//    int *mutation_pool;
//    int temp, chrom_length = 1, i = 1, mGen1, mGen2;

     
//    while(offspring[i] != 0)
//    {
//       chrom_length++;
//       i++;
//    }
  
//    mGen1 = (rand()%(chrom_length-1))+1;
//    mGen2 = (rand()%(target_count-2)); 
  
//    mutation_pool = (int*)malloc(sizeof(int)*(target_count-2));
//    i = 0;
//    for(int j = 1; j < target_count; j++)
//    {
//       if(j != offspring[mGen1])
//       {
// 	 mutation_pool[i] = j;
// 	 i++;
//       }
//    }


//    i = 1;
//    while(offspring[i] != 0)
//    {
//       if(offspring[i] == mutation_pool[mGen2])
//       {
// 	 offspring[i] = offspring[mGen1];
// 	 break;
//       }
//       i++;
//    }
// 	 offspring[mGen1] = mutation_pool[mGen2];

//    free(mutation_pool);
//    return 0;
// }

// int mutation_func(int *offspring, int target_count, StartParam param)
// {
//    int *mutation_pool;
//    int temp, chrom_length = 1, i = 1, mGen1, mGen2;
//    double mutate;
   
//    chrom_length = getRouteSteps(offspring);
   
//    do
//    {
//       long _rnd = rand();

//       if (_rnd == 0)
// 	 _rnd++;
      
//       mutate = 100.0 * (double)_rnd / RAND_MAX;
      
//       //cout << "mutate: " << mutate <<endl;
      
      
//       if(mutate < param.pm)
//       {
// 	 mGen1 = (rand()%(chrom_length-1))+1;
// 	 mGen2 = (rand()%(target_count-2)); 
      
// 	 mutation_pool = (int*)malloc(sizeof(int)*(target_count-2));
// 	 i = 0;
// 	 for(int j = 1; j < target_count; j++)
// 	 {
// 	    if(j != offspring[mGen1])
// 	    {
// 	       mutation_pool[i] = j;
// 	       i++;
// 	    }
// 	 }


// 	 i = 1;
// 	 while(offspring[i] != 0)
// 	 {
// 	    if(offspring[i] == mutation_pool[mGen2])
// 	    {
// 	       offspring[i] = offspring[mGen1];
// 	       break;
// 	    }
// 	    i++;
// 	 }
// 	       offspring[mGen1] = mutation_pool[mGen2];

// 	 free(mutation_pool);
      
//       }
   
//    }while(mutate < param.pm);
   
//    return 0;
// }



// void crossover_func(int *parentA, int *parentB, int *offspring_A, int *offspring_B, StartParam param, int target_count)
// {
//    double crosProb = param.pc;
//    int crosPointA, crosPointB, sizeA, sizeB;
//    int index = 0;
//    int i, k;
   
//    sizeA = getRouteSteps(parentA);
//    sizeB = getRouteSteps(parentB);
   
//    /* crossover */
//    long _rnd = rand();

//    if (_rnd == 0)
//       _rnd++;
   
//    double crosAux = 100.0 * (double)_rnd / RAND_MAX;
   
//    if(crosAux <= crosProb)
//    {  
//       if(sizeA > 1)
//       {
// 	 crosPointA = (rand()%(sizeA-1))+1;
//       }
//       else
//       {
// 	 crosPointA = 1;
//       }
//       if(sizeA == sizeB)
//       {
// 	 crosPointB = crosPointA;
//       }
//       else
//       {
// 	 crosPointB = (rand()%(sizeB-1))+1;
//       }
      
//       for(int j = 0; j < crosPointA; j++)
//       {
// 	 offspring_A[j] = parentA[j];
	 
// 	 //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//       }
//       for(int j = 0; j < crosPointB; j++)
//       {
// 	 offspring_B[j] = parentB[j];
	 
// 	 //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//       }

//       int index = crosPointA;
      
//       int j = 0;
//       do
//       {
// 	 j++;
// 	 int flag = 0;
	 
// 	 for(int k = 1; k < index; k++)
// 	 {
// 	    if(parentB[j] == offspring_A[k])
// 	    {
// 	       flag++;
// 	    }
	    
// 	 }
// 	 if(!flag)
// 	 {
// 	    if(index <= target_count)
// 	    {
// 	       offspring_A[index] = parentB[j];
// // 		  printf("offspring_A[%d] = %d \n", index, offspring_A[index] );
// 	       index++;
// 	    }
// 	 }
	 
//       }while(parentB[j] != 0);
      
//       index = crosPointB;
//       j = 0;
//       do
//       {
// 	 j++;
// 	 int flag = 0;
	 
// 	 for(int k = 1; k < index; k++)
// 	 {
// 	    if(parentA[j] == offspring_B[k])
// 	    {
// 	       flag++;
// 	    }
// 	 }
// 	 if(!flag)
// 	 {
// 	    if(index <= target_count)
// 	    {
// 	       offspring_B[index] = parentA[j];
// // 		  printf("offspring_B[%d] = %d \n", index, offspring_B[index]);
// 	       index++;
// 	    }
// 	 }
	 
//       }while(parentA[j] != 0);
      
//       offspring_A[target_count] = offspring_B[target_count] = 0;
      
//    }
//    else
//    {/*printf("no crossover\n");*/

//       offspring_A[0] = offspring_B[0] = 0;
//       for(int j = 1; j < target_count+1; j++)
//       {
// 	 offspring_A[j] = parentA[j];
// 	 if(parentA[j] == 0)
// 	    break;
//       }
//       for(int j = 1; j < target_count+1; j++)
//       {
// 	 offspring_B[j] = parentB[j];
// 	 if(parentB[j] == 0)
// 	    break;
//       }
     
//    }
// //    show_individual(offspring_A, target_count, 98765.4321);
// //    show_individual(offspring_B, target_count, 98765.4321);
   
      
// }

// void newGeneration(int **population, int **offspring, double *result_fitness, int target_count, double **target_data, StartParam param)
// {
//    int *aux;
//    double crosProb = param.pc, *wheel, x, lenA, lenB;
//    int crosPointA, crosPointB, parentA, parentB, sizeA, sizeB;
//    int *offspring_A, *offspring_B; 
//    int index = 0;
//    int i, k;

//    //aux = (int**)malloc(sizeof(int*)*(pop_size-elit));
//    offspring = (int**)malloc(sizeof(int*)*((param.pop_size+1)-param.elit));
   
//    i = 0;
   
//    while(i < (param.pop_size-param.elit))
//    {
// //       printf("current line %d\n", __LINE__);
//       parentSelection(population, result_fitness, param, &parentA, &parentB);
// //       printf("current line %d\n", __LINE__);
//       offspring_A = (int*)malloc(sizeof(int)*(target_count+1));
//       offspring_B = (int*)malloc(sizeof(int)*(target_count+1));
// //       printf("current line %d\n", __LINE__);
//       crossover_func(population[parentA], population[parentB], offspring_A, offspring_B, param, target_count);
// //       printf("current line %d\n", __LINE__);
//       mutation_func(offspring_A, target_count, param);
//       mutation_func(offspring_B, target_count, param);
// //       printf("current line %d\n", __LINE__);
      
//       lenA = routeLength2(offspring_A, target_data, target_count, param.velocity);
//       lenB = routeLength2(offspring_B, target_data, target_count, param.velocity);
//       if(lenA < param.autonomy && lenB < param.autonomy)
//       {/*printf("offspring_A & offspring_B < autonomy ");*/
// 	 offspring[i] = offspring_A;

// 	 offspring[i+1] = offspring_B;
// 	 i += 2;
//       }
//       else if(lenA < param.autonomy)
//       {/*printf("only offspring_A < autonomy\n");*/
// 	 offspring[i] = offspring_A;
// 	 free(offspring_B);
// 	 i++;
//       }
//       else if(lenB < param.autonomy)
//       {/*printf("only offspring_B < autonomy\n");*/
// 	 offspring[i] = offspring_B;
// 	 free(offspring_A);
// 	 i++;
//       }
//       else
//       {/*printf("offspring_A & offspring_B > autonomy\n");*/
// 	 free(offspring_A);
// 	 free(offspring_B);
//       }
      
//    }
// /*   
//    printf("current line %d, i = %d\n", __LINE__, i);
//    sleep(5);*/
   
//    for(int j = 0; j < param.pop_size-param.elit; j++)
//    {
// //       printf("current line %d, j = %d\n", __LINE__, j);
//       aux = population[j+param.elit];
//       population[j+param.elit] = offspring[j];
//       offspring[j] = aux;

//    }

//    for(int j = 0; j < i; j++)
//    {
// //       printf("current line %d, j = %d\n", __LINE__, j);
//       free(offspring[j]);
//    }
//    free(offspring);
   
   
// }

// void selection_crossover_asymm(int **population, int **offspring, double *result_fitness, int target_count, double **target_data, StartParam param)
// {
//    double crosProb = param.pc, *wheel, x;
//    int crosPointA, crosPointB, parentA, parentB, sizeA, sizeB;
//    int *offspring_A, *offspring_B; 
//    int index = 0;
//    int i, k;
   
//    wheel = (double*)malloc(sizeof(double)*(param.pop_size + 1));
//    wheel[0] = 0;
  
//    for (i = 0; i < param.pop_size; i++)  /*sets up the Roulette wheel*/
//       wheel[i+1] = result_fitness[i] + wheel[i];
   
// //    for(int i = 0; i < pop_size-elit; i++)
//    i = 0;
//    while(i < (param.pop_size-param.elit))
//    {
//       sizeA = sizeB = 0;

//       long _rnd = rand();

//       if (_rnd == 0)
// 	 _rnd++;

//       x = wheel[param.pop_size] * (double)_rnd / RAND_MAX; 

//       k = 0;
//       while (!((wheel[k] <= x) && (x <= wheel[k+1])))
// 	 k++;
//       parentA = k;
      
//       do
//       {
// 	 long _rnd = rand();

// 	 if (_rnd == 0)
// 	    _rnd++;

// 	 x = wheel[param.pop_size] * (double)_rnd / RAND_MAX; 

// 	 k = 0;
// 	 while (!((wheel[k] <= x) && (x <= wheel[k+1])))
// 	    k++;
// 	 parentB = k;

//       }while(parentA == parentB);    // ensures ParentA is Different from ParentB

//       sizeA = getRouteSteps(population[parentA]);
//       sizeB = getRouteSteps(population[parentB]);
      
//       /* crossover */
//       double crosAux = (double)(rand()%10000)/100.0f;
// //      cout << "i = " << i << "crosAux = " << crosAux <<endl;
//       if(crosAux <= crosProb)
//       {
// //         cout << "crosPoint: " << crosPoint <<endl;
//          offspring_A = (int*)malloc(sizeof(int)*(target_count+1));
//          offspring_B = (int*)malloc(sizeof(int)*(target_count+1));
         
// 	 if(sizeA > 1)
// 	 {
// 	    crosPointA = (rand()%(sizeA-1))+1;
// 	 }
// 	 else
// 	 {
// 	    crosPointA = 1;
// 	 }
// 	 if(sizeA == sizeB)
// 	 {
// 	    crosPointB = crosPointA;
// 	 }
// 	 else
// 	 {
// 	    crosPointB = (rand()%(sizeB-1))+1;
// 	 }
         
// //         doAgain:
// /*         
//          for(int j = 0; j < crosPoint; j++)
//          {
//             offspring_A[j] = population[parentA][j];
//             offspring_B[j] = population[parentB][j];
            
//             //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//          }*/
//          for(int j = 0; j < crosPointA; j++)
//          {
//             offspring_A[j] = population[parentA][j];
// //             offspring_B[j] = population[parentB][j];
            
//             //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//          }
//          for(int j = 0; j < crosPointB; j++)
//          {
// //             offspring_A[j] = population[parentA][j];
//             offspring_B[j] = population[parentB][j];
            
//             //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//          }

//          int index = crosPointA;
         
// 	 int j = 0;
//          do
//          {
//             j++;
//             int flag = 0;
            
//             for(int k = 1; k < index; k++)
//             {
//                if(population[parentB][j] == offspring_A[k])
//                {
//                   flag++;
//                }
               
//             }
//             if(!flag)
//             {
//                if(index <= target_count)
//                {
//                   offspring_A[index] = population[parentB][j];
// // 		  printf("offspring_A[%d] = %d \n", index, offspring_A[index] );
//                   index++;
//                }
//             }
            
//          }while((population[parentB][j] != 0));
         
//          index = crosPointB;
// 	 j = 0;
//          do
//          {
//             j++;
//             int flag = 0;
	    
//             for(int k = 1; k < index; k++)
//             {
//                if(population[parentA][j] == offspring_B[k])
//                {
//                   flag++;
//                }
//             }
//             if(!flag)
//             {
//                if(index <= target_count)
//                {
//                   offspring_B[index] = population[parentA][j];
// // 		  printf("offspring_B[%d] = %d \n", index, offspring_B[index]);
//                   index++;
//                }
//             }
	    
//          }while((population[parentA][j] != 0));
// /*	 
// 	 printf("offspring\ncrossA = %d, crossB = %d\n", crosPointA, crosPointB);
// 	 for( j = 0; j < target_count+1; j++)
// 	 {
// 	    printf("%s%d%s", j == 0 ? "| " : " ", population[parentA][j], j == target_count ? " |\n" : "");
// 	 }
// 	 for( j = 0; j < target_count+1; j++)
// 	 {
// 	    printf("%s%d%s", j == 0 ? "| " : " ", offspring_A[j], j == target_count ? " |\n" : "");
// 	 }
// 	 for( j = 0; j < target_count+1; j++)
// 	 {
// 	    printf("%s%d%s", j == 0 ? "| " : " ", offspring_B[j], j == target_count ? " |\n" : "");
// 	 }
// 	 for( j = 0; j < target_count+1; j++)
// 	 {
// 	    printf("%s%d%s", j == 0 ? "| " : " ", population[parentB][j], j == target_count ? " |\n" : "");
// 	 }
// // sleep(30);*/
//          offspring_A[target_count] = offspring_B[target_count] = 0;
// /*        
//          for(int j = 0; j < target_count; j++)
//          {            
//             cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] << ", ParentA[" << j << "]: " << population[parentA][j]<< ", ParentB[" << j << "]: " << population[parentB][j] <<endl;
//          }
//  */   
// 	 sizeA = routeLength2(offspring_A, target_data, target_count, param.velocity);
// 	 sizeB = routeLength2(offspring_B, target_data, target_count, param.velocity);
// 	 if(sizeA < param.autonomy && sizeB < param.autonomy)
// 	 {/*printf("offspring_A & offspring_B < autonomy ");*/
// 	    if(sizeA < sizeB)
// 	    {/*printf("offspring_A selected\n");*/
// 	       offspring[i] = offspring_A;
// 	       free(offspring_B);
// 	    }
// 	    else
// 	    {/*printf("offspring_B selected\n");*/
// 	       offspring[i] = offspring_B;
// 	       free(offspring_A);
// 	    }
// 	    i++;
// 	 }
// 	 else if(sizeA < param.autonomy)
// 	 {/*printf("only offspring_A < autonomy\n");*/
// 	    offspring[i] = offspring_A;
// 	    free(offspring_B);
// 	    i++;
// 	 }
// 	 else if(sizeB < param.autonomy)
// 	 {/*printf("only offspring_B < autonomy\n");*/
// 	    offspring[i] = offspring_B;
// 	    free(offspring_A);
// 	    i++;
// 	 }
// 	 else
// 	 {/*printf("offspring_A & offspring_B > autonomy\n");*/
// 	    free(offspring_A);
// 	    free(offspring_B);
// 	 }

//       }
//       else
//       {/*printf("no crossover\n");*/
//          offspring[i] = (int*)malloc(sizeof(int)*(target_count+1));
// 	 offspring[i][0] = population[parentA][0];
//          for(int j = 1; j < target_count+1; j++)
//          {
//             offspring[i][j] = population[parentA][j];
//             //offspring[i+1] = population[parentB];
// 	    if(population[parentA][j] == 0)
// 	       break;
//          }
//          i++;
//       }
// //       i++;

//    }
// // sleep(10);
// }

// void selection_mutation_new(StartParam param, int **offspring, int target_count)
// {
//    double mutate, mutProb = param.pm;

//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       do
//       {
//          mutate = (double)(rand()%10000)/100.0f;
         
//          //cout << "mutate: " << mutate <<endl;
         
//          if(mutate < mutProb)
//          {
// 	   mutation_func(offspring[i], target_count);
// 	 }
//       }while(mutate < mutProb);
// //      sleep(5);
//    }

// }

// void fitness2(int **population, int target_count, double **target_data, double **result_fitness, StartParam param)
// {
//    double *ls, ftotal = 0, totalWeight =0, temp;
   
//    for(int i = 0; i < target_count; i++)
//    {
//       totalWeight += target_data[i][4];
//    }
   
//    result_fitness[0] = (double*)malloc(sizeof(double)*param.pop_size);
//    ls = (double*)malloc(sizeof(double)*param.pop_size);
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       ls[i] = (double)(length / steps);
//    }
   
//    for(int i = 0; i < (param.pop_size-1); i++)
//    {
//       for(int j = 0; j < (param.pop_size-(i+1)); j++)
//       {
//          if(ls[j] > ls[j+1])
//          {
//             temp = ls[j];
//             ls[j] = ls[j+1];
//             ls[j+1] = temp;
//          }

//       }
//    }
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       double weight = getWeight(population[i], target_data);
// //       result_fitness[0][i] = ( 1.0 * ( ( length / (double)steps ) * ( (double)steps / (double)target_count ) ) );
//       result_fitness[0][i]  = ( ( (ls[0] + ls[param.pop_size-1]) - ( length / (double)steps ) ) * ( weight / totalWeight) );
//    }
   
//    free(ls);

// }

// void fitness2(double **round_results, int nRounds, int target_count, double **target_data)
// {
//    double *ls, ftotal = 0, totalWeight = 0, temp;
  
//    for(int i = 0; i < target_count; i++)
//    {
//       totalWeight += target_data[i][4];
//    }
//    ls = (double*)malloc(sizeof(double)*nRounds);
//    for(int i = 0; i < nRounds; i++)
//    {
//       ls[i] = (round_results[0][i] / round_results[1][i]);
//    }
   
//    for(int i = 0; i < (nRounds-1); i++)
//    {
//       for(int j = 0; j < (nRounds-(i+1)); j++)
//       {
//          if(ls[j] > ls[j+1])
//          {
//             temp = ls[j];
//             ls[j] = ls[j+1];
//             ls[j+1] = temp;
//          }

//       }
//    }
//    for(int i = 0; i < nRounds; i++)
//    {
//       round_results[3][i]  = ( ( (ls[0] + ls[nRounds-1]) - ( round_results[0][i] / round_results[1][i] ) ) * ( round_results[2][i] / totalWeight ) );
//    }
   
//    free(ls);

// }

// void fitness3(int **population, int target_count, double **target_data, double **result_fitness, StartParam param)
// {
//    double *ls, ftotal = 0, totalWeight =0, temp;
   
//    for(int i = 0; i < target_count; i++)
//    {
//       totalWeight += target_data[i][4];
//    }
   
//    result_fitness[0] = (double*)malloc(sizeof(double)*param.pop_size);
// //    ls = (double*)malloc(sizeof(double)*param.pop_size);
// //    for(int i = 0; i < param.pop_size; i++)
// //    {
// //       double length = routeLength2(population[i], target_data, target_count, param.velocity);
// //       int steps = getRouteSteps(population[i]);
// //       ls[i] = (double)(length / steps);
// //    }
// //    
// //    for(int i = 0; i < (param.pop_size-1); i++)
// //    {
// //       for(int j = 0; j < (param.pop_size-(i+1)); j++)
// //       {
// //          if(ls[j] > ls[j+1])
// //          {
// //             temp = ls[j];
// //             ls[j] = ls[j+1];
// //             ls[j+1] = temp;
// //          }
// // 
// //       }
// //    }
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       double weight = getWeight(population[i], target_data);
      
//       result_fitness[0][i]  = ( (1 - ( length / param.autonomy ) ) + (steps / target_count) + (weight / totalWeight) );
      
// //       result_fitness[0][i] = ( 1.0 * ( ( length / (double)steps ) * ( (double)steps / (double)target_count ) ) );
// //       result_fitness[0][i]  = ( ( (ls[0] + ls[param.pop_size-1]) - ( length / (double)steps ) ) * ( weight / totalWeight) );
//    }
   
// //    free(ls);

// }

// void fitness4(int **population, int target_count, double **target_data, double **result_fitness, StartParam param)
// {
//    double *ls, ftotal = 0, totalWeight =0, temp;
   
//    for(int i = 0; i < target_count; i++)
//    {
//       totalWeight += target_data[i][4];
//    }
   
//    result_fitness[0] = (double*)malloc(sizeof(double)*param.pop_size);
// //    ls = (double*)malloc(sizeof(double)*param.pop_size);
// //    for(int i = 0; i < param.pop_size; i++)
// //    {
// //       double length = routeLength2(population[i], target_data, target_count, param.velocity);
// //       int steps = getRouteSteps(population[i]);
// //       ls[i] = (double)(length / steps);
// //    }
// //    
// //    for(int i = 0; i < (param.pop_size-1); i++)
// //    {
// //       for(int j = 0; j < (param.pop_size-(i+1)); j++)
// //       {
// //          if(ls[j] > ls[j+1])
// //          {
// //             temp = ls[j];
// //             ls[j] = ls[j+1];
// //             ls[j+1] = temp;
// //          }
// // 
// //       }
// //    }
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       double weight = getWeight(population[i], target_data);
      
//       result_fitness[0][i]  = ( (1 - (length / param.autonomy) ) + (steps / target_count) + (weight / totalWeight) + ( ((weight * target_count) / (steps * totalWeight)*0.5) ) );
      
// //       result_fitness[0][i] = ( 1.0 * ( ( length / (double)steps ) * ( (double)steps / (double)target_count ) ) );
// //       result_fitness[0][i]  = ( ( (ls[0] + ls[param.pop_size-1]) - ( length / (double)steps ) ) * ( weight / totalWeight) );
//    }
   
// //    free(ls);

// }

// void fitness5(int **population, int target_count, double **target_data, double **result_fitness, StartParam param)
// {
//    double *ls, ftotal = 0, totalWeight =0, temp;
   
//    for(int i = 0; i < target_count; i++)
//    {
//       totalWeight += target_data[i][4];
//    }
   
//    result_fitness[0] = (double*)malloc(sizeof(double)*param.pop_size);
//    ls = (double*)malloc(sizeof(double)*param.pop_size);
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       ls[i] = (double)(length / steps);
//    }
   
//    for(int i = 0; i < (param.pop_size-1); i++)
//    {
//       for(int j = 0; j < (param.pop_size-(i+1)); j++)
//       {
//          if(ls[j] > ls[j+1])
//          {
//             temp = ls[j];
//             ls[j] = ls[j+1];
//             ls[j+1] = temp;
//          }

//       }
//    }
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, param.velocity);
//       int steps = getRouteSteps(population[i]);
//       double weight = getWeight(population[i], target_data);
      
//       result_fitness[0][i]  = ( (1 - (ls[i] / ls[param.pop_size-1]) ) + (steps / target_count) + (weight / totalWeight) + ( ((weight * target_count) / (steps * totalWeight))*ALPHA ) );
      
// //       result_fitness[0][i] = ( 1.0 * ( ( length / (double)steps ) * ( (double)steps / (double)target_count ) ) );
// //       result_fitness[0][i]  = ( ( (ls[0] + ls[param.pop_size-1]) - ( length / (double)steps ) ) * ( weight / totalWeight) );
//    }
   
// //    free(ls);

// }

//===================================================================================================================================================================================



// /*
// double routeLength(int *individual, double **target_data, const int target_count, const double velocity)   /* DEPRECATED !!*/
// {
//    double length = 0;
//    double *edge_time, **route_data, *h_data;
//    
//    edge_time = (double*)malloc(sizeof(double)*target_count);
//    
//    route_data = (double**)malloc(sizeof(double*)*target_count);
//    for(int i = 0; i < target_count; i++)
//    {
//       route_data[i] = (double*)malloc(sizeof(double)*2);
//    }
// 
//    for(int i = 0; i < target_count; i++)
//    {
//       route_data[i][0] = target_data[i][0];
//       route_data[i][1] = target_data[i][1];
//    }
//    
//    h_data = (double*)malloc(sizeof(double)*3);
//    h_data[0] = route_data[0][0];
//    h_data[1] = route_data[0][1];
//    h_data[2] = velocity;
// //    printf("current line %d - h_data[2] = %.2lf\n", __LINE__, h_data[2]);
//    
//    for(int i = 1; i < target_count; i++)
//    {
//       edge_time[i-1] = getInterceptTime(route_data[individual[i]], target_data[individual[i]][3], target_data[individual[i]][2], h_data);
//       for(int j = 0; j < target_count; j++)
//       {
//          double vt[2];
//          getVt(target_data[j][3], target_data[j][2], vt);
// 
//          route_data[j][0] += edge_time[i-1] * vt[0];
//          route_data[j][1] += edge_time[i-1] * vt[1];
// 
//       }
//       h_data[0] = route_data[individual[i]][0];
//       h_data[1] = route_data[individual[i]][1];
//    }
//    edge_time[target_count-1] = getInterceptTime(route_data[0], target_data[0][3], target_data[0][2], h_data);
//    length = eval_tour(edge_time, h_data, target_count);
//    
//    free(h_data);
//    free(edge_time);
//    for(int i = 0; i < target_count; i++)
//    {
//       free(route_data[i]);
//    }
//    free(route_data);
// 
//    return length;
// }
// 
// int* generateIndividual(int target_count)   /* DEPRECATED !!*/
// {
//    int *cromosomo, *temp;
// 
//    cromosomo = (int*)malloc(sizeof(int)*(target_count+1));
//    temp = (int*)malloc(sizeof(int)*target_count-1);
// 
//    for(int i = 0; i < target_count-1; i++)
//    {
//       temp[i]=i+1;
//    }
// 
//    int aux = target_count-1;
//    cromosomo[target_count] = cromosomo[0] = 0;
//    for(int i = 1; i < target_count; i++)
//    {
//       int position = rand()%aux;
// 
//       cromosomo[i] = temp[position];
// 
//       for(int j = position; j < aux-1; j++)
//       {
//          temp[j] = temp[j+1];
//       }
//       aux--;
//    }
// 
//    free(temp);
//    return cromosomo;                          
// }
// 
// int* generateIndividual_2(StartParam param, int target_count, double **target_data)   /* DEPRECATED !!*/
// {
//    int *cromosomo, i, j, k;
//    bool *visited;
//    double *edge_time, **route_data, *t_prob, *strength, x;
//    double *h_data;
// // printf("current line %d\n", __LINE__);
//    t_prob = (double*)malloc(sizeof(double)*target_count);
// // printf("current line %d\n", __LINE__);
//    strength = (double*)malloc(sizeof(double)*(target_count+1));
// // printf("current line %d\n", __LINE__);
//    edge_time = (double*)malloc(sizeof(double)*target_count);
// // printf("current line %d\n", __LINE__);
//    route_data = (double**)malloc(sizeof(double*)*target_count);
// // printf("current line %d\n", __LINE__);
//    for(int i = 0; i < target_count; i++)
//    {
//       route_data[i] = (double*)malloc(sizeof(double)*2);
//    }
//    for(i = 0; i < target_count; i++)
//    {
// // printf("current line %d\n", __LINE__);
//       route_data[i][0] = target_data[i][0];
//       route_data[i][1] = target_data[i][1];
// // printf("current line %d\n", __LINE__);
//    }
//    
//    h_data = (double*)malloc(sizeof(double)*3);
//    h_data[0] = route_data[0][0];
//    h_data[1] = route_data[0][1];
//    h_data[2] = param.velocity;
// //    printf("current line %d - h_data[2] = %.2lf\n", __LINE__, h_data[2]);
// 
//    cromosomo = (int*)malloc(sizeof(int)*(target_count+1));
//    visited = (bool*)malloc(sizeof(bool)*target_count);
// // printf("current line %d\n", __LINE__);
// /* Initialise tour */
//    for (i=0; i<target_count; i++)
//    {
//       visited[i] = false;
//       cromosomo[i] = -1;
//    }
// // printf("current line %d\n", __LINE__);
//    /* Tour always starts at position 0 */
//    cromosomo[target_count] = cromosomo[0] = 0;
//    visited[0] = true;
//    h_data[0] = target_data[0][0];
//    h_data[1] = target_data[0][1];
// // printf("current line %d\n", __LINE__);  
//    /* j marks where we are in constructing the tour, 
//       k is the next node to visit */
//    for (j=1; j<target_count; j++)
//    {
// // printf("current line %d\n", __LINE__);
//    /* Get transition probabilities - cannot choose a 
//       node that has previously been used */
//       for (i=0; i<target_count; i++)
//       {
// // printf("current line %d\n", __LINE__);
//          t_prob[i] = 0.0;
//          if (visited[i] == false)
//          {
// // printf("current line %d\n", __LINE__);
//             t_prob[i] = 1/pow((h_data[2]*getInterceptTime(route_data[i], target_data[i][3], target_data[i][2], h_data)), 2);
//          }
//          else
//          {
// // printf("current line %d\n", __LINE__);
//             t_prob[i] = 0.0;
//          }
//       }
// // printf("current line %d - %dj\n", __LINE__, j);
//       /* Roulette wheel selection - equivalent to probability-
//          based selection of next city. The index of the next 
//          city on the tour is given in k */
//       strength[0] = 0;
// // printf("current line %d - %dj\n", __LINE__, j);
//       for (i=0; i<target_count; i++)
//       {
// // printf("current line %d - %dj - %di\n", __LINE__, j, i);
//          strength[i+1] = t_prob[i] + strength[i];
// // printf("current line %d - %dj - %di\n", __LINE__, j, i);
//       }
// // printf("current line %d - %dj\n", __LINE__, j);
//       long _rnd = rand();
// // printf("current line %d - %dj\n", __LINE__, j);
//       if (_rnd == 0)
//          _rnd++;
// // printf("current line %d - %dj\n", __LINE__, j);
//       x = strength[target_count] * (double)_rnd / RAND_MAX; 
// // printf("current line %d - %dj\n", __LINE__, j);
//       k = 0;
//       while (!((strength[k] <= x) && (x <= strength[k+1])))
//       {
// // printf("current line %d - %dj - %dk\n", __LINE__, j, k);
//          k++;
// // printf("current line %d - %dj - %dk\n", __LINE__, j, k);
//       }
// 
// // printf("current line %d - %dj\n", __LINE__, j);
//       cromosomo[j] = k;
//       visited[k] = true;
// // printf("current line %d - %dj\n", __LINE__, j);
//       edge_time[j-1] = getInterceptTime(route_data[k], target_data[k][3], target_data[k][2], h_data);
// // printf("current line %d - %dj\n", __LINE__, j);
//       for(i = 0; i < target_count; i++)
//       {
// // printf("current line %d - %dj - %di\n", __LINE__, j, i);
//          double vt[2];
//          getVt(target_data[i][3], target_data[i][2], vt);
// 
//          route_data[i][0] += edge_time[j-1] * vt[0];
//          route_data[i][1] += edge_time[j-1] * vt[1];
//       }
// // printf("current line %d - %dj - %dk\n", __LINE__, j, k);
//       h_data[0] = route_data[k][0];
//       h_data[1] = route_data[k][1];
// // printf("current line %d - %dj\n", __LINE__, j);
//       
//    }
// // printf("current line %d\n", __LINE__);
// //    cout<<"New population Individual ";
// //    for( j = 0; j < target_count; j++)
// //    {
// //       printf("%s%d%s", j == 0 ? "| " : " ", cromosomo[j], j == target_count-1 ? " |\n" : "");
// //    }
// //    
// //    free(h_data);
// // // printf("current line %d\n", __LINE__);
// //    double length = routeLength(cromosomo);
// // // printf("current line %d\n", __LINE__);
// //    cout << "total distance: " << length <<endl;
// //    
// //    sleep(10);
// 
//    free(t_prob);
//    free(strength);
//    free(visited);
//    free(edge_time);
//    for(int i = 0; i < target_count; i++)
//    {
//       free(route_data[i]);
//    }
//    free(route_data);
//    free(h_data);
//    return cromosomo;                          
// }*/


// void sortPopulation(int **population, double **target_data, const int target_count, StartParam param)   /* DEPRECATED !!*/
// {
//    double *length, temp;
//    int *aux;
//    
//    length = (double*)malloc(sizeof(double)*param.pop_size);
//    
//    for(int i = 0; i < param.pop_size; i++)
//    {
// 
//       length[i] = routeLength2(population[i], target_data, target_count, param.velocity);
// 
//    }
// 
// 
//    for(int i = 0; i < (param.pop_size-1); i++)
//    {
//       for(int j = 0; j < (param.pop_size-(i+1)); j++)
//       {
//          if(length[j] > length[j+1])
//          {
//             temp = length[j];
//             length[j] = length[j+1];
//             length[j+1] = temp;
//             aux = population[j];
//             population[j] = population[j+1];
//             population[j+1] = aux;
//          }
// 
//       }
//    }
// 
//    free(length);
// //   cout << "sortPopulation checkpoint 5" <<endl;
// }

// void selection_crossover(StartParam param, int **population, int **offspring, int target_count, double **target_data, double *result_fitness)   /* DEPRECATED !!*/
// {
//    double crosProb = param.pc;
//    int crosPoint, parentA, parentB;
//    int *offspring_A, *offspring_B; 
//    int index = 0;
//    
//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       /* select parents */
//       double temp1 = ((double)((rand()%1000)))/10.0f;
//       double aux1 = 0.0f;
//       for(int j = 0; j < param.pop_size; j++)
//       {
//          aux1 += result_fitness[j];
//          parentA = j;
//          if(aux1 > temp1)
//          {
//             break;
//          }
//       }
// //      cout << "selection_crossover i: " << i << ", aux1: " << aux1 << ", temp1: " << temp1 << ", parentA: " << parentA <<endl;
//       do
//       {
//          double temp2 = ((double)((rand()%1000)))/10.0f;
//          double aux2 = 0.0f;
//          for(int j = 0; j < param.pop_size; j++)
//          {
//             aux2 += result_fitness[j];
//             parentB = j;
//             if(aux2 > temp2)
//             {
//                break;
//             }
//          }
//       }while(parentA == parentB);    // ensures ParentA is Different from ParentB
// //      cout << "selection_crossover i: " << i << ", aux2: " << aux2 << ", temp2: " << temp2 << ", parentB: " << parentB <<endl;
//       
//       /* crossover */
//       double crosAux = (double)(rand()%10000)/100.0f;
// //      cout << "i = " << i << "crosAux = " << crosAux <<endl;
//       if(crosAux <= crosProb)
//       {
// //         cout << "crosPoint: " << crosPoint <<endl;
//          offspring_A = (int*)malloc(sizeof(int)*(target_count+1));
//          offspring_B = (int*)malloc(sizeof(int)*(target_count+1));
//          
//          crosPoint = (rand()%(target_count-1))+1;
//          
// //         doAgain:
//          
//          for(int j = 0; j < crosPoint; j++)
//          {
//             offspring_A[j] = population[parentA][j];
//             offspring_B[j] = population[parentB][j];
//             
//             //cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//          }
//          
//          int index = crosPoint;
//          
//          for(int j = 0; j < target_count; j++)
//          {
//             int flag = 0;
//             
//             for(int k = 0; k < index; k++)
//             {
//                if(population[parentB][j] == offspring_A[k])
//                {
//                   flag++;
//                }
//                
//             }
//             if(!flag)
//             {
//                if(index < target_count)
//                {
//                   offspring_A[index] = population[parentB][j];
//                   index++;
//                }
//             }
//             
//          }
//          
//          index = crosPoint;
//          for(int j = 0; j < target_count; j++)
//          {
//             int flag = 0;
//             for(int k = 0; k < index; k++)
//             {
//                if(population[parentA][j] == offspring_B[k])
//                {
//                   flag++;
//                }
//             }
//             if(!flag)
//             {
//                if(index < target_count)
//                {
//                   offspring_B[index] = population[parentA][j];
//                   index++;
//                }
//             }
//          }
//          offspring_A[target_count] = offspring_B[target_count] = 0;
// /*         
//          for(int j = 0; j < target_count; j++)
//          {            
//             cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] << ", ParentA[" << j << "]: " << population[parentA][j]<< ", ParentB[" << j << "]: 
// " << population[parentB][j] <<endl;
//          }
// */       
//          if(routeLength(offspring_A, target_data, target_count, param.velocity) < routeLength(offspring_B, target_data, target_count, param.velocity))
//          {            
//             offspring[i] = offspring_A;
//             free(offspring_B);
//          }
//          else
//          {
//             offspring[i] = offspring_B;
//             free(offspring_A);
//          }
//       
//       }
//       else
//       {
//          offspring[i] = (int*)malloc(sizeof(int)*(target_count+1));
//          for(int j = 0; j < target_count+1; j++)
//          {
//             offspring[i][j] = population[parentA][j];
//             //offspring[i+1] = population[parentB];
//          }
//       }
//       
//    }
//    
// }
// 
// void selection_crossover_2point(StartParam param, int **population, int **offspring, int target_count, double **target_data, double *result_fitness)    /* DEPRECATED !!*/
// {
//    double crosProb = param.pc;
//    int crossPoint_1, crossPoint_2, parentA, parentB;
//    int *offspring_A, *offspring_B; 
//    int index = 0;
//    
//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       /* select parents */
//       double temp1 = ((double)((rand()%1000)))/10.0f;
//       double aux1 = 0.0f;
//       for(int j = 0; j < param.pop_size; j++)
//       {
//          aux1 += result_fitness[j];
//          parentA = j;
//          if(aux1 > temp1)
//          {
//             break;
//          }
//       }
// //      cout << "selection_crossover i: " << i << ", aux1: " << aux1 << ", temp1: " << temp1 << ", parentA: " << parentA <<endl;
//       do
//       {
//          double temp2 = ((double)((rand()%1000)))/10.0f;
//          double aux2 = 0.0f;
//          for(int j = 0; j < param.pop_size; j++)
//          {
//             aux2 += result_fitness[j];
//             parentB = j;
//             if(aux2 > temp2)
//             {
//                break;
//             }
//          }
//       }while(parentA == parentB);    // ensures ParentA is Different from ParentB
// //      cout << "selection_crossover i: " << i << ", aux2: " << aux2 << ", temp2: " << temp2 << ", parentB: " << parentB <<endl;
//       
//       /* crossover */
//       double crosAux = (double)(rand()%10000)/100.0f;
// //      cout << "i = " << i << "crosAux = " << crosAux <<endl;
//       if(crosAux <= crosProb)
//       {
// //         cout << "crosPoint: " << crosPoint <<endl;
//          offspring_A = (int*)malloc(sizeof(int)*(target_count+1));
//          offspring_B = (int*)malloc(sizeof(int)*(target_count+1));
//          
//          crossPoint_1 = (rand()%(target_count-1))+1;
//          crossPoint_2 = (rand()%(target_count-crossPoint_1))+crossPoint_1;
// //          printf("crossPoint_1 = %d, crossPoint_2 = %d\n", crossPoint_1, crossPoint_2);
// //         doAgain:
//          
//          for(int j = crossPoint_1; j <= crossPoint_2; j++)
//          {
//             offspring_A[j] = population[parentB][j];
//             offspring_B[j] = population[parentA][j];
//             
// //             cout << "offspring_A[" << j << "]: " << offspring_A[j] << ", offspring_B[" << j << "] " << offspring_B[j] <<endl;
//          }
//          
//          int index = 0;
//          
//          for(int j = 0; j < target_count; j++)
//          {
//             int flag = 0;
//          
//             for(int k = crossPoint_1; k <= crossPoint_2; k++)
//             {
//                if(population[parentA][j] == offspring_A[k])
//                {
//                   flag++;
//                }
//                
//             }
//             if(!flag)
//             {
//                if((index < crossPoint_1) || (index > crossPoint_2))
//                {
//                   offspring_A[index] = population[parentA][j];
//                   index++;
//                }
//                else
//                {
//                   while(index <= crossPoint_2)
//                   {
//                      index++;
//                   }
//                   offspring_A[index] = population[parentA][j];
//                   index++;
//                }
//             }
//             
//          }
//          
//          index = 0;
//          
//          for(int j = 0; j < target_count; j++)
//          {
//             int flag = 0;
//          
//             for(int k = crossPoint_1; k <= crossPoint_2; k++)
//             {
//                if(population[parentB][j] == offspring_B[k])
//                {
//                   flag++;
//                }
//                
//             }
//             if(!flag)
//             {
//                if((index < crossPoint_1) || (index > crossPoint_2))
//                {
//                   offspring_B[index] = population[parentB][j];
//                   index++;
//                }
//                else
//                {
//                   while(index <= crossPoint_2)
//                   {
//                      index++;
//                   }
//                   offspring_B[index] = population[parentB][j];
//                   index++;
//                }
//             }
//          }
//          offspring_A[target_count] = offspring_B[target_count] = 0;
// 
//          
//          if(routeLength(offspring_A, target_data, target_count, param.velocity) < routeLength(offspring_B, target_data, target_count, param.velocity))
//          {
//             offspring[i] = offspring_A;
//             free(offspring_B);
//          }
//          else
//          {
//             offspring[i] = offspring_B;
//             free(offspring_A);
//          }
//       
//       }
//       else
//       {
//          offspring[i] = (int*)malloc(sizeof(int)*(target_count+1));
//          for(int j = 0; j < target_count+1; j++)
//          {
//             offspring[i][j] = population[parentA][j];
//             //offspring[i+1] = population[parentB];
//          }
//       }
//       
//    }
//    
// }

// void selection_mutation_1Gen(StartParam param, int **offspring, int target_count)   /* DEPRECATED !!*/
// {
//    double mutate, mutProb = param.pm;
//    int mGen1, mGen2;
//    
//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       do
//       {
//          mutate = (double)(rand()%10000)/100.0f;
//          
//          //cout << "mutate: " << mutate <<endl;
//          
//          if(mutate < mutProb)
//          {
//             
//             mGen1 = (rand()%(target_count-1))+1;
//             
//             if(mGen1 == target_count-1)
//             {
//                mGen2 = mGen1-1;
//             }
//             else
//             {
//                mGen2 = mGen1+1;
//             }
//             
//             int temp = offspring[i][mGen1];
//             offspring[i][mGen1] = offspring[i][mGen2];
//             offspring[i][mGen2] = temp;
//                
//             
//          }
//       }while(mutate < mutProb);
//       
//    }
//    
// }
// 
// void selection_mutation_2Gen(StartParam param, int **offspring, int target_count)   /* DEPRECATED !!*/
// {
//    double mutate, mutProb = param.pm;
//    int mGen1, mGen2;
//    
//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       do
//       {
//          mutate = (double)(rand()%10000)/100.0f;
//          
//          //cout << "mutate: " << mutate <<endl;
//          
//          if(mutate < mutProb)
//          {
// 
//             mGen1 = (rand()%(target_count-1))+1;
//             do
//             {
//                mGen2 = (rand()%(target_count-1))+1;
//                //cout << "mGen1: " << mGen1 << " mGen2: " << mGen2 <<endl;
//             }while(mGen1 == mGen2);
//             
//             int temp = offspring[i][mGen1];
//             offspring[i][mGen1] = offspring[i][mGen2];
//             offspring[i][mGen2] = temp;
//                
//          }
//       }while(mutate < mutProb);
//    }
//    
// }
// 
// void selection_mutation_C(StartParam param, int **offspring, int target_count)   /* DEPRECATED !!*/
// {
//    double mutate, mutProb = param.pm;
//    int mGen1, mGen2;
//    
//    for(int i = 0; i < param.pop_size-param.elit; i++)
//    {
//       for(int j = 1; j < target_count; j++)
//       {
// 
//          mutate = (double)(rand()%10000)/100.0f;
//          
//          //cout << "mutate: " << mutate <<endl;
//          
//          if(mutate < mutProb)
//          {
//             
//             //mGen1 = (rand()%(target_count-1))+1;
//             
//             if(j == target_count-1)
//             {
//                //mGen2 = mGen1-1;
//                mGen1 = offspring[i][j];
//                offspring[i][j] = offspring[i][j-1];
//                offspring[i][j-1] = mGen1;
//             }
//             else
//             {
//                //mGen2 = mGen1+1;
//                mGen1 = offspring[i][j];
//                offspring[i][j] = offspring[i][j+1];
//                offspring[i][j+1] = mGen1;
//             }
//             /*
//             int temp = offspring[i][mGen1];
//             offspring[i][mGen1] = offspring[i][mGen2];
//             offspring[i][mGen2] = temp;
//                */
//             
//          }
//       }
//    }
//    
// }

// void fitness(int **population, int target_count, double **target_data, double **result_fitness, StartParam param)   /* DEPRECATED !!*/
// {
//    double fb, fk, ftotal = 0, totalPercent =0;
//    
//    result_fitness[0] = (double*)malloc(sizeof(double)*param.pop_size);
//    
//    fb = routeLength2(population[0], target_data, target_count, param.velocity);
//    fk = routeLength2(population[param.pop_size-1], target_data, target_count, param.velocity);
//    
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double temp = routeLength2(population[i], target_data, target_count, param.velocity);
//       result_fitness[0][i] = fb + fk - temp;
//       ftotal = ftotal + result_fitness[0][i];
//       //cout << "result_fitness[" << i << "] = " << result_fitness[i] <<endl;
//    }
//    
//    for(int i = 0; i < param.pop_size; i++)
//    {
//       double temp = routeLength2(population[i], target_data, target_count, param.velocity);
//       result_fitness[0][i] = (result_fitness[0][i]*100)/ftotal;
//       //cout << "result_fitness[" << i << "] = " << result_fitness[i] << "%" <<endl;
//       totalPercent += result_fitness[0][i];
//    }  
//    //cout << "totalPercent" << totalPercent <<endl;
//    
// }


