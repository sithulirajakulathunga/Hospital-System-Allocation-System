#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int patientOrder[100];
int patientCount = 0;
int patientBed[100];

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


// sort patient's by emergency priority
void sortByEmergencyPriority()
{
    int i,j;
    int temporaryValue;

    for (i=0; i<patientCount; i++)
    {
       patientOrder[i] = i;
    }
    for (i=0;i < patientCount-1;i++)
    {
        for(j=0; j<patientCount -1-i; j++)
        {
            if(emergencyLevel[patientOrder[j]]<emergencyLevel[patientOrder[j+1]])
            {
                temporaryValue= patientOrder[j];
                patientOrder[j] = patientOrder [j+1];
                patientOrder[j+1] = temporaryValue;

            }
        }
    }
}


// Display Final Bill

void DisplayFinalBill(int patientIndex)
{
    int specialty = patientSpecialty[patientIndex] -1;

    float basefee = consultationFee[specialty];
    float surcharge = calculateEmergencySurcharge(
        basefee,
        emergencyLevel[patientIndex]
    );
    float wardCost;

    if (admittedToWard[patientIndex]==1)
    {
        int ward = patientWard[patientIndex] -1;
        wardCost = calculateWardCost(
            admittedToWard[patientIndex],
            daysAdmitted[patientIndex],
            ward,
            wardDailyRate
        );
    }
    else
    {
        wardCost = 0;
    }

    float grossTotal = calculateGrossTotal(
            basefee,
            surcharge,
            wardCost
    );

    float discount = calculateAgeSubsidyDiscount(
        patientAge[patientIndex],
        grossTotal
    );

    float finalPayableAmount =  calculateFinalPayableAmount(
        grossTotal,
        discount
    );

    printf("\n==============================================================\n");
    printf("                SMART HOSPITAL ADMISSION & BILL\n");
    printf("--------------------------------------------------------------\n");

    printf("Patient ID             : PAT-100%d\n",patientIndex +1);
    printf("Patient Name           : %s\n",patientName[patientIndex]);
    printf("Age                    : %d Years",patientAge[patientIndex]);

    if (patientAge[patientIndex]<5 || patientAge[patientIndex]>65)
    {
        printf(" (15%% Subsidy Eligible)\n");
    }
    else
    {
        printf(" (0%% Subsidy Eligible)\n");
    }

    printf("Specialty              : %s\n",specialtyName[specialty]);


    if(admittedToWard[patientIndex]==1)
    {
        printf("Assigned Ward          : %s (Bed #%02d)\n",
               wardName[patientWard[patientIndex]-1],
               patientBed[patientIndex]);
    }
    else
    {
        printf("Assigned Ward          : None (OPD)\n");
    }

    printf("Urgency Level          : Level %d",emergencyLevel[patientIndex]);


    if (emergencyLevel[patientIndex]==1)
    {
        printf("(Normal)\n");
    }
    else if (emergencyLevel[patientIndex]==2)
    {
        printf("(Urgent)\n");
    }
    else if (emergencyLevel[patientIndex]==3)
    {
        printf("(Critical)\n");
    }

    printf("--------------------------------------------------------------\n");
    printf("Base Consulation Fee   : LKR %.2f\n",basefee);
    printf("Emergency Surcharge    : LKR %.2f",surcharge);
    if (emergencyLevel[patientIndex]==1)
    {
        printf("(0%%)\n");
    }
    else if(emergencyLevel[patientIndex]==2)
    {
        printf("(20%%)\n");
    }
    else if (emergencyLevel[patientIndex]==3)
    {
        printf("(50%%)\n");
    }
    printf("Ward Stay Cost (%d days): LKR %.2f\n",
            daysAdmitted[patientIndex],
            wardCost);
    printf("--------------------------------------------------------------\n");
    printf("Gross Total Bill       : LKR %.2f\n",grossTotal);
    if (patientAge[patientIndex] < 5 || patientAge[patientIndex] > 65)
    {
        printf("Age Subsidy Discount   : LKR -%.2f (15%%)\n",discount);
    }
    else
    {
        printf("Age Subsidy Discount   : LKR %.2f (0%%)\n",discount);
    }

    printf("--------------------------------------------------------------\n");
    printf("Final Payable Amount   : LKR %.2f\n",finalPayableAmount);
    if (waitingTime[patientIndex]==0)
    {
        printf("Estimated Waiting Time : %.2f mins (Immediate Attention)",(float)waitingTime[patientIndex]);

    }
    else
    {
        printf("Estimated Waiting Time : %.2f mins",(float)waitingTime[patientIndex]);
    }

    printf("\n==============================================================\n");
}

// Bed Allocation
int allocateBed(int ward)
{
    for(int i=0; i < bedCapacity[ward]; i++)
    {
        if(bedOccupancy[ward][i]==0)
        {
            bedOccupancy[ward][i]= 1;
            return i + 1;
        }
    }
    return 0;
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
                if (admittedToWard[patientCount]==1)
                {
                    printf("Please Enter Ward ID (1-4):");
                    scanf("%d", &patientWard[patientCount]);

                    printf("Please Enter Days Admitted: ");
                    scanf("%d", &daysAdmitted[patientCount]);

                    int ward = patientWard[patientCount] - 1;

                    patientBed[patientCount] = allocateBed(ward);

                    if(patientBed[patientCount]==0)
                    {
                        printf("No beds available in this ward.\n");
                        patientWard[patientCount]=0;
                        daysAdmitted[patientCount]=0;
                        patientBed[patientCount] = 0;
                        admittedToWard[patientCount]=0;
                    }
                   else
                   {
                       printf("Bed Allocated Successfully : Bed #%02d\n",patientBed[patientCount]);
                   }
                }

                else{
                    patientWard[patientCount]=0;
                    daysAdmitted[patientCount]=0;
                    patientBed[patientCount]=0;
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

              sortByEmergencyPriority();

              if (patientCount==0){
                printf("No Patients Registerd.\n");
              }
              else{
                for (int i =0; i<patientCount; i++)
                {
                    int patientIndex = patientOrder[i];

                    printf("Patient %d\n",patientIndex+1);
                    printf("Name: %s\n",patientName[patientIndex]);
                    printf("Age:%d\n",patientAge[patientIndex]);
                    printf("Emergency Level:%d\n",emergencyLevel[patientIndex]);
                    printf("Specialty ID:%d\n",patientSpecialty[patientIndex]);

                    if(admittedToWard[patientIndex]==1)
                    {
                    printf("Ward ID: %d\n", patientWard[patientIndex]);
                    printf("Days Admitted: %d\n", daysAdmitted[patientIndex]);
                    }

                    else
                    {
                     printf("Patient is not admitted to a ward (Outpatient/OPD)\n");
                    }

                    DisplayFinalBill(patientIndex);
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
