#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include "../includes/ga-dl_fun.h"
#include "../includes/io_fun.h"
//#include <python3.8/Python.h>

using namespace std;

//variaveis globais

FILE *inPtr, *outPtr, *configFilePtr;
char modified_date[14] = {"Jan 16th 2022"}, modified_time[16] = {"07:27 AM GMT -3"};
char ver[17] = {"v.1.1.0"};


int argc1;
char **argv1;
int generation = 0;
bool simple = false;
int nRounds = 1;

double **round_results;


const int length = 22; 

//variaveis globais GA
StartParam param;
int **population, *individual;


int **offspring;

double *result_fitness;


void startUp(int argc, char **argv);
void helpFun();
void getDate();
void version();

void GA_Solver();
void XGBR_Solver();
void XGBC_Solver();

void new_session();
void reset();

//int startup(int argc, char** argv);

int main(int argc, char** argv)
{
   srand(time(NULL));
   // char inFileName[24] = {"accuracy.dat"};
   // int acc = 0;
   // int err = 0;
   // double *accuracy;
   // int parentA, parentB;
   // int *offspring_A, *offspring_B;

   // printf("teste %d\n", acc);
   // inPtr = fopen(inFileName, "w");
   // if(inPtr == NULL)
   // {
   //    printf("Couldn\'t open file %s\n", inFileName);
   //    exit(1);
   // }
   // fclose(inPtr);

   startUp(argc, argv);

   //GA_Solver();
   //XGBR_Solver();
   XGBC_Solver();

   // double time, energy;
   // char command[256];
   // int max_depth = 3, n_jobs = 12, n_estimators = 100;
   // float eta = 0.4;
   // sprintf(command,"exec /mnt/storage/andre/GA-CNN/PySrc/monitor.sh  python3.8  /mnt/storage/andre/GA-CNN/PySrc/XGBRegression_4.py %d %.2f %d %d", 
   //             max_depth, eta, n_jobs, n_estimators);
   // printf("\nRunning test XGBoost\n");
   // printf("%s\n", command);
   // system(command);
   // printf("End test XGBoost \n");

   // //getTestResult("PerfResult.dat", &energy, &time, param);

   // printf("time = %.3lfs, energy = %.3lfJ\n", time, energy);


//printf("main current line %d\n", __LINE__);

   // err = generatePopulation(&population, length, param);
   // accuracy = (double*)malloc(sizeof(double)*param.pop_size);

//printf("main current line %d\n", __LINE__);

// float eta;
// int n_jobs, n_estimators, max_depth;

//    for(int i = 0; i < param.pop_size; i++)
//    {
//       printf("old individuo %d [", i);
//       for(int j = 0; j < length; j++)
//       {
//          printf(" %d,",population[i][j]);
//       }
//       getETA(population[i], &eta);
//       getN_JOBS(population[i], &n_jobs);
//       getN_Estimators(population[i], &n_estimators);
//       getMAX_DEPTH(population[i], &max_depth);
//       printf("\b] = [%.1f, %d, %d, %d]\n", eta, n_jobs, n_estimators, max_depth);
//    }
//    putchar('\n');

//    for(int i = 0; i < param.pop_size; i++)
// {
//    accuracy[i] = 100.0f - (3+i);
// }

// //printf("main current line %d\n", __LINE__);

// err = newGeneration(population, accuracy, length, param);


   // printf("Running test monitor.sh\n");
   // system("exec /mnt/storage/andre/Teste/monitor.sh");
   // printf("End test monitos.sh\n");
  
   return 0;
}

//===================================================================================================================================================================================

