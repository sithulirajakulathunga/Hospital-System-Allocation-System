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
char patientName[100][50];
int patientAge[100];
int emergencyLevel[100];
int patientSpecialty[100];
int admittedToWard[100];
int daysAdmitted[100];
int patientWard[100];
int specialyQueueCount[4]={0};
int waitingTime[100];
int patientCount = 0;

// Calculate waiting time
int calculateWaitingTime(int specialyQueueCount,int consultationTime)
{
        return specialyQueueCount * consultationTime;
}

// Calculate Emergency Surcharge
float calculateEmergencySurcharge(float basefee,int emergencyLevel)
{
    if (emergencyLevel == 1){
        return 0;
    }
    else if (emergencyLevel == 2){
        return basefee * 0.20;
    }
    else if (emergencyLevel == 3){
        return basefee * 0.50;
    }
    return 0;
}


// Calculate Ward Cost
float calculateWardCost(int admittedToWard,int daysAdmitted,int ward,float wardDailyRate[])
{
    if (admittedToWard == 1){
        return daysAdmitted * wardDailyRate [ward];
    }
    else{
        return 0;
    }
}


// Calculate Gross Total
float calculateGrossTotal(float basefee,float surcharge,float wardCost)
{
    return basefee + surcharge + wardCost;
}


// Calculate Age Subsidy Discount
float calculateAgeSubsidyDiscount(int age,float grossTotal)
{
    if(age<5 || age > 65)
    {
        return grossTotal * 0.15;
    }
    else
    {
        return 0;
    }
}

// Calculate Final Payable Amount
float calculateFinalPayableAmount(float grossTotal,float discount)
{
    return grossTotal - discount;
}

int main()
{
    int choice;
    do{

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
              printf("======== Patient Registration ========\n");
              printf("Please Enter Patient Name:  ");  //patient details
              scanf(" %[^\n]",patientName[patientCount]);
              printf("Please Enter Patient Age:  ");
              scanf("%d", &patientAge[patientCount]);
              printf("Please Enter Emergency Level (1=Normal, 2=Urgent, 3=Critical,):");
              scanf("%d", &emergencyLevel[patientCount]);
              printf("Please Enter Specialty ID (1-4):");
              scanf("%d", &patientSpecialty[patientCount]);

              int specialty = patientSpecialty[patientCount]-1;

              waitingTime[patientCount]= calculateWaitingTime(
                        specialyQueueCount[specialty],
                        consultationTime[specialty]
              );

              printf("Estimated Waiting Time: %d minutes\n", waitingTime[patientCount]);
              specialyQueueCount[specialty]++;

              printf("Is Patient Admitted to the Ward? (1=Yes, 0=No):");
              scanf("%d", &admittedToWard[patientCount]);// ward details
                   if (admittedToWard[patientCount]==1){
                    printf("Please Enter Ward ID (1-4):");
                    scanf("%d", &patientWard[patientCount]);
                    printf("Please Enter Days Admitted: ");
                    scanf("%d", &daysAdmitted[patientCount]);
                   }
                   else{
                    patientWard[patientCount]=0;
                    daysAdmitted[patientCount]=0;
                   }

                   // bill calculation
                   float surcharge;
                   float basefee;
                   float wardCost;
                   float grossTotal;
                   float discount;
                   float finalPayableAmount;

                   basefee = consultationFee[specialty];

                   surcharge = calculateEmergencySurcharge(
                        basefee,
                        emergencyLevel[patientCount]
                   );

                   int ward = patientWard[patientCount] - 1;

                   wardCost = calculateWardCost(
                        admittedToWard[patientCount],
                        daysAdmitted[patientCount],
                        ward,
                        wardDailyRate
                   );

                   grossTotal = calculateGrossTotal(
                        basefee,
                        surcharge,
                        wardCost
                   );

                   discount = calculateAgeSubsidyDiscount(
                        patientAge[patientCount],
                        grossTotal
                   );

                   finalPayableAmount = calculateFinalPayableAmount(
                        grossTotal,
                        discount
                   );


                   printf("Base Consaltation Fee = %.2f\n ",basefee);
                   printf("Emergency Surcharge   = %.2f\n ",surcharge);
                   printf("Ward Cost   = %.2f\n ",wardCost);
                   printf("Gross Total = %.2f\n ",grossTotal);
                   printf("Age Subsidy Discount = %.2f\n",discount);
                   printf("Final Amount Payable = %.2f\n",finalPayableAmount);

                   patientCount++;
                   printf("Patient Registration is Successful!\n");

              break;

          case 2:
              printf("======== Bed Availability ========\n");
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
              printf("======== Patient Records ========\n");
              if (patientCount==0){
                printf("No Patients Registerd.\n");
              }
              else{
                for (int i =0; i<patientCount; i++){
                    printf("Patient %d\n", i+1);
                    printf("Name: %s\n",patientName[i]);
                    printf("Age:%d\n",patientAge[i]);
                    printf("Emergency Level:%d\n",emergencyLevel[i]);
                    printf("Specialty ID:%d\n",patientSpecialty[i]);
                            if(admittedToWard[i]==1){
                                printf("Ward ID: %d\n",patientWard[i]);
                                printf("Days Admitted: %d\n", daysAdmitted[i]);
                            }
                            else {
                                printf("Patient is not admitted to a ward (Outpatient/OPD)\n");
                            }
                }
              }
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
     }while(choice !=5);
    return 0;

}
