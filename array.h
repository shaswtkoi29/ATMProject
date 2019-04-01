#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct _array array;
typedef struct _user user;

/* Return a new array with no elements.
 * Return NULL if creation fails. */
array * newArray(void);
/* Free array a. */
void deleteArray(array* a);
/* Change the size of array a.
 * Return 0 if successful and -1 if resizing fails. */
int resizeArray(array* a, size_t newSize);
/* Write the size of array a to the location pointed by num.
 * Return 0 if succesful and -1 if a is an invalid pointer. */
int arrayNum(array const * a, size_t * num);
/* Write the i-th element of array a to the location
 * pointed by e.  Return 0 if successful and -1 otherwise. */
int arrayGet(array const * a, size_t i, user* e);
/* Add element e at the end of array a.  Return 0 if
 * successful and -1 otherwise. */
int arrayPushBack(array * a, user e);
/* Set the i-th element of array a to e.  Return 0 if
 * successful and -1 otherwise.  The i-th element of a
 * must already exist.  */
int arrayPut(user * a, size_t i, void * e);
/* Type of function to print the content of one array cell. */
typedef void (* printFn)(void const * e);
/* Print contents of array. */
int printArray(user const * a, printFn f);
/* Type of function to compare two array elements. */
typedef int (* compareFn)(void const * x, void const * y);
/* Sort array a using f for comparisons.  Return 0 if successful and
 * -1 otherwise.  */
int sortArray(user * a, compareFn f);


void flush(FILE * input);

/* This function has to ask the user to type all the
information and then call the function arrayPuchBack to add this information
in the array. */
int newUser(array *a);

/*  This function has to print all the information related to
    the user with index indexUser */
 int printUserInfo(array * a, size_t indexUser);

/* This function has to set the value of * indexUser by the index of the user in the array whose information matches the given username and password. */
 int checkPasswordUsername(array *a, char * username, int password,
			  size_t * indexUser);

/* This function has to set the value of * indexUser by the index of the user in the array whose information matches the given username. This function will be useful when you want to make a cash transfer. */
 int checkUsername(array *a, char * username, size_t * indexUser);


/* get the balance of the user with index indexUser and put it where balance is pointInputg to. */
 userBalanceGet(array *a, size_t indexUser, size_t * balance);


/*add to the balance of the user with index indexUser the amount. Note that amount can be positive or negative value. Hence, this function can be used to add or deposit money.*/
userBalancePut(array *a, size_t indexUser, int amount);

/* This function will ask the user with index indexUser in the array to re-input all the information */
 int editUser(array * a , size_t indexUser);

/* This function has to reduce the balance of the user with index
indexUser1 by amount and add to the balance of the user with index
indexUser2 the amount */
 int cashTransfer (array *a, size_t indexUser1, size_t indexUser2 , size_t amount);

/* This function has to delete the user with index
   indexIser from the array */
 int userDelete(array *a, size_t indexUser);


#endif
