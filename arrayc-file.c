#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "array.h"

struct _array {
  size_t capacity; /* elements allocated */
  size_t inUse;    /* elements currently in use */
  user * data;    /* actual data */
};

struct _user {
    char name[50];
    char address[50];
    int age;
    double phone_num;
    double balance;
    char username[50];
    int password;
    double account_num;
};

array * newArray(void) {
  array * a;
  a = (array *) malloc(sizeof(array));
  if (!a) return NULL;
  a->capacity = 1; /* parsimonious */
  a->inUse = 0;
  a->data = (user*) malloc(sizeof(user) * a->capacity);
  if (!a->data) {
    free(a);
    return NULL;
  }
  return a;
}

void deleteArray(array * a) {
  if (a) {
    free(a->data);
    free(a);
  }
}

int resizeArray(array * a, size_t newSize) {
  if (!a) return -1;
  if (newSize > a->capacity) {
    /* To avoid too many calls to realloc, we choose the larger of
     * twice the current size and the new requested size. */
    size_t newCapacity = 2 * a->capacity;
    if (newCapacity < newSize)
      newCapacity = newSize;
    user* tmp = (user *) realloc(a->data, newCapacity * sizeof(user));
    /* If the allocation fails, leave the array alone. */
    if (!tmp) return -1;
    a->data = tmp;
    a->capacity = newCapacity;
  }
  /* Here we are guaranteed that newSize <= a->capacity. */
  a->inUse = newSize;
  return 0;
}

int arrayNum(array const * a, size_t * num) {
  if (!a || !num) return -1;
  *num = a->inUse;
  return 0;
}

int arrayGet(array const * a, size_t index, user* e) {
  if (!a || !e || index >= a->inUse) return -1;
  *e = a->data[index];
  return 0;
}

int arrayPushBack(array * a, user e) {
  if (!a) return -1;
  if (resizeArray(a, a->inUse + 1)) return -1;
  /* Now we have space. */
  a->data[a->inUse-1] = e;
  return 0;
}

void flush(FILE * input) {
    int c;
    while( (c = fgetc(input)) != '\n' && c != EOF);
}

/* This function has to ask the user to type all the
information and then call the function arrayPuchBack to add this information
in the array. */

int newUser(array *a){
    user u;
    int err;
    size_t index;

    printf("Enter name: ");
    scanf("%49[^\n]",u.name);
    flush(stdin);

    printf("Enter address: ");
    scanf("%49[^\n]",u.address);
    flush(stdin);

    printf("Enter age: ");
    scanf("%d",&u.age);
    flush(stdin);


    printf("Enter phone number: ");
    scanf("%lf",&u.phone_num);
    flush(stdin);


    printf("Enter initial balance: ");
    scanf("%lf",&u.balance);
    flush(stdin);

    
        // Check if username exists
        do {
         printf("Enter username: ");
         scanf("%49[^\n]",u.username);
         flush(stdin);
	 
	 err = checkUsername(a, u.username, index);
	         if(err == -1) {          // If err = -1, then username is found (already exists)
        printf("ERROR: User already exists. Pick a different username.\n");
        }
     } while(err == -1);
    printf("\nYou can use this username.\n");
    printf("Enter password: ");
    scanf("%d", &u.password);
    flush(stdin);

    u.account_num = u.phone_num;

    err = arrayPushBack(a,u);
    if(err == -1) {
        printf("Failed to create account.\n");
        return -1;
    } else {
        printf("Successfully created user (%s) with account number: %lf.\n", u.username, u.account_num);
	}
    return 0;
    }

/*  This function has to print all the information related to
    the user with index indexUser */
 int printUserInfo(array * a, size_t indexUser){

   printf("Your name is: %s\n",a->data[indexUser].name);
   printf("Your address is: %s\n",a->data[indexUser].address);
   printf("Your age is: %d \n",a->data[indexUser].age);
    printf("Your phone number is: %lf\n",a->data[indexUser].phone_num);
    printf("Your balance is: $%lf\n",a->data[indexUser].balance);
    printf("Your account number is: %lf\n",a->data[indexUser].account_num);
    return 0;
 }