void startUp(int argc, char** argv)
{
   char configFileName[65];
   bool manual = false;
   bool configFile = false;
   if(argc > 1)
   {
      for(int i = 1; i < argc; i++)
      {
         if ((!strcmp(argv[i], "-h")) || (!strcmp(argv[i], "--help")))
         {
            helpFun();
            exit(0);
         }
         else if((!strcmp(argv[i], "-m")) || (!strcmp(argv[i], "--manual")))
         {
            manual = true;
         }
        //  else if((!strcmp(argv[i], "-s")) || (!strcmp(argv[i], "--simple")))
        //  {
        //     simple = true;
        //  }
        //  else if((!strcmp(argv[i], "--round")) || (!strcmp(argv[i], "-r")) )
        //  {
        //     if(atoi(argv[i+1]) >= 1)
        //     {
        //        nRounds = atoi(argv[i+1]);
        //        i = i+1;
        //     }
        //     else
        //     {
        //        printf("Parameter \"--round\"/\"-r\" must be followed by a positive integer !\n");
        //        exit(0);
        //     }
        //  }
         else if((!strcmp(argv[i], "--version")) || (!strcmp(argv[i], "-v")) )
         {
            version();
            exit(0);
         }
        //  else if((!strcmp(argv[i], "--autonomy")) || (!strcmp(argv[i], "-a")) )
        //  {
        //     if(atoi(argv[i+1]) >= 1)
        //     {
        //        param.autonomy = atoi(argv[i+1]);
        //        i = i+1;
        //     }
        //     else
        //     {
        //        printf("Parameter \"--autonomy\"/\"-a\" must be followed by a positive real number !\n");
        //        exit(0);
        //     }
        //  }
         else if( (!strcmp(argv[i], "--file")) || (!strcmp(argv[i], "-f")) )
         {
            if(argv[i+1][0] != '-')
            {
               strcpy(configFileName, argv[i+1]);
               i = i+1;
               configFile = true;
               printf("current line %d, inFileName = %s\n", __LINE__, configFileName);
            }
            else
            {
               printf("Parameter \"--file\"/\"-f\" must be followed by the input file name!\n");
               printf("current line %d, inFileName = %s\n", __LINE__, configFileName);
               exit(0);
            }
         }
         else
         {
            printf("GA_DL : Invalid option! \"%s\", try \'GA_DL --help\' for more information.\n", argv[i]);
            exit(1);
         }
      }
   }

   if(configFile)
   {
      int err = configParam(configFileName, &param);
      if(!err)
      {
         cout << "Using Using Configuration File values;" <<endl;
         cout << "   pop_size = " << param.pop_size <<endl;
         //       cout << "   initialization method = " << param.initType <<endl;
         cout << "   elit = " << param.elit <<endl;
         cout << "   Fitness Type = " << param.fitnessType <<endl;
         //       cout << "   Crossover Type = " << param.crossoverType <<endl;
         //       cout << "   Mutation Type = " << param.mutationType <<endl;
         cout << "   pc = " << param.pc <<endl;
         cout << "   pm = " << param.pm <<endl;
         cout << "   max_gen = " << param.max_gen <<endl;
         cout << "   score weight = " << param.wScore <<endl;
         cout << "   time weight = " << param.wTime <<endl;
         cout << "   energy weight = " << param.wEnergy <<endl;
         cout << "Setting values. please wait!." <<endl;
         sleep(3);   
      }
   }
   else if(manual)
   {
      do
      {
         char buffer[256];
         cout<<"Input population (10)= ";
         cin >> buffer;
         param.pop_size = atoi(buffer);
      }while(param.pop_size < 3);
      
      // do
      // {
      //    char buffer[256];
      //    cout<<"Select initialization method:   ";
      //    cin >> buffer;
      //    param.initType = atoi(buffer);
      // }while(param.initType < 1 || param.initType > 3);
      
      do
      {
         char buffer[256];
         cout<<"Input elit (recommended 2) = ";
         cin >> buffer;
         param.elit = atoi(buffer);
      }while(param.elit < 0 || param.elit > 10);
      
      do
      {
         char buffer[256];
         cout<<"Select fitness type:   ";
         cin >> buffer;
         param.fitnessType = atoi(buffer);
      }while(param.fitnessType < 1 || param.fitnessType > 4);
      
//       do
//       {
//          char buffer[256];
//          cout<<"Select Crossover type:   ";
//          cin >> buffer;
//          param.crossoverType = atoi(buffer);
//       }while(param.crossoverType < 1 || param.crossoverType > 4);
//       
//       do
//       {
//          char buffer[256];
//          cout<<"Select Mutation type:   ";
//          cin >> buffer;
//          param.mutationType = atoi(buffer);
//       }while(param.mutationType < 1 || param.mutationType > 5);
      do
      {
         char buffer[256];
         cout<<"Input the probability of Crossover (0.00 to 100.00 : recommended 80.00)= ";
         cin >> buffer;
         param.pc = atof(buffer);
      }while(param.pc<0 || param.pc>100);

      do
      {
         char buffer[256];
         cout << "Input the probability of Mutation (0.00 to 100.00 : recommended 10.0)= ";
         cin >> buffer;
         param.pm = atof(buffer);
      }while(param.pm<0 || param.pm>100);
      
      do
      {
         char buffer[256];
         cout << "Input max gen (100)= "; //recommended Pm=100..1000
         cin >> buffer;
         param.max_gen = atoi(buffer);
      }while(param.max_gen < 1);

      do
      {
         char buffer[256];
         cout << "Input the weight for the score metric = ";
         cin >> buffer;
         param.wScore = atof(buffer);
      }while(param.wScore<0);

      do
      {
         char buffer[256];
         cout << "Input the weight for the time = ";
         cin >> buffer;
         param.wTime = atof(buffer);
      }while(param.wTime<0);

      do
      {
         char buffer[256];
         cout << "Input the for the energy = ";
         cin >> buffer;
         param.wEnergy = atof(buffer);
      }while(param.wEnergy<0);

      cout << "Using manual values;" <<endl;
      cout << "   pop_size = " << param.pop_size <<endl;
      //cout << "   initialization method = " << param.initType <<endl;
      cout << "   elit = " << param.elit <<endl;
      cout << "   Fitness Type = " << param.fitnessType <<endl;
//       cout << "   Crossover Type = " << param.crossoverType <<endl;
//       cout << "   Mutation Type = " << param.mutationType <<endl;
      cout << "   pc = " << param.pc <<endl;
      cout << "   pm = " << param.pm <<endl;
      cout << "   max_gen = " << param.max_gen <<endl;
      cout << "   score weight = " << param.wScore <<endl;
      cout << "   time weight = " << param.wTime <<endl;
      cout << "   energy weight = " << param.wEnergy <<endl;
      cout << "Setting values. please wait!." <<endl;
      sleep(3);
   }
   else
   {
      param.pop_size = 30;
      param.initType = 1;
      param.elit = 2;
      param.fitnessType = 2;
//       param.crossoverType = 3;
//       param.mutationType = 4;
      param.pc = 80.0;
      param.pm = 10.0;
      param.max_gen = 30;
      param.wScore = 1;
      param.wTime = 1;
      param.wEnergy = 1;
      cout << "Using Default values;" <<endl;
      cout << "   pop_size = " << param.pop_size <<endl;
      cout << "   initialization method = " << param.initType <<endl;
      cout << "   elit = " << param.elit <<endl;
      cout << "   Fitness Type = " << param.fitnessType <<endl;
//       cout << "   Crossover Type = " << param.crossoverType <<endl;
//       cout << "   Mutation Type = " << param.mutationType <<endl;
      cout << "   pc = " << param.pc <<endl;
      cout << "   pm = " << param.pm <<endl;
      cout << "   max_gen = " << param.max_gen <<endl;
      cout << "   score weight = " << param.wScore <<endl;
      cout << "   time weight = " << param.wTime <<endl;
      cout << "   energy weight = " << param.wEnergy <<endl;
      cout << "Setting values. please wait!." <<endl;
      sleep(3);
   }
//    round_result = (double*)malloc(sizeof(double)*nRounds);
//    round_percent = (double*)malloc(sizeof(double)*nRounds);
//    round_steps = (double*)malloc(sizeof(double)*nRounds);

   round_results = (double**)malloc(sizeof(double*)*4);
   for(int i = 0; i < 4; i++)
   {
      round_results[i] = (double*)malloc(sizeof(double)*nRounds);
   }


}

