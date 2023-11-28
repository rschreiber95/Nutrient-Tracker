//
//  Final Project- Personal Nutrient Tracker
//
//  Created by Reagan Schreiber on 9/18/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//global variable that gets used in calculateRemaining() function
double recommendedValue;
int dayCounter;
                             

//Beginning of the structs, typedefs, constructors, and destructors utilized for the linked lists. List List Traversal to display information within nodes is used in option 1 of the second main menu("View Daily Nutrient Intake Goals")
struct nutrientRec{
    double amount;
    int type;
    struct nutrientRec* next;
};
typedef struct nutrientRec nutrientRec;

struct recList{
    nutrientRec* head;
};
typedef struct recList recList;

nutrientRec* nutrientRecConstructor(double amount, int n)
{
    nutrientRec* rec = malloc(sizeof(nutrientRec));
    rec->amount = amount;
    rec->type = n;
    rec->next = NULL;
    return rec;
}

void nutrientRecDestructor(nutrientRec* nRec)
{
    free(nRec);
}

recList* recListConstructor(void)
{
    recList* list = malloc(sizeof(recList));
    list->head = NULL;
    return list;
}

void recListDestructor(recList* list)
{
    free(list);
}

void addToList(nutrientRec* rec, recList* list)
   {
        rec->next = list->head;
        list->head = rec;
    }


nutrientRec* temp;




//This function is where a linked list is actually TRAVERSED, and the members of its subsequent node structs are printed out.
void printNutrientRecList(recList* list)
{
    printf("\nYour recommended daily nutrient intake is as follows:\n\n");
    temp = list->head;
    
    while(temp!= NULL)
    {
        switch(temp->type)
        {
            case(5):
            {
                printf("\n\nCALORIES: %.1lf\n", temp->amount);
                break;
            }
            case(4):
            {
                printf("\n\nSUGAR( grams ): %.1lf\n", temp->amount);
                break;
            }
            case(3):
            {
                printf("\n\nSODIUM( milligrams ): %.1lf\n", temp->amount);
                break;
            }
            case(2):
            {
                printf("\n\nPROTEIN( grams ): %.1lf\n", temp->amount);
                break;
            }
            case(1):
            {
                printf("\n\nFAT( grams ): %.1lf\n", temp->amount);
                break;
            }
            case(0):
            {
                printf("\n\nCHOLESTEROL( milligrams ): %.1lf\n", temp->amount);
                break;
            }
        }
        
        temp = temp->next;
    }
}


//Calculates the recommended nutrient value based on sex, weight, and height; this will get called in the function newRec to help initialize the newRec's double variable 'amount'.
double calculateNutrientRec(char* sex, double height, double weight, int age, int index)
{
    //This switch will individualize the calculations for each nutrient based on index variable.
    switch(index){
            
        case(0)://cholesterol case
        {
            return 300.0;
            break;
        }
        case(1)://fat case
        {
            if (strcmp(sex, "m") ==0 )
            {
                return (1/30.0)*(66.5 + (6.23*weight) + (12.7*height) - (6.8*age));
            }
            else{
                return (1/30.0)*(655.1 + (4.35*weight) + (4.7*height) -(4.7*age));
            }
            break;
        }
        case(2)://protein case
        {
            
            return ((weight*0.454)*(0.85));
            break;
        }
        case(3)://sodium case
        {
            if(age <= 3)
            {
                return 1500.0;
            }
            else if(age <= 8)
            {
                return 1900.0;
            }
            else if(age <= 13)
            {
                return 2100.0;
            }
            else if(age > 13)
            {
                return 2300.0;
            }
            break;
        }
        case(4)://sugar case
        {
            if (strcmp(sex, "m") ==0 )
            {
                if(age<18)
                {
                    return 20.0;
                }
                else{
                    return 36.0;
                }
            }
            else{
                
                if(age<18)
                {
                    return 20.0;
                }
                else{
                    return 25.0;
                }
            }
            break;
        }
        case(5)://calories case
        {
          if (strcmp(sex, "m") ==0 )
          {
              return (66.5 + (6.23*weight) + (12.7*height) - (6.8*age));
          }
          else{
              return (655.1 + (4.35*weight) + (4.7*height) -(4.7*age));
          }
            break;
        }
    }
    return 0.0;
}


