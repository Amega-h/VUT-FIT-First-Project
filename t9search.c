                                    /*
                    Bogdan Shaposnik (xshapo04)
            shaposhnikbogdan@gmail.com or xshapo04@vutbr.cz
                                29.10.2022
                               Project 1 IZP
                Cvičujici : Grezl Frantisek,Ing.,Ph.D.
     RADME file and tests txts you will see on my merlin server in Project1IZP foulder 
                                    */

//Including all the libraries we need
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//Declaration of all the functions we have
bool CheckErrSymb(char argv[]);
int CountChar(char ArrChar[],char charperson);
char ContactTransform(char person[],int cyclus);
void Search (int argc,char *argv[]);

//Main function checks all the errors we could have at the beginning of the programm 
int main (int argc, char *argv[]) 
{
        if (argc > 2) // If quantity of argumetns is more than 2 , then print Error message and ends the whole function 
        {
            fprintf(stderr,"Too many arguements! Enter 1 only");
            return 1;
        } else if (argc > 1 && !CheckErrSymb(argv[1])) // checks if Argument has something that is not a number , if so , prints error message
        {
            fprintf(stderr,"Wrong arguement! Enter numbers only!");
            return 1;
        } else 
            { 
                Search(argc,argv);// if everithing alright , starts the search function
            }
}

bool CheckErrSymb(char argv[]) //function that checks if in arguement nothing but numbers
{
        bool NumCheck = true;
        for (int i=0;i<CountChar(argv,'\0');i++)//For goes till reach the end of the main arguement (our numbers that we are searching)
        {
            if (argv[i]<'0' || argv[i]>'9')//check for other symbols itself
            {
                NumCheck = false;
            }
        }
    return NumCheck;//returns true if it didnt find anything or false if in arguement is something except numbers
}

int CountChar(char ArrChar[],char charperson)//have loop untill reach the defined char symbol in defined char array
{
  int Lastchar = 0;
        while (ArrChar[Lastchar] != charperson)
        {
            Lastchar++;
        }
  return Lastchar;
}

/* Transform one char symbol in its number equivalent .If it finds (abs) , transforms it in '2' ,if (def) in '3' etc.
Also if it finds SPACE it remains the same symbol , because we dont want to have other errors
*/
char ContactTransform(char person[],int cyclus)
{
    char temp = ' ';//described upper
            if (person[cyclus]==' ')
            {
                return temp;
            }
    char numbers[27] = {'2','2','2','3','3','3','4','4','4','5','5','5','6','6','6','7','7','7','7','8','8','8','9','9','9','9'};
    /* We have char array that has amount equivalent to amount of letters we have. 
    Then , following ASCII table , we take letter , which has already been transformed into its lower case 
    using function tolower(), and subtracting from the ASCII meaning of given letter 97 . That is why for
    'a' we will have index 0 for 'b' index 1 and so on and so forth, so that each letter will have its own index
    in numbers[] array */
    temp = numbers[(tolower(person[cyclus])) - 97];
    return temp;
}

void Search (int argc,char *argv[])
{
    char person[102];// Person`s name , that will be rewritten every time in while
    char number[102];// Person`s number , that will be rewritten every time in while
    int notfound = 0;// Varibale, which shows us , wheter we found something(meaning >1) or not(meaning == 0)
            while (fgets(person,102,stdin) != NULL) // start of the loop , which scans the whole seznam
            {
                person[CountChar(person,'\n')] = '\0';// we cut the char array we got , not to have lots of emty space in it
                if(fgets(number,102,stdin) == NULL)
                {
                    printf("There is an error in your phone list\n");
                    break;
                }
                number[CountChar(number,'\n')] = '\0';// we cut the char array we got , not to have lots of emty space in it
                if (argc == 1)
                {
                    printf("%s,%s\n", person, number);//if you dont enter any number in your arguement ,prints all the phone list
                }
                if (argc == 2)
                {
                    char person_num[strlen(person)]; // char array for already transformed into number form person`s name
                    for (size_t i = 0;i < strlen(person);i++)// loop that actually transform all the line into number form
                    {
                        person_num[i] = ContactTransform(person,i);
                    }
                    if (strstr(person_num , argv[1]) != NULL) //if it found contact by name , prints its name and number into stdout
                    {
                        printf("%s , %s\n",person,number);
                        notfound++;//cancells the NOT FOUND case activation
                    } else
                    {
                        char number1[strlen(number)];//creates new char array for transformed numbers
                        strcpy(number1,number);//copies number[] array in number1[] array
                        if (number1[0]=='+')//it is for cases if the phone number starts with '+'. We make it to include all the conditions
                            number1[0] = '0';//which are described in Project`s aims
                        if (strstr(number1 , argv[1]) !=NULL)//if it found contact by number , prints its name and number into stdout
                        printf(" %s , %s\n",person,number);
                        notfound++;//cancells the NOT FOUND case activation
                    }

                }
            }
        if ((notfound == 0) && (argc == 2))
        fprintf(stderr,"NOT FOUND\n"); //checks wheter we actually found someting or not , if not , prints error message "NOT FOUND"
}