/*
Name : Ashwajeet Kshirsagar
*/

#include "contact.h"
#include "file.h"
#include <stdio.h>

int main() 
{
    AddressBook addressBook;
    initialize(&addressBook);
    loadContactsFromFile(&addressBook);

    // Load existing contacts at startup
    loadContactsFromFile(&addressBook);

    int choice;
    while (1)  // running loop
    {
        printf("\n");
        printf("\t\t\t\tWELCOME TO ASHWAJEET'S ADDRESSBOOK         \n");
        // Print table header
        printf("\n");
        printf("\t\t+-------+--------------------------+\n");
        printf("\t\t| Option| Address Book Menu        |\n");
        printf("\t\t+-------+--------------------------+\n");

        // Print menu options in table rows
        printf("\t\t| 1     | Create Contact           |\n");
        printf("\t\t| 2     | Search Contact           |\n");
        printf("\t\t| 3     | Edit Contact             |\n");
        printf("\t\t| 4     | Delete Contact           |\n");
        printf("\t\t| 5     | List Contacts            |\n");
        printf("\t\t| 6     | Save Contacts to File    |\n");
        printf("\t\t| 7     | Exit                     |\n");

        // Print table footer and prompt
        printf("\t\t+-------+--------------------------+\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);
        // using switch case for choice
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook); // Assuming you have this function
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Exiting program.\n");
                saveContactsToFile(&addressBook); // Save before exiting
                return 0;
            default:
                printf("Invalid choice! Please enter a number between 1 and 7.\n");
        }
    }
    return 0;
}