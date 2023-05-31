#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>

struct user {
    char phone[50];
    char ac[50];
    char password[50];
    char password1[50];
    float balance;
    char name[50];
};

int main(){
    long long random_value;
    long long lower=10000000000,upper=99999999999;
    struct user usr,usr1;
    struct stat fileInfo;
    
    char filepath[100];
    
    FILE *fp;
     FILE *data;
    char filename[50],phone[50],pword[50],filename1[50],filename2[50],pword1[50],pword2[50];
    int opt,choice;
    char cont = 'y';
    float amount;
    
    printf("--------------------------------------------------------------------------------------\n");
    printf("                                welcome to UDYOJIT bank                           \n");
    printf("---------------------------------------------------------------------------------------\n");
    
    printf("\nWhat do you want to do?");
    printf("\n\n1. Register an account");
    printf("\n2. Login to an account");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);

    if(opt == 1){
        printf("\n                                        WELCOME TO THE REGISTRATION PORTAL\n                         ");
        
        printf("\nEnter your phone number:\t");
        scanf("%s",usr.phone);
         sprintf(filepath,"%s.txt",usr.phone);
        if (stat(filepath, &fileInfo) == 0) {
        printf("phone number'%s' already registered.\n", usr.phone);
        
        }else{
        printf("Enter your password:\t");
        scanf("%s",usr.password);
        
         printf("confirm password:\t");
         
        scanf("%s",usr.password1);
          
        if(strcmp(usr.password,usr.password1)==0){
        usr.balance = 0;
        strcpy(filename,usr.phone);
        printf("Enter Your Name: ");
        scanf("%s",usr.name);
        sprintf(filepath,"%s.txt",filename);
       
        fp = fopen(strcat(filename,".txt"),"w");
          
        fwrite(&usr,sizeof(struct user),1,fp);
        
        if(fwrite!=0){
            printf("\n\nAccount succesfully registered\n");
             srand(time(NULL)); // seed the random number generator with the current time
               random_value  =(rand()%(upper-lower+1))+lower;
 
    printf("your Account Number is: %d\n", random_value); // output the random value
        }
        }else {
            printf("\n\nSomething went wrong please try again");
        }
        
        }
        
        fclose(fp);
    }
    if(opt == 2){

        printf("\n                                        WELCOME TO LOGIN PAGE\n                    ");
        
        printf("\nPhone number:\t");
        scanf("%s",phone);
        printf("Password:\t");
        scanf("%s",pword);
        strcpy(filename,phone);
        fp = fopen(strcat(filename,".txt"),"r");
        if(fp == NULL){
            printf("\nAccount number not registered");
        }
        else {
        fread(&usr,sizeof(struct user),1,fp);
        fclose(fp);
        if(!strcmp(usr.password,pword)){
            printf("\n\t\t Welcome %s to UDYOJIT bank\n",usr.name);;
            while(cont == 'y'){
                
                printf("\n\nPress 1 for balance inquiry");
                printf("\nPress 2 for depositing cash");
                printf("\nPress 3 for cash withdrawl");
                printf("\nPress 4 for online transfer");
                printf("\nPress 5 for password change");
                printf("\n\nYour choice:\t");
                scanf("%d",&choice);

                switch(choice){
                    case 1:
                        printf("\nYour current balance is Rs.%.2f",usr.balance);
                        break;
                    case 2:
                        printf("\nEnter the amount:\t");
                        scanf("%f",&amount);
                        usr.balance += amount;
                        fp = fopen(filename,"w");
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL) printf("\nSuccesfully deposited.");
                        fclose(fp);
                        break;
                    case 3:
                        printf("\nEnter the amount:\t");
                        scanf("%f",&amount);
                        if(usr.balance>=amount){
                        usr.balance -= amount;
                        fp = fopen(filename,"w");
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL) printf("\nYou have withdrawn Rs.%.2f",amount);
                        }else{
                            printf("Insufficient balance");
                        }
                        fclose(fp);
                        break;

                    case 4:
                        printf("\nPlease enter the phone number to transfer the balance:\t");
                        scanf("%s",phone);
                        strcpy(filename,phone);
                        fp = fopen(strcat(filename,".txt"),"r");
                        if(fp == NULL) {
                            printf("\nAccount number not registered");
                        }else{
                        printf("\nPlease enter the amount to transfer:\t");
                        scanf("%f",&amount);
                        fread(&usr1,sizeof(struct user),1,fp);
                        printf("\nyou are transferring money to %s do you want to continue(y/n): ",usr1.name);
                        char choose;
                        scanf("%s",&choose);
                       if(choose=='y'){
                        strcpy(filename,phone);
                        fp = fopen(strcat(filename,".txt"),"r");
                        if(fp == NULL) printf("\nAccount number not registered");
                        
                            fread(&usr1,sizeof(struct user),1,fp);

                        fclose(fp);
                        if(amount > usr.balance) printf("\nInsufficient balance");
                        else {


                            fp = fopen(filename,"w");
                            usr1.balance += amount;
                            fwrite(&usr1,sizeof(struct user),1,fp);

                            fclose(fp);
                            if(fwrite != NULL){
                                printf("\nYou have succesfully transfered Rs.%.2f to %s",amount,phone);
                                strcpy(filename,usr.phone);
                                fp = fopen(strcat(filename,".txt"),"w");
                                usr.balance -= amount;
                                fwrite(&usr,sizeof(struct user),1,fp);
                                fclose(fp);
                            }
                        }

                        }
                        break;
                 case 5:
                 printf("\nPlease enter your old password:\t");
                      scanf("%s",pword1);
                      if(strcmp(usr.password,pword1)==0){
                        printf("\nPlease enter your new password:\t");
                        scanf("%s",pword2);
                        fp = fopen(filename,"w");
                        strcpy(usr.password,pword2);
                
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL)
                        printf("\nPassword succesfully changed");
                        }else{
                            printf("wrong password");
                        }
                        }
                    break;
                default:
                    printf("\nInvalid option");
                }


                printf("\nDo you want to continue the transaction [y/n]\t");
                scanf("%s",&cont);

            }
        }
        else {
            printf("\nInvalid password");
        }
        }

    }


    return 0;
}