/* This function has to set the value of * indexUser by the index of the user in the array whose information matches the given username and password. */
 int checkPasswordUsername(array *a, char * username, int password,
			  size_t * indexUser){
int i;
                      for( i=0; i <= a->inUse; i++){
			if(strcmp(username, a->data[i].username) == 0 && password == a->data[i].password){
			  printf("login successfully\n");
			  //  printf("i = %d\n", i); checked
			  *indexUser = i; // set indexUser to be equal to user i in the array
			  //  printf("index user = %d\n", *indexUser); checked
			  
			  return 0; // success
		      }
		      } // exit for loop user not found
		      return -1;
 }
			

/* This function has to set the value of * indexUser by the index of the user in the array whose information matches the given username. This function will be useful when you want to make a cash transfer. */
int checkUsername(array *a, char * username, size_t * indexUser){
int i;
                      for( i=0; i < a->inUse; i++){
			if(strcmp(username, a->data[i].username) == 0){
			  *indexUser = i;
			  return -1; // username exists
		      }
		      } // exit the for loop,username does not exist ,you can use this username
		      return 0; // success
 }

   


/* get the balance of the user with index indexUser and put it where balance is pointInputg to. */
userBalanceGet(array *a, size_t indexUser, size_t * balance){
  *balance = a->data[indexUser].balance;
  printf("Your balance is: $%d\n", *balance);
}
   


/*add to the balance of the user with index indexUser the amount. Note that amount can be positive or negative value. Hence, this function can be used to add or deposit money.*/
		      
int userBalancePut(array *a, size_t indexUser, int amount){
  int tmp = a->data[indexUser].balance;
  a->data[indexUser].balance =   a->data[indexUser].balance + amount;
  if(  a->data[indexUser].balance < 0){
    printf("Error, please check the entered amount\n");
      a->data[indexUser].balance = tmp;
      return -1;
  }
return 0;
  }


/* This function will ask the user with index indexUser in the array to re-input all the information */
 int editUser(array * a , size_t indexUser){
    user u;
    size_t index;
    int input;
    char Input[50];

    // Main Loop
    do{
    printf("changing data ..\n");
    printf("What do you want to change? (please enter a number)\n");
      printf("1- Name\n");
      printf("2- Address\n");
      printf("3- Age\n");
      printf("4- Phone number\n");
      printf("5- Exit\n");
      printf("> ");
      scanf("%d",&input);
          flush(stdin);
	  
      if(input == 1){
    printf("Enter your new name: ");
    scanf("%49[^\n]", Input);
    flush(stdin);
    strcpy(a->data[indexUser].name, Input);
        printf("\nName changed.\n");
      }
      else if(input == 2){
    printf("Enter your new address: ");
    scanf("%49[^\n]s", Input);
    flush(stdin);
        strcpy(a->data[indexUser].address, Input);
        printf("\nAddress changed.\n");
	}
      else if(input == 3){
	printf("Enter your new age: ");
    scanf("%d",&a->data[indexUser].age);
    flush(stdin);
        printf("\Age changed.\n");
      }
      else if(input == 4){
	printf("Enter new phone number: ");
    scanf("%lf",&a->data[indexUser].phone_num);
    flush(stdin);
        printf("\nPhone number changed.\n");
      }
     else {
       printf("error, Please enter a number\n");
    }
    }  while(input != 5);
    
    return 0;
 } //


/* This function has to reduce the balance of the user with index
indexUser1 by amount and add to the balance of the user with index
indexUser2 the amount */
int cashTransfer (array *a, size_t indexUser1, size_t indexUser2 , size_t amount){

  int err;
  int output;
  err = userBalancePut(a, indexUser1, (-1)*amount);
  if(err == -1){
    return -1;
  }
  userBalanceGet(a, indexUser1, &output);
   printf("Cash tranfered successfully!\n");
userBalancePut(a, indexUser2, amount);
    return 0;
}


/* This function has to delete the user with index
   indexIser from the array */
int userDelete(array *a, size_t indexUser){
  int i;
                    for( i= indexUser; i < a->inUse-1; i++){
			    a->data[i] = a->data[i+1];
		      }
	    		     free(&a->data[i]);
	     		    resizeArray( a, a->inUse -1);
		      return 0; // success
}


