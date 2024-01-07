#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Taxi {
   int id;
   char driver[20];
   char category[20];
   char plate[7];
   char color[20];
   float rate;
   float minCharge;
   char state;
   struct Taxi *next;
};

struct Taxi *list = NULL; /* Global pointer to a linked list of Taxi structures. */

//-----------------------------------
void addTripCar() {
   struct Taxi *head = NULL, *current;

   FILE* fp= fopen("Taxies.txt","r"); /* Open the file in read mode. */
   if (fp == NULL) {
      printf("Error opening file\n"); /* Display error if file can't be opened. */
      return;
   }

   char *firstLine;
   fgets(firstLine, 100, fp); /* Read and ignore the first line of the file. */

   int i;
   for (i=0; i<6; i++){
      struct Taxi *temp = (struct Taxi *) malloc(sizeof(struct Taxi)); /* Allocate memory for a new Taxi structure. */
      if (temp == NULL) {
          printf("Memory allocation failed\n");
          return;
      } /* Exit the function if memory allocation fails. */

     
      fscanf(fp, "%d %s %s %s %s %f %f ", &(temp->id), temp->driver, 
             temp->category, temp->plate, temp->color, &(temp->rate),
             &(temp->minCharge));
      temp->state = 'A'; /* Initialize state to 'A' (Available). */
      
      temp->next = NULL;
      if (head == NULL){
         head = temp;
         current = head;
      }
      else {
         current->next = temp;
         current = current->next;
      }
   } /* End of for loop. */

   list = head; /* Assign the head of the list to the global list pointer. */
   fclose(fp); /* Close the file. */
}

//-----------------------------------
void setTripCar(char* category, float* rate) {
   if (list == NULL) {
      printf("the list is empty \n"); /* Check if list is empty. */
      return;
   }

   struct Taxi *current = list;

   while (current != NULL) {
      if (strcmp(current->category, category) == 0 && current->rate == *rate) {
         current->state = 'R'; /* Set state to 'R' (Reserved) if category and rate match. */
         return;
      }
      current = current->next;
   }
}

//-----------------------------------
void writeCarsInRide(char* fileName) {
   if (list == NULL) {
      printf("the list is empty \n"); /* Check if list is empty. */
      return;
   }

   FILE *fop = fopen(fileName, "a"); /* Open the file in append mode. */
   if (fop == NULL) {
      printf("Error opening file\n");
      return;
   }

   struct Taxi* current = list;

   while (current != NULL) {
      if (current->state == 'R')
         fprintf(fop, "%-15d %-15s %-20s %-20s %-15.1f %c \n", current->id, current->driver, current->category, 
                 current->plate, current->rate, current->state); /* Write taxi details to the file if state is 'R'. */

      current = current->next;
   }
   fclose(fop); /* Close the file. */
}

//-----------------------------------
void printList() {
   if (list == NULL) {
      printf("there is no list\n"); /* Check if list is empty. */
      return;
   }

   struct Taxi* current = list;

   while (current != NULL) {
      printf("%-10d %-10s %-10s %-10s %-10.1f %-10.2f %c\n", current->id, current->driver, current->category,
             current->plate, current->rate, current->minCharge, current->state); /* Print details of each taxi. */

      current = current->next;
   }
}

//-----------------------------------
int main() {
   addTripCar(); /* Add taxis from file to the list. */

   printf("The Available Trip cars:\n");
   printList(); /* Print all taxis in the list. */

   char *s1 = "Business"; float f1 = 4.5;
   char *s2 = "Family";    float f2 = 5.0;
   char *s3 = "Family";    float f3 = 4.0;
   char *s4 = "standard";  float f4 = 3.4;
   char *s5 = "standard";  float f5 = 5.0;

   setTripCar(s1, &f1);
   setTripCar(s2, &f2);
   setTripCar(s3, &f3);
   setTripCar(s4, &f4);
   setTripCar(s5, &f5); /* Set specific taxis as reserved based on category and rate. */

   printf("\n--------------------------------------------------------------------\n");

   printf("The Cars in Ride:\n");
   printList(); /* Print updated list of taxis. */

   char *fileName = "Taxies.txt";
   writeCarsInRide(fileName); /* Write details of reserved taxis to a file. */

   return 0;
}
