#include <stdio.h>
#include <stdlib.h>

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
              printf("Bed Availability Selected\n");
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