//Traverses a file, will calculate how many days the user has been tracking their nutrient intake
int calculateAmountDaysTracked(FILE* file_ptr)
{
  
    double counter = 0;
    double output = 0;
   
   
  while(fscanf(file_ptr, "%lf", &output) != EOF)
   {
       
       counter++;
      
  }
    
   return counter;
  
}

//Traverses a file, will calculate the TOTAL of all doubles read from file
double calculateFileTotal(FILE* file_ptr)
{
   
    double output = 0;
    double total = 0;

    while(fscanf(file_ptr, "%lf", &output) != EOF)
    {
       
        total = total + output;
    }
    return total;
}





//This function will find the difference between a current nutrient consumption daily total, and the daily RECOMMENDED nutrient goal. Will traverse the file containing the users personalized nutrient intake goals until it gets to the intended nutrient goal in the file(which int x will help us identify via the x-REGULATED for loop)
double calculateRemaining(double currentTotal, FILE* file_ptr, int x)
{
   
    for(int i= -1; i < x; i++)
    {
     fscanf(file_ptr, "%lf\n", &recommendedValue);
    }
   
    return (recommendedValue - currentTotal);
}



//Calculates the cumulative avg of each nutrient. Takes a file as a parameter(this file will be the file that stores the totals of each day.....will call the calculate file total to calculate the TOTAL of all the toals, and then will divide by how many days have been tracked(which we will get by calling the calculateAmountDaysTracked() function
double calculateCumulativeAvg(FILE* file1)
{
    double total = calculateFileTotal(file1);
    
    //restarting reading of the file from the first line
    rewind(file1);
    
    double days = calculateAmountDaysTracked(file1);
    
    return (total / days);
}









void menu(void)
{
    printf("--------------------------------------------------------------------------------------------------");
    printf("\n\n\n                                          MAIN MENU\n\n                          Select a choice from the following options:\n\n1: View Your Daily Goals\n\n\n2: Add A Meal\n\n\n3: View Today's Progress\n\n\n4: Save Today's Progress, Come Back Later!\n\n\n5: End Today's Tracking and Recieve Reports\n\n\n\n\nAnswer> ");
}

//Will hold the daily consumption amounts of nutrients.
FILE* file_ptr_cals;
FILE* file_ptr_sugar;
FILE* file_ptr_sodium;
FILE* file_ptr_protein;
FILE* file_ptr_fat;
FILE* file_ptr_cholesterol;