void helpFun()
{
   printf("GA_DL!\n\n");
   printf("Usage: GA_DL [OPTION1 [ARG1]] [OPTION2 [ARG2]] ... \n\n");

   printf("   -h,  --help%39s\n", "Display this information.");
//    printf("   -s,  --simple%40s\n", "Display a simplified report.");
   printf("   -m,  --manual%59s\n", "Allows for manual setup of the test parameters.");
//    printf("   -r,  --round%54s\n%67s\n%54s\n", "Define the number of rounds for the test.", 
//                                                "The value must be a positive integer,", "The default value is 1.");
   printf("   -v,  --version%43s\n", "Display Current instaled Version");
//    printf("   -d,  --device%47s\n%64s\n%55s\n", "If more than 1 device is installed,", 
//                                                 "selects the device to be tested", "The default value is 0");
//    printf("   -k,  -K%62s\n%64s\n", "Sets the result unit of the memory bandwidth", "and MIP badwidth to KBytes/bits");
//    printf("   -m,  -M%62s\n%64s\n", "Sets the result unit of the memory bandwidth", "and MIP badwidth to MBytes/bits");
//    printf("   -g,  -G%62s\n%64s\n", "Sets the result unit of the memory bandwidth", "and MIP badwidth to GBytes/bits");
//    printf("   -b%67s\n%57s\n", "Sets the result unit of the memory bandwidth", "and MIP badwidth to bits");


   printf("\n\n");
   version();
   
}
void getDate()
{
   char month[4], wday[4];
   time_t now;
   now = time(0);
   struct tm* tm = localtime(&now);

   switch( tm->tm_wday )
   {
      case 0: strcpy(wday, "Sun");
              break;
      case 1: strcpy(wday, "Mon");
              break;
      case 2: strcpy(wday, "Tue");
              break;
      case 3: strcpy(wday, "Wed");
              break;
      case 4: strcpy(wday, "Thu");
              break;
      case 5: strcpy(wday, "Fri");
              break;
      case 6: strcpy(wday, "Sat");
              break;
   }

   switch( tm->tm_mon )
   {
      case 0: strcpy(month, "Jan");
              break;
      case 1: strcpy(month, "Feb");
              break;
      case 2: strcpy(month, "Mar");
              break;
      case 3: strcpy(month, "Apr");
              break;
      case 4: strcpy(month, "May");
              break;
      case 5: strcpy(month, "Jun");
              break;
      case 6: strcpy(month, "Jul");
              break;
      case 7: strcpy(month, "Aug");
              break;
      case 8: strcpy(month, "Sep");
              break;
      case 9: strcpy(month, "Oct");
              break;
      case 10: strcpy(month, "Nov");
               break;
      case 11: strcpy(month, "Dec");
               break;

   }

   printf("%s %s %2d %d:%02d:%02d %d\n", wday, month, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, 1900 + tm->tm_year);
   
}

