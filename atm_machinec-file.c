#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include "array.h"
#include "array.c"
#include <ncurses.h>



int main(){
   char * adminUser = "Admin";
    int adminPass = 1234;
    int running;
    array * users = newArray();
    int intInput;
    char password[9],c;
    double doubleInput;
    int output;
    char stringInput[50];
    size_t index, index_2;
    int err;

    printf("\nWelcome to ECEN1310 ATM Machine!\n");
    running = 1;

    // Main Loop
    while(running) {

        // First Menu
        printf("\nEnter a choice:\n");
        printf("1- Admin Login\n");
        printf("2- Customer Login\n");
        printf("3- Exit\n");
        printf("> ");
        scanf("%d", &intInput);
        flush(stdin);
	if(intInput == 1) {     // Admin Login
            printf("\n** Admin Login **\n");
            printf("username: ");
            scanf("%49[^\n]s", stringInput);
            flush(stdin);
	    printf("password:");
	    int i=0;
	    while( (c=getch())!= '\n');{
           password[i] = c;
           printf("*");
          i++;
          }
	    flush(stdin);
            printf("\nLogging in as %s...", stringInput);
            if(strcmp(stringInput, adminUser) != 0 || password != adminPass) {
      
		  
	    
                printf("\nInvalid username or password.\n");
                continue;
            }
            printf("\nLogin succesful! Welcome, %s.\n", stringInput);
  
            // Admin menu loop start
            do {
                printf("\nEnter a choice:\n");
                printf("1- Add Customer\n");
                printf("2- Delete Customer\n");
                printf("3- Log Out\n");
                printf("> ");
                scanf("%d", &intInput);
                flush(stdin);

                if(intInput == 1) {         // Create new customer
                    printf("\nAdding new customer...\n");
                    newUser(users);
                } else if(intInput == 2) {   // Delete customer
                    printf("\nEnter username of account to delete: ");
                    scanf("%49[^\n]", stringInput);
                    flush(stdin);
                    
                    err = checkUsername(users, stringInput, &index);
                    if(err == 0) {
                        printf("User %s not found.\n", stringInput);
                        continue;
                    } else {
		      userDelete(users, index);
                    }
                   
                    printf("Successfully deleted user (%s).\n", stringInput);
                } else if(intInput == 3) {    // Log Out
                    printf("Logging out...\n");
                } else {    // Invalid
                    printf("Invalid choice.\n");
                }
            } while (intInput != 3);
        }     // Admin menu loop end
	else if(intInput == 2) {    // Customer Login
            printf("\n** Customer Login **\n");
            printf("username: ");
            scanf("%49[^\n]", stringInput);
            flush(stdin);
            printf("password: ");
            scanf("%d", &intInput);
            flush(stdin);
            printf("Logging in as %s...\n", stringInput);
            
            err = checkPasswordUsername(users, stringInput, intInput, &index);

            if(err) {
                printf("Invalid username or password.\n\n");
                continue;
            }
            
            printf("Login succesful! Welcome, %s.\n", stringInput);
	    // printf("index = %d\n", index); checked
	 // Customer menu loop start
            do {
                printf("\nEnter a choice:\n");
                printf("1- Cash Deposit\n");
                printf("2- Cash Withdrawal\n");
                printf("3- View Customer Information\n");
                printf("4- Edit Customer Information\n");
                printf("5- Cash Transfer\n");
                printf("6- Log Out\n");
                printf("> ");
                scanf("%d", &intInput);
                flush(stdin);

                if(intInput == 1) {     // Deposit
                    printf("\n** Cash Deposit **\n");
                    printf("Enter deposit amount: $");
                    scanf("%lf", &doubleInput);
                    flush(stdin);
                    if (doubleInput <= 0) {
                        printf("Invalid amount.\n");
                        continue;
                    }
                   
                    userBalancePut(users, index, doubleInput);
                    printf("Deposited $%lf successfully.\n", doubleInput);
		    userBalanceGet(users, index, &output);
                } // exit deposit
		else if(intInput == 2) {  // Withdrawal
                    printf("\n** Cash Withdrawal **\n");
                    printf("Enter withdraw amount: $");
                    scanf("%lf", &doubleInput);
                    flush(stdin);
                    if (doubleInput <= 0) {
                        printf("Invalid amount.\n");
                        continue;
                    }
                    doubleInput = doubleInput * (-1);
                    err = userBalancePut(users, index, doubleInput);

		    if( err == 0){
		     printf("Withdrawn $%lf successfully.\n", doubleInput);
		     printf("Please take your money.\n");}
		    else{
		      printf("Transaction failed!\n");
		    }
		
                } // exit withdraw 
		else if(intInput == 3) {     // View info
                     printUserInfo(users,index);                 
                } // exit view info
		else if(intInput == 4) { 
                     editUser(users,index);
                } // exit edit
		else if(intInput == 5) {     // Transfer
                    printf("\n** Cash Transfer **\n");
		    
                    printf("Enter transfer amount: $");
                    scanf("%lf", &doubleInput);
                    flush(stdin);
		    
                    if (doubleInput <= 0) {
                        printf("Invalid amount.\n");
                        continue;
                    }
		    
                    printf("Enter username of recipient: ");
                    scanf("%49[^\n]", stringInput);
                    flush(stdin);
                   
                    err = checkUsername(users, stringInput, &index_2);
                    if(err == 0) {
                        printf("User does not exist.\n");
                        continue;
                    } else if(index_2 == index) {
                        printf("Cannot transfer cash to yourself!\n");
                        continue;
                    }

                    cashTransfer(users, index, index_2, (size_t) doubleInput);
                   
                } // exit tranfer 
		else if(intInput == 6) {     // Log Out
                    printf("Logging out...\n");
                }
		else {    // Invalid
                    printf("Invalid choice.\n");
                }
            } while (intInput != 6);    // Customer menu loop end
        } else if(intInput == 3) {     // Exit
            running = 0;
        } else {                       // Invalid Choice
            printf("Invalid choice.\n");
        }
    }


    printf("\nThanks for using our ECEN1310 ATM Machine!\nPlease come again .. Enjoy your day!\n\n");
    deleteArray(users);

    return 0;
}