//Will hold totals from each day, will help caluclate a cumulative progress report of nutrient intake. Will never get wiped, cleared.
FILE* calTotals;
FILE* sugarTotals;
FILE* sodiumTotals;
FILE* proteinTotals;
FILE* fatTotals;
FILE* cholesterolTotals;
FILE* recs;



    int main(void)
{
    // Variables/ Pointer Declarations
        recList* recList;
        nutrientRec* nutrientRecCals;
        nutrientRec* nutrientRecSugar;
        nutrientRec* nutrientRecSodium;
        nutrientRec* nutrientRecProtein;
        nutrientRec* nutrientRecFat;
        nutrientRec* nutrientRecCholesterol;
        
        int a=1;
        char exceptionToStartNewDay = 'y';

        int answer=1;
        
      
        double nrec;
        double fscanfValue = 0;
        
        char sex[1]= "m";
        double height;
        double weight;
        int age;
        
        double calories;
        double sugar;
        double sodium;
        double protein;
        double fat;
        double cholesterol;
        
        double calorieTotal;
        double sugarTotal;
        double sodiumTotal;
        double proteinTotal;
        double fatTotal;
        double cholesterolTotal;
        double cumulativeDailyAvg;
        int daysTracked;
        
        //opening the totals files for each respective nutrient.
        calTotals = fopen("calTotals.txt", "a+");
        sugarTotals = fopen("sugarTotals.txt", "a+");
        sodiumTotals = fopen("sodiumTotals.txt", "a+");
        proteinTotals = fopen("proteinTotals.txt", "a+");
        fatTotals = fopen("fatTotals.txt", "a+");
        cholesterolTotals = fopen("cholesterolTotals.txt", "a+");
        
        
        do
        {
            printf("\n\n                        Welcome to your Personalized Nutrient Tracker!\n\n\nTrack your daily intake of calories, sugar, sodium, protein, fat, and cholesterol!\n\n\n\n                        Please select from the following:\n\n\n                      1: Start A New Day of Nutrient Tracking\n\n                      2: Continue Tracking Today\n\n                      3: Exit \n\n\nAnswer> ");
            scanf(" %d", &a);
            
            
            //User wants to begin tracking a new day
            if(a==1)
            {
                printf("\n\n                                     DISCLAIMER:\nIF THIS IS YOUR FIRST TIME USING THE PROGRAM AND YOU HAVE NOT BEGUN TRACKING YOUR NUTRIENT\nINTAKE, DISREGARD THE FOLLOWING WARNING MESSAGE AND ENTER 'Y' WHEN PROMPTED.\n\n                                    HAPPY TRACKING!\n\n\n                                     WARNING:\nIf you have not concluded your tracking from yesterday by recieving a cumulative report, yesterday's data will be lost.\n\n\n\n\nPlease Answer: Have you asked for a cumulative report of your previous tracking?:\n\n  Y or N:\n\n");
                
                scanf(" %c", &exceptionToStartNewDay);
            }
        }while(exceptionToStartNewDay == 'N' || exceptionToStartNewDay == 'n');
        
        
        
                
                //this means user has entere 'Y' to previous question about saving previous data, and now they can begin tracking a new day(starting with right now setting their personalized nutrient intake goals)
                if(a==1){
                //opening recs file in write mode, and setting default values
                
                recs = fopen("recs.txt", "w");
                double defaultCalorie = 2000.0;
                double defaultSugar = 30.0;
                double defaultSodium = 2300.0;
                double defaultProtein = 50.0;
                double defaultFat = 25.0;
                double defaultCholesterol = 300.0;
                
                fprintf(recs, "%lf\n", defaultCalorie);
                fprintf(recs, "%lf\n", defaultSugar);
                fprintf(recs, "%lf\n", defaultSodium);
                fprintf(recs, "%lf\n", defaultProtein);
                fprintf(recs, "%lf\n", defaultFat);
                fprintf(recs, "%lf\n", defaultCholesterol);
                
                
                
                
                //opening up and clearing these files to be newly used, since user is starting a new day.
                file_ptr_cals = fopen("caloriesFile.txt","w");
                file_ptr_sugar= fopen("sugarFile.txt","w");
                file_ptr_sodium= fopen("sodiumFile.txt","w");
                file_ptr_protein= fopen("proteinFile.txt","w");
                file_ptr_fat= fopen("fatFile.txt","w");
                file_ptr_cholesterol= fopen("cholesterolFile.txt","w");
                
                    printf("--------------------------------------------------------------------------------------------");
                printf("\n                    Awesome! Its a new day, Let's begin tracking your nutrient intake!\n\nFirst up, let's calculate your personalized daily nutrient recommendations!\n");
             
                    // re-opening recs to wipe the file and start new
                    recs = freopen("recs.txt", "w", recs);
                    
                    printf("\n\nPlease enter your sex:\n\n  f or m:");
                    scanf(" %s", sex);
                    
                    
                    while(*sex != 'f'&& *sex != 'm')
                    {
                        printf("\nINVALID SEX\n");
                        printf("\nPlease enter your sex:\n\n  f or m:");
                        scanf(" %s", sex);
                    }
                                
                    printf("\n\nPlease enter your height, in inches:\n\n  Height: ");
                    scanf(" %lf", &height);
                                while(height < 36.0 || height > 84.0)
                                {
                                    printf("\nINVALID HEIGHT\nPlease enter your height, in inches:\n\n  Height: ");
                                    scanf(" %lf", &height);
                                }
                    printf("\n\nPlease enter your weight, in lbs:\n\nWeight: ");
                    scanf(" %lf", &weight);
                    printf("\nPlease enter your age, as a whole number rounded up:\n\n  Age: ");
                    scanf(" %d", &age);
                    
                    printf("--------------------------------------------------------------------------------------------");
                    printf("\n\n                                     CALCULATIONS SUCCESSFUL!\n\nPer your sex, height, weight, and age, your daily nutrient intake goals are as follows:\n\n");
                    
                    //This for-loop will calculate the recommended intake of each nutrient for the individual. Will input the results to the recs file, and also print the recommended list to the terminal.
                    for(int i = 5; i >= 0; i--)
                    {
                        nrec = calculateNutrientRec(sex, height, weight, age, i);
                        switch(i){
                            case(5):
                            {
                                printf("\nCALORIES: %.1lf", nrec);
                                break;
                            }
                            case(4):
                            {
                                printf("\n\n\nSUGAR( grams ): %.1lf", nrec);
                                break;
                            }
                            case(3):
                            {
                                printf("\n\n\nSODIUM( milligrams ): %.1lf", nrec);
                                break;
                            }
                            case(2):
                            {
                                printf("\n\n\nPROTEIN( grams ): %.1lf", nrec);
                                break;
                            }
                            case(1):
                            {
                                printf("\n\n\nFAT( grams ): %.1lf", nrec);
                                break;
                            }
                            case(0):
                            {
                                printf("\n\n\nCHOLESTEROL( milligrams ): %.1lf\n", nrec);
                                break;
                            }
                        }
                        
                        fprintf(recs, "%.2lf\n", nrec);
                    }
                    
                    answer = 1;
                    fclose(recs);
                    recs = fopen("recs.txt", "r");
                    
               
               
                
            }
            
            
            //User wants to continue tracking current day
            else if(a==2)
            {
                printf("\n\nAwesome! You want to continue tracking today's nutrient intake!!\n");
                recs = fopen("recs.txt", "a");
                //opening files in append mode, since we are adding to today's tracking
                file_ptr_cals = fopen("caloriesFile.txt","a+");
                file_ptr_sugar= fopen("sugarFile.txt","a+");
                file_ptr_sodium= fopen("sodiumFile.txt","a+");
                file_ptr_protein= fopen("proteinFile.txt","a+");
                file_ptr_fat= fopen("fatFile.txt","a+");
                file_ptr_cholesterol= fopen("cholesterolFile.txt","a+");
                
                
            }
            
            //User wants to just exit program
            else if(a==3)
            {
                return 0;
            }
        
        
        //This is the start of the do-while loop that regulates the iterations of the main menu
        while(answer != 0)
        {
            //menu gets printed
            menu();
            
            //answer to menu options gets scanned into answer variable
            scanf(" %d", &answer);
            
            
            if(answer == 1)
            {
                // Creating the linked list of nutrientRec nodes, which will get printed out to the terminal for the user to see via a traversal of the linked list.
                fclose(recs);
                fopen("recs.txt", "r");
                printf("--------------------------------------------------------------------------------------------");
               
                
                    recList = recListConstructor();
                    
                    for(int i=0; i<=5; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecCholesterol = nutrientRecConstructor(fscanfValue, 0);
                    addToList(nutrientRecCholesterol, recList);
                    fclose(recs);
                    recs = fopen("recs.txt", "r");
                
                    
                    
                    for(int i=0; i<=4; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecFat = nutrientRecConstructor(fscanfValue, 1);
                    addToList(nutrientRecFat, recList);
                fclose(recs);
                recs = fopen("recs.txt", "r");
                    
                    for(int i=0; i<=3; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecProtein= nutrientRecConstructor(fscanfValue, 2);
                    addToList(nutrientRecProtein, recList);
                fclose(recs);
                recs = fopen("recs.txt", "r");
                    
                    for(int i=0; i<=2; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecSodium= nutrientRecConstructor(fscanfValue, 3);
                    addToList(nutrientRecSodium, recList);
                fclose(recs);
                recs = fopen("recs.txt", "r");
                    
                    for(int i=0; i<=1; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecSugar= nutrientRecConstructor(fscanfValue, 4);
                    addToList(nutrientRecSugar, recList);
                fclose(recs);
                recs = fopen("recs.txt", "r");
                    
                    for(int i=0; i<=0; i++)
                    {
                     fscanf(recs, "%lf", &fscanfValue);
                    }
                    nutrientRecCals= nutrientRecConstructor(fscanfValue, 5);
                    addToList(nutrientRecCals, recList);
                    
                    //Printing out the recommended nutrient Values
                    printNutrientRecList(recList);
                
                
                
                //Using destructors to FREE the Dynamic Memory Allocations
                nutrientRecDestructor(nutrientRecCholesterol);
                nutrientRecDestructor(nutrientRecFat);
                nutrientRecDestructor(nutrientRecProtein);
                nutrientRecDestructor(nutrientRecSodium);
                nutrientRecDestructor(nutrientRecSugar);
                nutrientRecDestructor(nutrientRecCals);
                
                recListDestructor(recList);
                
                
            }
            
            //User wantst to add a meal's nutrient contents to their respective files
            else if(answer == 2)
            {
                
                //re-opening files in "append" mode, in case they were opened in any other mode previously.
                file_ptr_cals= freopen("caloriesFile.txt","a+", file_ptr_cals);
                file_ptr_sugar= freopen("sugarFile.txt","a+", file_ptr_sugar);
                file_ptr_sodium= freopen("sodiumFile.txt","a+", file_ptr_sodium);
                file_ptr_protein= freopen("proteinFile.txt","a+", file_ptr_protein);
                file_ptr_fat= freopen("fatFile.txt","a+", file_ptr_fat);
                file_ptr_cholesterol=freopen("cholesterolFile.txt","a+", file_ptr_cholesterol);
                printf("--------------------------------------------------------------------------------------------");
                printf("\n                       You want to add a meal's nutrients to today's tracking!\n");
                printf("\nPlease enter meal's calorie amount:\n\n  Calories: ");
                scanf("%lf", &calories);
                fprintf(file_ptr_cals, "%.2lf\n", calories);
                
                printf("\n%.1lf calories added to today's total.\n\n\nPlease enter meal's sugar content, in grams:\n\n  Sugar: ", calories);
                scanf("%lf", &sugar);
                fprintf(file_ptr_sugar, "%.1lf\n", sugar);
                
                printf("\n%.1lf grams of sugar added to today's total.\n\n\nPlease enter meal's sodium content, in milligrams:\n\n  Sodium: ", sugar);
                scanf("%lf", &sodium);
                fprintf(file_ptr_sodium, "%.1lf\n", sodium);
                
                printf("\n%.1lf milligrams of sodium added to today's total.\n\n\nPlease enter meal's protein content, in grams:\n\n  Protein: ", sodium);
                scanf("%lf", &protein);
                fprintf(file_ptr_protein, "%.1lf\n", protein);
                
                printf("\n%.1lf grams of protein added to today's total.\n\n\nPlease enter meal's fat content, in grams:\n\n  Fat: ", protein);
                scanf("%lf", &fat);
                fprintf(file_ptr_fat, "%.1lf\n", fat);
                
                printf("\n%.1lf grams of fat added to today's total.\n\n\nPlease enter meal's cholesterol content, in milligrams:\n\n  Cholesterol: ", fat);
                scanf("%lf", &cholesterol);
                fprintf(file_ptr_cholesterol, "%.1lf\n", cholesterol);
                
                printf("\n%.1lf milligrams of cholesterol added to today's total.\n\n\n                             Meal successfully tracked! Awesome job!\n", cholesterol);
            }
            
            
            //User wants to know todays' progress so far. this option will traverse the contents of each file via the calculateFileTotal function and find the daily total for each nutrint to print out, and will then print the remaining total for each nutrient using the calculateRemaining function.
            else if(answer == 3)
            {
                fclose(file_ptr_cals);
                fclose(file_ptr_sugar);
                fclose(file_ptr_sodium);
                fclose(file_ptr_protein);
                fclose(file_ptr_fat);
                fclose(file_ptr_cholesterol);
                fclose(recs);
                //re-opeing the files in read mode so that the functions calculateFileTotal and calculateRemaining can read from file.
                file_ptr_cals=fopen("caloriesFile.txt","r");
                file_ptr_sugar= fopen("sugarFile.txt","r");
                file_ptr_sodium= fopen("sodiumFile.txt","r");
                file_ptr_protein= fopen("proteinFile.txt","r");
                file_ptr_fat= fopen("fatFile.txt","r");
                file_ptr_cholesterol=fopen("cholesterolFile.txt","r");
                recs = fopen("recs.txt", "r");
                
                
                
                //setting these variables to the totals of each respective file
                calorieTotal = calculateFileTotal(file_ptr_cals);
                sugarTotal = calculateFileTotal(file_ptr_sugar);
                sodiumTotal = calculateFileTotal(file_ptr_sodium);
                proteinTotal = calculateFileTotal(file_ptr_protein);
                fatTotal = calculateFileTotal(file_ptr_fat);
                cholesterolTotal = calculateFileTotal(file_ptr_cholesterol);
              
                
                
                printf("--------------------------------------------------------------------------------------------");
                printf("n\nBelow are your total intakes for each nutrient, as well as a comparison to your daily intake goals.\n\n");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\n\nYou have consumed a total of %.1lf calories today.\n", calorieTotal);
                printf("\nYou have %.1lf calories REMAINING in the day to consume.\n", calculateRemaining(calorieTotal, recs, 0));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nYou have consumed a total of %.1lf grams of sugar today.\n", sugarTotal);
                printf("\nYou have %.1lf grams of sugar REMAINING in the day to consume.\n", calculateRemaining(sugarTotal, recs, 1));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nYou have consumed a total of %.1lf milligrams of sodium today.\n", sodiumTotal);
                printf("\nYou have %.1lf milligrams of sodium REMAINING in the day to consume.\n", calculateRemaining(sodiumTotal, recs, 2));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nYou have consumed a total of %.1lf grams of protein today.\n", proteinTotal);
                printf("\nYou have %.1lf grams of protein REMAINING in the day to consume.\n", calculateRemaining(proteinTotal, recs, 3));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nYou have consumed a total of %.1lf grams of fat today.\n", fatTotal);
                printf("\nYou have %.1lf grams of fat REMAINING in the day to consume.\n", calculateRemaining(fatTotal, recs, 4));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nYou have consumed a total of %.1lf milligrams of cholesterol today.\n", cholesterolTotal);
                printf("\nYou have %.1lf milligrams of cholesterol REMAINING in the day to consume.\n", calculateRemaining(cholesterolTotal, recs, 5));
                fclose(recs);
                recs = fopen("recs.txt", "r");
                
            }
            
            
            //User wants to exit the porgram for now, but does not want to end the day of tracking. Will exit the program.
            else if(answer == 4)
            {
                printf("--------------------------------------------------------------------------------------------");
                printf("\n\nBye For Now!\n\nCome Back Soon!\n\n\n");
                fclose(file_ptr_cals);
                fclose(file_ptr_sugar);
                fclose(file_ptr_sodium);
                fclose(file_ptr_protein);
                fclose(file_ptr_fat);
                fclose(file_ptr_cholesterol);
                
                fclose(recs);
                
                fclose(calTotals);
                fclose(sugarTotals);
                fclose(sodiumTotals);
                fclose(proteinTotals);
                fclose(fatTotals);
                fclose(cholesterolTotals);
                answer = 0;
            }
            
            
            //User wants to end today's tracking and recieve a daily and cumulative progress report.
            else if(answer ==5)
            {
                
                fclose(file_ptr_cals);
                fclose(file_ptr_sugar);
                fclose(file_ptr_sodium);
                fclose(file_ptr_protein);
                fclose(file_ptr_fat);
                fclose(file_ptr_cholesterol);
                fclose(recs);
                
                //re-eopeing the nutrient files in "read" mode
                file_ptr_cals=fopen("caloriesFile.txt","r");
                file_ptr_sugar= fopen("sugarFile.txt","r");
                file_ptr_sodium= fopen("sodiumFile.txt","r");
                file_ptr_protein= fopen("proteinFile.txt","r");
                file_ptr_fat= fopen("fatFile.txt","r");
                file_ptr_cholesterol=fopen("cholesterolFile.txt","r");
                
                //Opening the files that contain the daily totals for each nutrient so that we can add to them. These files will NEVER get wiped. Whenever option 5 is called, they will just be opened in "append" mode. We will also traverse these files, find the total, and divide by how many days have been tracked.
                calTotals = freopen("calTotals.txt", "a+",  calTotals);
                sugarTotals = freopen("sugarTotals.txt", "a+", sugarTotals);
                sodiumTotals = freopen("sodiumTotals.txt", "a+",sodiumTotals);
                proteinTotals = freopen("proteinTotals.txt", "a+",proteinTotals);
                fatTotals = freopen("fatTotals.txt", "a+", fatTotals);
                cholesterolTotals = freopen("cholesterolTotals.txt", "a+",cholesterolTotals);
                
                
                
                printf("\n\nBelow is a report on today's tracking, as well as cumulative reports on your average daily nutrient consumption\n\n");
                
                //Calculates out today's total for each nutrient and prints it out, and writes it into total file. Then, it calculates the cumulative avg for each nutrient(using the CalculateCumulativeAvg() function) and prints that out.
                calorieTotal = calculateFileTotal(file_ptr_cals);
                fprintf(calTotals, "%.2lf\n", calorieTotal);
                
                
                fclose(calTotals);
                calTotals = fopen("calTotals.txt", "r");
                
                daysTracked = calculateAmountDaysTracked(calTotals);
                fclose(calTotals);
                calTotals = fopen("calTotals.txt", "r");
                
                
                printf("--------------------------------------------------------------------------------------------\nCALORIES\n");
                printf("\n\nYou have consumed %.1lf calories today\n", calorieTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(calTotals);
                printf("\nYou have consumed an average of %.1lf calories per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
                
                
                sugarTotal = calculateFileTotal(file_ptr_sugar);
                fprintf(sugarTotals, "%.2lf\n", sugarTotal);
                
                fclose(sugarTotals);
                sugarTotals = fopen("sugarTotals.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------\nSUGAR\n");
                printf("\n\nYou have consumed %.1lf grams of sugar today\n", sugarTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(sugarTotals);
                printf("\nYou have consumed an average of %.1lf grams of sugar per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
                
                sodiumTotal = calculateFileTotal(file_ptr_sodium);
                fprintf(sodiumTotals, "%.2lf\n", sodiumTotal);
                
                fclose(sodiumTotals);
                sodiumTotals = fopen("sodiumTotals.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------\nSODIUM\n");
                printf("\n\nYou have consumed %.1lf milligrams of sodium today\n", sodiumTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(sodiumTotals);
                printf("\nYou have consumed an average of %.1lf milligrams of sodium per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
                
                proteinTotal = calculateFileTotal(file_ptr_protein);
                fprintf(proteinTotals, "%.2lf\n", proteinTotal);
                
                fclose(proteinTotals);
                proteinTotals = fopen("proteinTotals.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------PROTEIN\n");
                printf("\n\nYou have consumed %.1lf grams of protein today\n", proteinTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(proteinTotals);
                printf("\nYou have consumed an average of %.1lf grams of protein per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
                
                fatTotal = calculateFileTotal(file_ptr_fat);
                fprintf(fatTotals, "%.2lf\n", fatTotal);
                
                fclose(fatTotals);
                fatTotals = fopen("fatTotals.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------\nFAT\n");
                printf("\n\nYou have consumed %.1lf grams of fat today\n", fatTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(fatTotals);
                printf("\nYou have consumed an average of %.1lf grams of fat per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
                
                cholesterolTotal = calculateFileTotal(file_ptr_cholesterol);
                fprintf(cholesterolTotals, "%.2lf\n", cholesterolTotal);
                
                fclose(cholesterolTotals);
                cholesterolTotals = fopen("cholesterolTotals.txt", "r");
                
                printf("--------------------------------------------------------------------------------------------\nCHOLESTEROL\n");
                printf("\n\nYou have consumed %.1lf milligrams of cholesterol today\n", cholesterolTotal);
                cumulativeDailyAvg = calculateCumulativeAvg(cholesterolTotals);
                printf("\nYou have consumed an average of %.1lf milligrams of cholesterol per day over the past %d days.\n\n", cumulativeDailyAvg, daysTracked);
                
            
                printf("\n                                  Come back tomorrow!\n");
               
                
                fclose(file_ptr_cals);
                fclose(file_ptr_sugar);
                fclose(file_ptr_sodium);
                fclose(file_ptr_protein);
                fclose(file_ptr_fat);
                fclose(file_ptr_cholesterol);
                
                //opening these files in write mode will clear their contents before closing them again.
                file_ptr_cals=fopen("caloriesFile.txt","w");
                file_ptr_sugar= fopen("sugarFile.txt","w");
                file_ptr_sodium= fopen("sodiumFile.txt","w");
                file_ptr_protein= fopen("proteinFile.txt","w");
                file_ptr_fat= fopen("fatFile.txt","w");
                file_ptr_cholesterol=fopen("cholesterolFile.txt","w");
                
                fclose(file_ptr_cals);
                fclose(file_ptr_sugar);
                fclose(file_ptr_sodium);
                fclose(file_ptr_protein);
                fclose(file_ptr_fat);
                fclose(file_ptr_cholesterol);
                
                fclose(recs);
                
                fclose(calTotals);
                fclose(sugarTotals);
                fclose(sodiumTotals);
                fclose(proteinTotals);
                fclose(fatTotals);
                fclose(cholesterolTotals);
                
               
                answer = 0;
            }
            
            
        }
    //end of while loop
        
      
        return 0;
    }