void version()
{
   printf("\n");
   printf("Latest version:  %s  as of %s, %s\n\n", ver, modified_date, modified_time);
   printf("Please report any Bugs to: andre.yokoyama.ist@gmail.com\n");
   printf("GitHub: https://github.com/AndreYokoyama/GA-ML.git\n\n");
}


void GA_Solver()
{
   char outFileName[24] = {"evolution.dat"};
   char inFileName[24] = {"accuracy.dat"};
   char perfResultFile[24] = {"PerfResult.dat"};
   int err = 0, gen;
   double *accuracy, *pop_fitness;
   int parentA, parentB;
   int *offspring_A, *offspring_B;
   float eta;
   int n_jobs, n_estimators, max_depth;

   outPtr = fopen(outFileName, "w");
   if(outPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", outFileName);
      exit(1);
   }
   

   err = generatePopulation(&population, length, param);
   accuracy = (double*)malloc(sizeof(double)*param.pop_size);
   pop_fitness = (double*)malloc(sizeof(double)*param.pop_size);
   gen = 0;

   do 
   {
      inPtr = fopen(inFileName, "w");
      if(inPtr == NULL)
      {
         printf("Couldn\'t open file %s\n", inFileName);
         exit(1);
      }
      fclose(inPtr);
      err = testPopulation(population, accuracy, param, gen);
      if (param.fitnessType == 1)
      {
         err = fitness(population, pop_fitness, param);
      }
      else
      {
         err = fitness2(population, pop_fitness, param, gen, accuracy);
      }
      
      //err = getAccuracy(inFileName, accuracy, param, gen);
      
      err = sortPopulation(population, param, pop_fitness, accuracy);

      fprintf(outPtr,"Generatio %d\n",gen);
      for (int i = 0; i < param.pop_size; i++)
      {
         getETA(population[i], &eta);
         getN_JOBS(population[i], &n_jobs);
         getN_Estimators(population[i], &n_estimators);
         getMAX_DEPTH(population[i], &max_depth);
         fprintf(outPtr," [%.2f, %d, %d, %d] - accuracy = %.6lf - fitness = %.6f\n", eta, n_jobs, n_estimators, max_depth, accuracy[i], pop_fitness[i]);
         //fprintf(outPtr,"%lf\n", accuracy[i]);
      }
      fprintf(outPtr,"\n\n");

      err = newGeneration(population, pop_fitness, length, param);
      gen++;


   }while (gen < param.max_gen);

   inPtr = fopen(inFileName, "w");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   fclose(inPtr);
   err = testPopulation(population, accuracy, param);
   if (param.fitnessType == 1)
   {
      err = fitness(population, pop_fitness, param);
   }
   else
   {
      err = fitness2(population, pop_fitness, param, accuracy);
   }
   
   err = sortPopulation(population, param, pop_fitness, accuracy);

   fprintf(outPtr,"Generatio %d\n",gen);
   for (int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      fprintf(outPtr," [%.2f, %d, %d, %d] - accuracy = %.6lf - fitness = %.6f\n", eta, n_jobs, n_estimators, max_depth, accuracy[i], pop_fitness[i]);
      //fprintf(outPtr,"%lf\n", accuracy[i]);
   }
   
   fclose(outPtr);
   free(accuracy);

}

