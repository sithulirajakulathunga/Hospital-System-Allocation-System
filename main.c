#include <stdio.h>
#include <stdlib.h>

int specialtyID[]= {1,2,3,4};
char specialtyName [][40]={
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};
float consultationFee[]={
    1500.00,
    2500.00,
    4500.00,
    5000.00
};
int consultationTime[]={15,20,30,30};
int dailyPatientCap[]= {30,20,12,10};
int wardID[]={1,2,3,4};
char wardName[][40]={
     "General Ward",
     "Paediatric Ward",
     "Surgical Ward",
     "ICU"
};
float wardDailyRate[]={
     3000.00,
     6000.00,
     12000.00,
     25000.00
};
int bedCapacity[]={20,10,10,5};
int bedOccupancy[4][20]={0};


int main()
{
    int choice;

    printf("=========================================================\n");
    printf("     Smart Hospital & Resource Allocation System\n");
    printf("=========================================================\n");

       printf("1.Register Patient\n");
       printf("2.Display Bed Availability\n");
       printf("3.View Patient Records\n");
       printf("4.Generate Reports\n");
       printf("5.Exit\n");
       scanf("%d",&choice);

       switch(choice){
          case 1:
              printf("Patient Registration Selected\n");
              break;
          case 2:
              printf("========Bed Availability========\n");
                for (int i=0; i<4; i++){
                    printf("%s:\n",wardName[i]);
                    for(int j=0; j< bedCapacity[i];j++){
                        if(bedOccupancy[i][j]==0){
                            printf("Bed %02d is Available\n",j+1 );
                        }
                        else{
                            printf("Bed %02d is Occupied\n",j+1);
                        }

                    }
                }
                break;

          case 3:
              printf("Patient Records Selected\n");
              break;
          case 4:
              printf("Generate Reports Selected\n");
              break;
          case 5:
              printf("Exit From The System\n");
              break;
          default:
              printf("Invalid Choice,Please Try Again.\n");
     }
    return 0;

}
