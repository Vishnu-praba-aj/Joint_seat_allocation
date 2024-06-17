#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>

//                                STURCTURES
typedef struct {
    char reg[100];   //registration number
    int pref[100];   // array of preferences (each element is course code)
    int assigned;    //status of the student (assigned or not)
    int next_choice; //varbile used to point the index of the pref array
} Student;

typedef struct {
    char name[50];
    int capacity;
    char assigned_stu[100][100];
    int num_stu;
} College;


//                                                                        FUNCTIONS

//           1. function which initialises the elements in the prefe array as zero
initialize(int pref[])
{
	int i;
	for(i=0;i<56;i++)
	{
		pref[i]=0;
	}
}

//               2. returns number of students given their preferences
int no_of_students()
{    
    int count=0;
	Student s;
	
	FILE *sf=fopen("studentpreference.txt","rb");
	while(fread(&s,sizeof(Student),1,sf))
	{
		count+=1;
	}
	fclose(sf);
	
	return count;
}

//                        3. to trim the trailing spaces
char *trim(char *str)
{
    // Trim leading spaces
    while (*str == ' ')
    {
        str++;
    }

    // Trim trailing spaces and newline characters
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n'))
    {
        str[--len] = '\0';
    }

    return str;
}

//                  4. print student name according to their registration number
int check_pass( char* reg) 
{   int i;
    FILE* file = fopen("C:\\Users\\varsh\\AppData\\Roaming\\Microsoft\\Windows\\Network Shortcuts\\Ranklist.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
	 {
        // Tokenize the line using comma as the delimiter
        char* token = strtok(line, ",");
        
        // Compare the name in the first column
        if (strcmp(trim(token),trim(reg))== 0) 
		{
            // Move to the fourth column
            for ( i = 0; i < 3; i++) 
			{
                token = strtok(NULL, ",");
                if (token == NULL) 
				{
                    printf("Invalid file format.\n");
                    fclose(file);
                    return 0;
                }
            }
		    printf("%s\n",token);
            fclose(file);
            return 1;	
        }
    }
    
    fclose(file);
    return 0;
}

//                           5.write clg name eaccording to their clg code
void write_clg(int college)
{
	char file_path[100] = "D:\\college.txt";
    FILE* file = fopen(file_path, "r");
    char line[1000];
    while(fgets(line,sizeof(line),file))
    {
    	int count = 0;
        int current_college;
        char college_name[100];
        char* token = strtok(line, " ");
        while (token != NULL)
        {
            count++;
            if (count == 1)
            {
                strcpy(college_name, token);
            }
            else if (count == 3)
            {
                current_college = atoi(token);
                break;
            }
            
            token = strtok(NULL, " "); 
        }
        if (current_college == college)
        {
            printf("Congrats!! \nYou have been alotted to %s.",college_name);
            break;
        }
        
    }
    
    fclose(file);
    }
    
//                               6.It display the allotment status of a student    
void display_alloted_program(char name1[])
{
    int college,i,check=0;
    College clg;
	FILE *f2=fopen("Alloted.txt","r");
	for(i=0;i<no_of_students();i++)
	{
		Student s;
		fread(&s,sizeof(Student),1,f2);
	    
		if (strcmp(s.reg,name1)==0)
		{ //printf("%s",s.name);
		 check=1;
		 college=s.assigned+1;
		 if (s.assigned==-1)
		{
		 	printf("You are not alloted.\n");
		 	printf("The collegs with available seats are:\n");
		 	FILE *clg_file=fopen("college_allotment.txt","rb");
		 	for (i=0;i<28;i++)
		 	{
		 		fread(&clg,sizeof(College),1,clg_file);
		 		
		 		if (clg.capacity!=clg.num_stu)
		 		{
		 			printf("%s  %d\n",clg.name,clg.capacity-clg.num_stu);
				 }
			 }
			 fclose(clg_file);
		}
		 else
		{
		 //printf("%d",college);
		 write_clg(college);
     	}
		}
		
	}
	if (check!=1)
	{
		printf("you have not yet given the preferences");
	}
	fclose(f2);
}

//                   7.whether a given college is present in the file or not
int is_present(const char* flag) 
{
    FILE* file = fopen("D:\\college.txt", "r");
    if (file == NULL) 
	{
        printf("Unable to open the file.\n");
        return 0;
    }

    char line[1000];
    int num = -1; // Sentinel value to indicate number not found

    while (fgets(line, sizeof(line), file)) 
	{   
	    int i;
        // Convert both line and flag to uppercase for case-insensitive comparison
        char lineUpper[1000];
        char flagUpper[100];
        strcpy(lineUpper, line);
        strcpy(flagUpper, flag);
        for (i = 0; lineUpper[i]; i++) 
		{
            lineUpper[i] = toupper(lineUpper[i]);
        }
        for (i = 0; flagUpper[i]; i++)
		{
            flagUpper[i] = toupper(flagUpper[i]);
        }

        // Check if flag is present in the line
        if (strstr(lineUpper, flagUpper) != NULL) 
		{
            char* token;
            int count = 0;

            // Tokenize the line and extract the value after the second space
            token = strtok(line, " ");
            while (token != NULL) 
			{
                count++;
                if (count == 3)
				{
                    num = atoi(token);
                    break;
                }
                token = strtok(NULL, " ");
            }
            break; // Exit the loop after finding the line
        }
    }

    fclose(file);
    return num;
}

//                      8.check and returns jee advanced rank of the given student
int check_advanced( char name[])
{
    FILE *the_file;
    char line[1000];
    name[strcspn(name, "\n")] = '\0';
    int columnChoice=2;
    the_file = fopen("C:\\Users\\varsh\\AppData\\Roaming\\Microsoft\\Windows\\Network Shortcuts\\Ranklist.csv", "r");
    if (the_file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1; // Indicate an error occurred
    }

    while (fgets(line, sizeof(line), the_file))
    {   int i;
        line[strcspn(line, "\n")] = '\0';

        // Tokenize the line
        char *token;
        token = strtok(line, ",");

        // Check if the first column value matches the specified name
        if (strcmp(trim(token), trim(name)) == 0)
        {
        	for (i = 0; i < 2; i++) 
			{
                token = strtok(NULL, ",");
                if (token == NULL) 
				{
                    printf("Invalid file format.\n");
                    fclose(the_file);
                    return 0;
                }
            }
           
            return atoi(trim(token));
            
               
        }
        }
    }

//                     9.display the respective clgs when a wrong clg name is given
void show()
{
	FILE* the_file = fopen("D:\\college.txt", "r");
    if (the_file != NULL)
	{
        char line[1000];
        while (fgets(line, sizeof(line), the_file)) 
		{
            printf("%s", line);
        }
        fclose(the_file);
    }
        
}

//                   10.Authentication of the student
char* check_password(char* name, char* password) {
    FILE* file = fopen("C:\\Users\\varsh\\AppData\\Roaming\\Microsoft\\Windows\\Network Shortcuts\\Ranklist.csv", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int i;
        // Tokenize the line using comma as the delimiter
        char* token = strtok(line, ",");
        
        // Get the roll number from the first column
        char* roll_number = trim(token);

        // Skip the next three columns (name, password, and some other data)
        for (i = 0; i < 3; i++) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                printf("Invalid file format.\n");
                fclose(file);
                return NULL;
            }
        }

        // Compare the name in the 4th column
        if (strcmp(trim(token), trim(name)) == 0) {
            // Move to the 5th column (password column)
            token = strtok(NULL, ",");
            if (token == NULL) {
                printf("Invalid file format.\n");
                fclose(file);
                return NULL;
            }
            
            // Compare the password in the 5th column
            if (strcmp(trim(token), trim(password)) == 0) {
                fclose(file);
                return roll_number; // Return the roll number if both name and password match
            } else {
                fclose(file);
                return NULL; // Password doesn't match
            }
        }
    }
    
    fclose(file);
    return NULL; // Name not found
}

//                    11.Editing the preferences
void change_pref(int prefe[])
{
	char college[100];
	char clg[100];
	int num1,num2,i;
	printf("enter the college name to be changed:");
	scanf("%s",college);
	num1=is_present(college);
	while(prefe[i]!=0)
	{
		if (num1==prefe[i])
		{printf("enter the clg to be added:");
	    scanf("%s",clg);
	    num2=is_present(clg);
		prefe[i]=num2;	
		}
		i+=1;
	}
		
}
