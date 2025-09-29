#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "file.h"

// Saves all contacts from the address book to a CSV file
void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "w");  // Opens file in write mode
    if (fp == NULL) 
    {
        perror("Cannot save contacts");  // Prints error if file opening fails
        return;  // Exits function on failure
    }

    // Loops through all contacts in the address book
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fp, "%d,%s,%s,%s\n", i + 1,  // Writes contact data to file
                addressBook->contacts[i].name,   // Format: index,name,phone,email
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fp);  // Closes the file after writing
    //printf("Contacts saved successfully to contacts.csv\n");  // Commented confirmation message
}

// Loads contacts from a CSV file into the address book
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp = fopen("contacts.csv", "r");  // Opens file in read mode
    if (fp == NULL) 
    {
        // printf("Error: Could not open contacts.csv\n");  // Commented error message
        addressBook->contactCount = 0;  // Sets contact count to 0 if file not found
        return;  // Exits function on failure
    }

    addressBook->contactCount = 0;  // Resets contact count before loading
    char line[150];  // Buffer to store each line from the file

    // Reads lines from file until end or max contacts reached
    while (fgets(line, sizeof(line), fp) != NULL && addressBook->contactCount < MAX_CONTACTS) 
    {
        int index;  // Variables to store parsed data
        char name[50], phone[15], email[50];

        // Parses line into index, name, phone, and email
        int fields = sscanf(line, "%d,%49[^,],%14[^,],%49s", 
                            &index, name, phone, email);
        if (fields == 4)  // Checks if all 4 fields were successfully parsed
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);   // Copies name
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone); // Copies phone
            strcpy(addressBook->contacts[addressBook->contactCount].email, email); // Copies email
            addressBook->contactCount++;  // Increments contact count
        }
    }

    fclose(fp);  // Closes the file after reading
    // printf("Total contacts loaded: %d\n", addressBook->contactCount);  // Commented confirmation message
}