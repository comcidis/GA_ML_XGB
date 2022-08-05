#include "../includes/io_fun.h"
// #include "../includes/ga-dl_fun.h"
//#include "../commons/tspcommon.h"
//#include "../tsp_ga/tspgafun.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int dataRead(const char* inFileName, double *accuracy, StartParam param) /* DEPRECATED !!*/
{
   int i = 0;
   char aux[24];
   double acc = 0;

   FILE *inPtr = fopen(inFileName, "r");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   
   fscanf(inPtr,"%s %lf", aux, &acc);
   
   while((!feof(inPtr)) && (i < param.pop_size))
   {
      accuracy[i] = acc;
      fscanf(inPtr,"%s %lf", aux, &acc);
      i++;
   }
   
  
   
  
   fclose(inPtr);

   return 0;
}

int getAccuracy(const char* inFileName, double *accuracy, StartParam param, const int generation)
{
   int i = 0;
   char aux[24];
   double acc = 0;
   if(generation)
   {
      i = param.elit;
   }

   FILE *inPtr = fopen(inFileName, "r");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   
   fscanf(inPtr,"%s %lf", aux, &acc);
   
   while((!feof(inPtr)) && (i < param.pop_size))
   {
      accuracy[i] = acc;
      fscanf(inPtr,"%s %lf", aux, &acc);
      i++;
   }
   
  
   
  
   fclose(inPtr);

   return 0;
}

int getAccuracy(const char* inFileName, double *accuracy, StartParam param)
{
   int i = 0;
   char aux[24];
   double acc = 0;

   FILE *inPtr = fopen(inFileName, "r");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   
   fscanf(inPtr,"%s %lf", aux, &acc);
   
   while((!feof(inPtr)) && (i < param.pop_size))
   {
      accuracy[i] = acc;
      fscanf(inPtr,"%s %lf", aux, &acc);
      i++;
   }
    
   fclose(inPtr);

   return 0;
}

int getTestResult(const char* inFileName, double *energy, double *time)
{
   FILE *inPtr;
   char *token, buffer[256], auxc;
   int aux1, aux2;
   int i = 0, j;
   //double energy, time;

   inPtr = fopen(inFileName, "r");
   if(inPtr == NULL)
   {
      printf("Failed to open input file");
      return 1;
   }

   fgets(buffer, sizeof(buffer), inPtr);
   fgets(buffer, sizeof(buffer), inPtr);
   fgets(buffer, sizeof(buffer), inPtr);
   fgets(buffer, sizeof(buffer), inPtr);

   do
   {
      if(buffer[i] == ',')
      {
            j = i;
            do
            {
                     buffer[j] = buffer[j+1];
                     j++;

            }while(buffer[j] != 'J');
      }
      i++;
   }while(buffer[i] != 'J');

   printf("token = %s\n", buffer);


   sscanf(buffer,"%lf", energy);

   fscanf(inPtr, "%lf", time);

   printf("energy = %lf Joules, time = %.9lf\n", energy[0], time[0]);

   return 0;
}

int configParam(const char* configFileName, StartParam *param)
{
   const int maxPram = 9;
   int paramCount = 0;
   char pName[33];
   FILE *inPtr = fopen(configFileName, "r");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", configFileName);
      exit(1);
   }

   fscanf(inPtr, "%s %d", pName, &param->pop_size);
   fscanf(inPtr, "%s %d", pName, &param->elit);
   fscanf(inPtr, "%s %d", pName, &param->fitnessType);
   fscanf(inPtr, "%s %lf", pName, &param->pc);
   fscanf(inPtr, "%s %lf", pName, &param->pm);
   fscanf(inPtr, "%s %d", pName, &param->max_gen);
   fscanf(inPtr, "%s %lf", pName, &param->wScore);
   fscanf(inPtr, "%s %lf", pName, &param->wTime);
   fscanf(inPtr, "%s %lf", pName, &param->wEnergy);
   
/*
   param->pop_size = 30;
   //       param->initType = 1;
   param->elit = 2;
   param->fitnessType = 2;
   //       param.crossoverType = 3;
   //       param.mutationType = 4;
   param->pc = 80.0;
   param->pm = 10.0;
   param->max_gen = 30;
   param->wScore = 1;
   param->wTime = 1;
   param->wEnergy = 1;
*/
   fclose(inPtr);
   return 0;

}



//---------------------------------------------------/* DEPRECATED !!*/----------------------------------------------------------------------

// void dataRead(const char* inFileName, int *target_count, double ***target_data)
// {
//   int data_count = 4;
//   double solutions = 0;
//   double velocities = 0;
//    FILE *inPtr = fopen(inFileName, "r");
//    if(inPtr == NULL)
//    {
//       printf("Couldn\'t open file %s\n", inFileName);
//       exit(1);
//    }
   
//    fscanf(inPtr, "%d %d", target_count, &data_count);
   