void XGBR_Solver()
{
   char outFileName[24] = {"evolution.dat"};
   char inFileName[24] = {"accuracy.dat"};
   char perfResultFile[24] = {"PerfResult.dat"};
   int err = 0, gen;
   double *score, *time, *energy, *pop_fitness;
   int parentA, parentB;
   int *offspring_A, *offspring_B;
   float eta;
   int n_jobs, n_estimators, max_depth;

   outPtr = fopen(outFileName, "w");
   if(outPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", outFileName);
      exit(1);
   }
   
   score = (double*)malloc(sizeof(double)*param.pop_size);
   time = (double*)malloc(sizeof(double)*param.pop_size);
   energy = (double*)malloc(sizeof(double)*param.pop_size);
   pop_fitness = (double*)malloc(sizeof(double)*param.pop_size);
   gen = 0;


   err = generatePopulation(&population, length, param);

   do 
   {
      inPtr = fopen(inFileName, "w");
      if(inPtr == NULL)
      {
         printf("Couldn\'t open file %s\n", inFileName);
         exit(1);
      }
      fclose(inPtr);

      err = xgbrTestPopulation(population, time, energy, param, gen);

      // for(int i = 0; i < param.pop_size; i++)
      // {
      //    printf("i = %d, time = %.3lf, energy = %.2lf\n", i, time[i], energy[i]);
      // }

      if (param.fitnessType == 1)
      {
         err = xgbrFitness(population, pop_fitness, param, score, time, energy);
      }
      else
      {
         err = xgbrFitness(population, pop_fitness, param, gen, score, time, energy);
      }
      
      // for (int i = 0; i < param.pop_size; i++)
      // {
      //    getETA(population[i], &eta);
      //    getN_JOBS(population[i], &n_jobs);
      //    getN_Estimators(population[i], &n_estimators);
      //    getMAX_DEPTH(population[i], &max_depth);
      //    fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
      //             eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
      // }
      // fprintf(outPtr,"\n\n");

      err = sortPopulation(population, param, pop_fitness, score, energy, time);

      fprintf(outPtr,"Generatio %d\n",gen);
      for (int i = 0; i < param.pop_size; i++)
      {
         getETA(population[i], &eta);
         getN_JOBS(population[i], &n_jobs);
         getN_Estimators(population[i], &n_estimators);
         getMAX_DEPTH(population[i], &max_depth);
         fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
                  eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
      }
      fprintf(outPtr,"\n\n");

      err = newGeneration(population, pop_fitness, length, param);
      gen++;


   }while (gen < param.max_gen);

   inPtr = fopen(inFileName, "w");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   fclose(inPtr);

   err = xgbrTestPopulation(population, time, energy, param);

   if (param.fitnessType == 1)
   {
      err = xgbrFitness(population, pop_fitness, param, score, time, energy);
   }
   else
   {
      err = xgbrFitness(population, pop_fitness, param, score, time, energy);
   }
   
   err = sortPopulation(population, param, pop_fitness, score, energy, time);

   fprintf(outPtr,"Generatio %d\n",gen);
   for (int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
                  eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
   }
   
   fclose(outPtr);
   free(score);
   free(time);
   free(energy);
   free(pop_fitness);

}

