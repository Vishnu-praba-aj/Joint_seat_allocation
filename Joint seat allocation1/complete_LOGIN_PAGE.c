#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<strings.h>
#include "functions.h"



int student_login()
{
	
    char name[100];
	char password[100];
	int choice,i,j,allot,prefcheck=1,c=1;
	
	printf("Enter your Name:");
	scanf("%[^\n]s",name);
	getchar();
	
	printf("Enter your Password:");
	scanf("%[^\n]s",password);
	getchar();
	
	if(check_password(name,password)!=NULL) //Authentication of the student user and returns the register number(string) .
	{	
	  Student student,checkstd;
	  
	  strcpy(student.reg,check_password(name,password)); //storing the register number in the reg member of student stucture. 
	  printf("Your register number is:%s\n",check_password(name,password));
	  printf("Enter 1 for Choice Filling 2 for Allocation:");
	  scanf("%d",&allot);
	  
	  if (allot==1)
	  {
	    FILE *stdf=fopen("studentpreference.txt","rb");
	    while(fread(&checkstd,sizeof(Student),1,stdf))
	       { 
	        if (strcmp(checkstd.reg,student.reg)==0) //check whether the student has already given the prefernces
	           {  //int c;
	     	       printf("You have already given the preferences");
	     	       prefcheck=0;	
		       }
           }    
      fclose(stdf);
      
      if (prefcheck==1) //
	  {
	    printf("Enter 1 to stop giving prefences and 3 to change any of ur prefernces \n\n ");
	    initialize(student.pref); // this function initialises the elements of "pref" array of the student with zero.
	  
	  //format for the candidate to give preference as given here.
	    printf("***NOTE: Format is College Name with Branch(eg:iitmadras,cse)***\n");
	  
	    for (i=0;i<56;i++) //sice there are only "56" courses are available
	    {  
	       int advanced_check=0;
	       char college[100];
	       int flag=0;
	    
	  	    printf("Enter the Program:");
	  	    getchar();
	  	    scanf("%[^\n]s",college);
	  	    college[strcspn(college, "\n")] = '\0';
	  	
	  	
	        if (strcmp(college,"1")!=0)
	  	    {
	  	
	     	  if (!check_advanced(student.reg)) 
	  	      {
		        if (strstr(strupr(college),"IIT"))//if the candidate gives IIT colleges as preference without writing JEE advanced can not give IIT colleges as preference.
		        {
		          printf("You can't give IIT colleges since you have not written JEE Advanced.\n");
		          advanced_check=1;	
	            }
	          } 
	          
	          if (advanced_check!=1)
	          {
		        if (strcmp(college,"3")==0) //checking whether the input is 3(for editing the already given preferences.)
		        {
		            change_pref(student.pref); //function for editing
		            continue; // after editing again continuing with getting preferences
		        }
		        
		         
	  	        if (is_present(college) != -1) //check whether the given preference is valid.
	  	        {  //checks if the candidate have given the preference that has been given already. 
		           for (j=0;j<i+1;j++)
		           {
		  	            if(student.pref[j]==is_present(college))
		  	           { 
		  		            printf("*You have already entered this program*\n");
		  		            flag=1;
			           }
		           }
		           
		           if (flag!=1) //if the preference was not yet given.
		           { 
		  	            student.pref[i]=is_present(college); //assinging the preference in the "pref" array in the student structure
		           }
		           else
		           {
		        	    continue; //if the preference was already given then continue to ask preference
		           }
	           }
	           else // when an invalid preference is given
	           {
	                printf("Invalid Program Name\n");
	                
		            //showing institutes and the braches in the institutions to be more user friendly.	
	                printf("   Enter 1 to see the Institutes and Branches 2 to continue:");
	                scanf("%d",&choice);
	                if (choice==1)
	                {
	                	show();
		            }
	      	   }
	      	   
    	     }
        
	       } 
	       
	       else //when the input for preference is "1"(to stop giviing preference).
	      {
	     	break;
	      }	
	      
	   }
    
	   student.assigned=-1; 
	   student.next_choice=0;
	   
	   // writing the studnt structure to the file.
       FILE *fle=fopen("studentpreference.txt","a");
       fwrite(&student,sizeof(Student),1,fle);
	   fclose(fle);
    } 
    }
    
    
    if (allot==2) 
    { 
      display_alloted_program(student.reg);	//Displays the course for which the student ids alloted.
	}
	}
    
    else 
    {
	    printf("Incorrect Name or password!");
    }
    
    return 0;
}  



int college_login()
{   
    int i,j;
    int f=0;
	char name1[100];
	
	printf("Enter the College Name:");
	scanf("%[^\n]s",name1);
	
	FILE *cf=fopen("college_allotment.txt","r");

	for (i=0;i<=28;i++) // since only 28 colleges are there.
	{
	 
	 College clg;
	 fread(&clg,sizeof(College),1,cf);

	 
	 if (strstr(strupr(clg.name),strupr(name1))) //checking for all the courses in the given college name
	 { 
        f=1;
	    printf("%s\n",clg.name);
	    
	 
	    printf("No. of Students Alloted to this Branch: %d\n",clg.num_stu);	//shows how many students have been alotted to the particular branch in the particular college.
	    
	    for (j=0;j<clg.num_stu;j++)
	    {  
	       check_pass(clg.assigned_stu[j]); // displays the students who are assigned for that course.  
        }
        
        //gives the info that the seats of that branch in that institute have been filled.
        if (clg.capacity==clg.num_stu)
	    {
	    	printf("All Seats were filled in this Branch.\n");
		}
		
		else
		{
			printf("The no of available seats in the branch is %d\n",clg.capacity-clg.num_stu);
		}
		
     }
	}
	
	if (f==0)
	{
		printf("Invalid college name");
	}
	
	fclose(cf);
	return 0;
}


int main()
{   
    char roll;
    printf("-------------------------------------------------------\n");
    printf("------------JOINT SEAT ALLOCATION AUTHORITY----------\n");
    printf("-------------------------------------------------------\n");
	printf("LOGIN PAGE\n");
	
    jump:
	//user interface module
	printf("ENTER S TO LOGIN AS A STUDENT\nENTER C TO LOGIN AS A COLLEGE ADMIN:");
	scanf("%c",&roll);
	getchar();
	
	switch(toupper(roll))
    {
    	case 'S' :
	    {
	    	student_login();
    		break;
		}
		
		case 'C' :
		{
			college_login();
			break;
		}
		
		default :
			{
				printf("Invalid choice");
				goto jump;
			}
	}
	return 0;
}