//    target_data[0] = (double**)malloc(sizeof(double*)*target_count[0]);
   
  
//    for(int i = 0; i < target_count[0]; i++)
//    {
//       target_data[0][i] = (double*)malloc(sizeof(double)*data_count);
//    }
  
//    int index = 0;
//    while((!feof(inPtr)) && (index < target_count[0]))
//    {
//       for(int j = 0; j < data_count; j++)
//       {
//          fscanf(inPtr, "%lf", &target_data[0][index][j]); 
//       }
//       index++;
//    }
  
//    fclose(inPtr);

// }

// void printRound(int i)
// {
//   printf("Round %d\n", i+1);
// }

// void show_population(int **population, const int pop_size, const int target_count)
// {
//    for(int i = 0; i < pop_size/10; i++)
//    {
//       //double length = routeLength(population[i]);
//       cout<<"New population Individual to "<<i<<" ";
//       printf("%s%d", "| ", population[i][0]);
//       for(int j = 1; j < target_count+1; j++)
//       {
//          printf("%s%d"," ", population[i][j]);
// 	 if(population[i][j] == 0)
// 	    break;
//       }
//       printf(" |\n");
//       //cout << "total distance: " << length <<endl;
//    }
//       cout<<endl;
// }

// void show_population(int **population, const int pop_size, const int target_count, double *result_fitness)
// {
//    for(int i = 0; i < pop_size; i++)
//    {
//       //double length = routeLength(population[i]);
//       cout<<"New population Individual to "<<i<<" ";
//       printf("%s%d", "| ", population[i][0]);
//       for(int j = 1; j < target_count+1; j++)
//       {
//          printf("%s%d"," ", population[i][j]);
// 	 if(population[i][j] == 0)
// 	    break;
//       }
//       printf(" | fitness = %.2lf\n", result_fitness[i]);
//       //cout << "total distance: " << length <<endl;
//    }
//       cout<<endl;
// }

// void show_population(int **population, const int pop_size, const int target_count, double *result_fitness, const double velocity, double **target_data)
// {
//    for(int i = 0; i < pop_size/10; i++)
//    {
//       double length = routeLength2(population[i], target_data, target_count, velocity);
//       int targets = getRouteSteps(population[i]);
//       cout<<"New population Individual to "<<i<<" ";
//       printf("%s%d", "| ", population[i][0]);
//       for(int j = 1; j < target_count+1; j++)
//       {
//          printf("%s%d"," ", population[i][j]);
// 	 if(population[i][j] == 0)
// 	    break;
//       }
//       printf(" | fitness = %.2lf\n", result_fitness[i]);
//       printf("length = %.3lf, targets = %d\n", length, targets);
//       //cout << "total distance: " << length <<endl;
//    }
//       cout<<endl;
// }

// void show_best_solution(int *population, const int target_count, double length)
// {
// //    double length = routeLength(population[0], target_data, target_count, velocity);
//    printf("Best Individual found\n");
//    printf("%s%d", "| ", population[0]);
//    for(int j = 1; j < target_count+1; j++)
//    {
//       printf("%s%d"," ", population[j]);
//       if(population[j] == 0)
// 	 break;
//    }
//    printf(" |\n");
// //    for(int j = 0; j < target_count+1; j++)
// //    {
// //       printf("%s%d%s", j == 0 ? "| " : " ", population[j], j == target_count ? " |\n" : "");
// //    }
// //    //cout << "total distance: " << length <<endl;
//    printf("total distance: %lf\n", length);
// }

// void show_best_solution(int *population, const int target_count, double **target_data, double length)
// {
// //    double length = routeLength(population[0], target_data, target_count, velocity);
//    printf("Best Individual found\n");
//    printf("%s%d", "| ", population[0]);
//    for(int j = 1; j < target_count+1; j++)
//    {
//       printf("%s%d"," ", population[j]);
//       if(population[j] == 0)
// 	 break;
//    }
//    printf(" |\n");
   
//    printf("%s%.1lf", "| ", target_data[population[0]][4]);
//    for(int j = 1; j < target_count+1; j++)
//    {
//       printf("%s%.1lf"," ", target_data[population[j]][4]);
//       if(population[j] == 0)
// 	 break;
//    }
//    printf(" |\n");
// //    for(int j = 0; j < target_count+1; j++)
// //    {
// //       printf("%s%d%s", j == 0 ? "| " : " ", population[j], j == target_count ? " |\n" : "");
// //    }
// //    //cout << "total distance: " << length <<endl;
//    printf("total distance: %lf\n", length);
// }

// void show_individual(int *individual, const int target_count, double length)
// {
// //    double length = routeLength(population[0], target_data, target_count, velocity);
//    printf("New Individual\n");
//    for(int j = 0; j < target_count+1; j++)
//    {
//       printf("%s%d", j == 0 ? "| " : " ", individual[j]);
      
//       if((individual[j] == 0) && (j > 0) && (j < target_count))
//       {
// 	 break;
//       }
//    }
// 	 printf(" |\n");
//    //cout << "total distance: " << length <<endl;
//    printf("total distance: %lf\n", length);
// }