void XGBC_Solver()
{
   char outFileName[24] = {"evolution.dat"};
   char inFileName[24] = {"accuracy.dat"};
   char perfResultFile[24] = {"PerfResult.dat"};
   int err = 0, gen;
   double *score, *time, *energy, *pop_fitness;
   int parentA, parentB;
   int *offspring_A, *offspring_B;
   float eta;
   int n_jobs, n_estimators, max_depth;

   outPtr = fopen(outFileName, "w");
   if(outPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", outFileName);
      exit(1);
   }
   
   score = (double*)malloc(sizeof(double)*param.pop_size);
   time = (double*)malloc(sizeof(double)*param.pop_size);
   energy = (double*)malloc(sizeof(double)*param.pop_size);
   pop_fitness = (double*)malloc(sizeof(double)*param.pop_size);
   gen = 0;


   err = generatePopulation(&population, length, param);

   do 
   {
      inPtr = fopen(inFileName, "w");
      if(inPtr == NULL)
      {
         printf("Couldn\'t open file %s\n", inFileName);
         exit(1);
      }
      fclose(inPtr);

      err = xgbcTestPopulation(population, time, energy, param, gen);

      // for(int i = 0; i < param.pop_size; i++)
      // {
      //    printf("i = %d, time = %.3lf, energy = %.2lf\n", i, time[i], energy[i]);
      // }

      if (param.fitnessType == 1)
      {
         err = xgbcFitness(population, pop_fitness, param, score, time, energy);
      }
      else
      {
         err = xgbcFitness(population, pop_fitness, param, gen, score, time, energy);
      }
      
      // for (int i = 0; i < param.pop_size; i++)
      // {
      //    getETA(population[i], &eta);
      //    getN_JOBS(population[i], &n_jobs);
      //    getN_Estimators(population[i], &n_estimators);
      //    getMAX_DEPTH(population[i], &max_depth);
      //    fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
      //             eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
      // }
      // fprintf(outPtr,"\n\n");

      err = sortPopulation(population, param, pop_fitness, score, energy, time);

      fprintf(outPtr,"Generatio %d\n",gen);
      for (int i = 0; i < param.pop_size; i++)
      {
         getETA(population[i], &eta);
         getN_JOBS(population[i], &n_jobs);
         getN_Estimators(population[i], &n_estimators);
         getMAX_DEPTH(population[i], &max_depth);
         fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
                  eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
      }
      fprintf(outPtr,"\n\n");

      err = newGeneration(population, pop_fitness, length, param);
      gen++;


   }while (gen < param.max_gen);

   inPtr = fopen(inFileName, "w");
   if(inPtr == NULL)
   {
      printf("Couldn\'t open file %s\n", inFileName);
      exit(1);
   }
   fclose(inPtr);

   err = xgbcTestPopulation(population, time, energy, param);

   if (param.fitnessType == 1)
   {
      err = xgbcFitness(population, pop_fitness, param, score, time, energy);
   }
   else
   {
      err = xgbcFitness(population, pop_fitness, param, score, time, energy);
   }
   
   err = sortPopulation(population, param, pop_fitness, score, energy, time);

   fprintf(outPtr,"Generatio %d\n",gen);
   for (int i = 0; i < param.pop_size; i++)
   {
      getETA(population[i], &eta);
      getN_JOBS(population[i], &n_jobs);
      getN_Estimators(population[i], &n_estimators);
      getMAX_DEPTH(population[i], &max_depth);
      fprintf(outPtr," [%.2f, %d, %d, %d] - score = %.6lf - time = %.3lf - energy = %.2lf - fitness = %.6f\n", 
                  eta, n_jobs, n_estimators, max_depth, score[i], time[i], energy[i], pop_fitness[i]);
   }
   
   fclose(outPtr);
   free(score);
   free(time);
   free(energy);
   free(pop_fitness);

}

//===================================================================================================================================================================================
