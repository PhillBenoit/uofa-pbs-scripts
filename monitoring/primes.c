#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//define the structure for a linked list node
typedef struct node {
	long data;
	struct node* next;
}node;

//pointers for the head and tail of the list
static struct node *head = NULL, *tail = NULL;

//count starts at 2 (2 and 3 are considered to be part of the list)
long counter = 2;

//prime numbers to a billion
#define LAST_NUMBER 1000000000

//slices for progress
#define SLICE 100

//adds a link to the linked list
void addNode(long n) {
	
	//allocate space for the node
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	//if malloc fails to allocate, print a helpful message
	if (newNode == NULL) printf("Stopped at %d. size of node: %d\n", counter,
		sizeof(struct node));
		
	//set new prime
	newNode->data = n;
	
	//point to new prime
	tail->next = newNode;
	
	//set new prime as the tail of the list
	tail = newNode;
	
	//increment counter
	counter++;
}

//entry point
int main() {

	//reject bad math that prevents proper counting
	if (LAST_NUMBER % SLICE != 0) {
		printf("Slice did not evenly divide the max\n");
		return -1;
	}

	//define step for monitoring loop
	long step = LAST_NUMBER / SLICE;

	//add 3 as first node of the list
	head = (struct node*)malloc(sizeof(struct node));
	head->data = 3;
	tail = head;

	//number being tested for primeness
	//start counting from 5
	long x = 5;

	//outer loop counter for monitoring
	long y = step;

	//cursor for stepping through the linked list
	struct node* cursor;

	//Holds the square root of the number being tested for "primeness".
	//Only prime numbers less than or equal
	//to this value are possible factors.
	long squarert;

	//variables that hold time info for monitoring
	time_t rawtime;
	struct tm * timeinfo;

	//outer monitoring loop
	for (; y <= LAST_NUMBER; y += step) {
		
		//step through numbers to test for "primeness"
		for (; x <= y; x += 2) {
			
			//find largest possible factor
			squarert = (long)sqrtl(x);
			
			//start at the beginning of the primes linked list
			cursor = head;
			
			//step through the linked list while primes do not evenly divide
			//the number being tested
			while (x % cursor->data != 0) {
			
				//break loop if a prime number is found
				if (cursor->data > squarert) {
					addNode(x);
					break;
				}
				
				//steps through the list
				cursor = cursor->next;
			}
		}

		//get time info
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
		//display progress
		printf("%.1f%% %d primes found ", ((double)x / LAST_NUMBER) * 100, counter);
		printf(asctime(timeinfo));
	}

	//see if results are correct
	if (counter == 50847534) printf("Correct number of primes found.\n");
	else printf("Incorrect number of primes found.\n");

	return 0;
}
