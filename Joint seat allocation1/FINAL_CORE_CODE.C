//                                                        main program
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINES 1000
#define MAX_LENGTH 100
#define MAX_LINE_LENGTH 1000
#include "functions.h"


// 1.returns thre rank of the student according to their college choice (preferences) (nit ot iit)
int rank( char reg[],int college_choice)
{
    FILE *the_file;
    char line[1000];
    // User input
    reg[strcspn(reg, "\n")] = '\0'; // Remove newline character
    int columnChoice;
    
    if (college_choice>16)
       columnChoice=1; 
    else
       columnChoice=2;
       
    the_file = fopen("C:\\Users\\varsh\\AppData\\Roaming\\Microsoft\\Windows\\Network Shortcuts\\Ranklist.csv", "r");
    if (the_file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1; // Indicate an error occurred
    }

    while (fgets(line, sizeof(line), the_file))
    {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        // Tokenize the line
        char *token;
        token = strtok(line, ",");

        // Check if the first column value matches the specified name
        if (strcmp(trim(token), trim(reg)) == 0)
        {
            // Get the corresponding column value based on the user's choice
            token = strtok(NULL, ",");
            if (token != NULL)
            {
                if (columnChoice == 1)
                {
                    int firstColumnValue = atoi(trim(token));
                    fclose(the_file);
                   
                    return firstColumnValue;
                }
                else if (columnChoice == 2)
                {
                    token = strtok(NULL, ",");
                    if (token != NULL)
                    {
                        int secondColumnValue = atoi(trim(token));
                        fclose(the_file);
                        return secondColumnValue;
                    }
                }
                else
                {
                    printf("Invalid column choice.\n");
                    break;
                    return 0;
                }
            }
        }
    }
}

//  2.sorting the already assigned students according to their rank.
void sort(char assigned_stu[][100],int num_stu,int college_choice)
{

	int i,j,a;
	for (i=0;i<num_stu-1;i++)
	{
		for(j=i;j<num_stu-i-1;j++)
		{
		if (rank(assigned_stu[j],college_choice)>rank(assigned_stu[j+1],college_choice))
		{
			char temp[100];
			strcpy(temp,assigned_stu[j]);
			strcpy(assigned_stu[j],assigned_stu[j+1]);
			strcpy(assigned_stu[j+1],temp);
		}
		}
	}
}

//   3.comparing the rank of the already assigned least rank candidate with current student's rank
int prefers(int choice,char current_stu[],char last_stu[])
{
	if(rank(current_stu,choice)<rank(last_stu,choice))
	{       
			return 1;
	}
	else
	{
		return 0;
	}
}


int main()
{  
    int i,j;
    Student studentarr[no_of_students()];
    
    FILE *fle = fopen("studentpreference.txt", "rb");
    
    for (i=0;i<no_of_students();i++)
	{
    	fread(&studentarr[i], sizeof(Student), 1, fle);
    }
	fclose(fle);
	
	char file_path[100] = "D:\\college.txt";
    FILE* file = fopen(file_path, "r");
    
    if (file == NULL) 
	{
        printf("Unable to open the file.\n");
        return 1; // Indicate an error occurred
    }
    
    char lines[MAX_LINES][MAX_LENGTH];
    char names[MAX_LINES][MAX_LENGTH];
    int digits[MAX_LINES];
    int num_lines = 0;
    char line[MAX_LENGTH];
    
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %d", names[num_lines], &digits[num_lines]);
        strcpy(lines[num_lines], line);
        num_lines++;
    }
    fclose(file);
    
    College collegearr[num_lines]; 
    for(i=0;i<num_lines;i++){
    	strcpy(collegearr[i].name,names[i]);
    	collegearr[i].capacity=digits[i];
    	collegearr[i].num_stu=0;
    	
	}
	
	int stable=0;
	//here stable is taken as 1 to check whether the preferred college of the candidate is allotted or not.
	//while(!stable)
	//{
	//stable=1;
	
	
	
	
	
	for(i=0;i<no_of_students();i++)
	{
	
		//assumed the assigned branch for all the candidates as -1.
		if(studentarr[i].assigned==-1)
		{
			int college_choice=studentarr[i].pref[studentarr[i].next_choice]-1; //getting the course code
			
			if(collegearr[college_choice].num_stu<collegearr[college_choice].capacity) //checking for the availability of seats for the given preference
			{
				strcpy(collegearr[college_choice].assigned_stu[collegearr[college_choice].num_stu],studentarr[i].reg); //alloting the student for that preference if seats are available
				studentarr[i].assigned=college_choice; 
				collegearr[college_choice].num_stu++; // incrementing the number of assigned students
				
			}
			
			else // when there is no seats available 
			{  
				sort(collegearr[college_choice].assigned_stu,collegearr[college_choice].num_stu,college_choice); // sorting the already assigned students
				char current_assignment[100]; // variable for the already assigned least rank student
				strcpy(current_assignment,collegearr[college_choice].assigned_stu[collegearr[college_choice].num_stu-1]);
				if(prefers(college_choice,studentarr[i].reg,current_assignment)) // check for swaping
				{    
					strcpy(collegearr[college_choice].assigned_stu[collegearr[college_choice].num_stu-1],studentarr[i].reg);// allot the student to that preference
					
					for(j=0;j<no_of_students();j++)
					{  
						studentarr[j].reg[strcspn(studentarr[j].reg, "\n")] = '\0';
						
		            	if(strcmp(current_assignment,studentarr[j].reg)==0)
		            	{
	                        studentarr[j].assigned=-1; // changing the assigned status of the least rank cabdidate
							studentarr[j].next_choice=studentarr[j].next_choice+1; // goes to next choice of the least rank cabdidate
							 // swaping
							studentarr[i].assigned=college_choice;
							Student temp;
							temp=studentarr[j];
							studentarr[j]=studentarr[i];
							studentarr[i]=temp;
							//decrementing i so that the least rank candidate after swaping again gets into the loop
							i=i-1;
							
							break;
							
						}
				   }
				   
			    }
				else // when can't swap
				{
					studentarr[i].next_choice++; // goes to next choice of the student 
					 
				}
			}
		}
	}
    //}
    // writing the alloted students with their alloted course in the file.
    FILE *f=fopen("Alloted.txt","wb");
    for(j=0;j<no_of_students();j++)
    {
    	fwrite(&studentarr[j],sizeof(Student),1,f);	
	}
	fclose(f);
	
	//writing the alloted students for each college course in the file
	FILE *f1=fopen("college_allotment.txt","wb");
    for(j=0;j<28;j++)
    {
    	fwrite(&collegearr[j],sizeof(College),1,f1);	
	}
	fclose(f);
	
	// reading the file to verify whethere the code runs 
	Student stud;
	FILE *fl=fopen("Alloted.txt","r");
	for(j=0;j<no_of_students();j++)
    {   	
    	fread(&stud,sizeof(Student),1,fl);
    	check_pass(stud.reg);
		write_clg(stud.assigned+1);
		printf("\n\n");
	}
		fclose(fl);
		
    return 0;
}
