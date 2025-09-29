#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define RED     "\033[31m"  // Red color for invalid messages
#define RESET   "\033[0m"   // Reset color

// Initializes the address book by setting contact count to 0
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
}

// Validates if name contains only letters and spaces
int isValidName(char *name) 
{
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!isalpha(name[i]) && !isspace(name[i])) 
            return 0;  // Returns 0 if any character is not a letter or space
    }
    return strlen(name) > 0;  // Returns 1 if name is not empty, 0 otherwise
}

// Validates if phone number is exactly 10 digits
int isValidPhone(char *phone) 
{
    if (strlen(phone) != 10) return 0;  // Checks length
    for (int i = 0; i < 10; i++) 
    {
        if (!isdigit(phone[i])) return 0;  // Checks each character is a digit
    }
    return 1;  // Returns 1 if valid
}

// Validates email format: must start with letter, contain one '@', end with '.com'
int isValidEmail(char *email) 
{
    if (email == NULL || email[0] == '\0' || !isalpha(email[0])) 
        return 0;  // Checks if email is null, empty, or doesn't start with letter

    char *atPos = strstr(email, "@");  // Finds '@' position
    if (atPos == NULL || atPos == email) 
        return 0;  // Checks if '@' exists and isn't first character

    int atCount = 0;
    for (int i = 0; email[i] != '\0'; i++) 
    {
        if (email[i] == '@') 
            atCount++;  // Counts '@' occurrences
    }
    if (atCount != 1) 
        return 0;  // Ensures exactly one '@'

    char *dotComPos = strstr(email, ".com");  // Finds '.com' position
    if (dotComPos == NULL) 
        return 0;  // Checks if '.com' exists

    if (dotComPos[4] != '\0') 
        return 0;  // Ensures nothing follows '.com'

    if (dotComPos - atPos <= 1) 
        return 0;  // Ensures at least one character between '@' and '.com'

    for (char *p = atPos; p < dotComPos; p++) 
    {
        if (*p == '.' && *(p + 1) == '.') 
            return 0;  // Checks for consecutive dots
    }

    return 1;  // Returns 1 if all conditions are met
}

// Creates a new contact with validated and unique entries
void createContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf(RED "Address book is full! Cannot add more contacts.\n" RESET);
        return;  // Exits if address book is full
    }

    int index = addressBook->contactCount;

    printf("Enter name: ");
    scanf(" %[^\n]s", addressBook->contacts[index].name);

    while (!isValidName(addressBook->contacts[index].name)) 
    {
        printf(RED "Invalid name. Enter again: " RESET);
        scanf(" %[^\n]s", addressBook->contacts[index].name);  // Re-prompts until valid
    }

    int isUniquePhone;
    do 
    {
        printf("Enter phone number (10 digits): ");
        scanf(" %s", addressBook->contacts[index].phone);
        while (!isValidPhone(addressBook->contacts[index].phone)) 
        {
            printf(RED "\nInvalid phone number (must be 10 digits):" RESET); 
            printf("\nEnter again: ");
            scanf(" %s", addressBook->contacts[index].phone);  // Re-prompts until valid
        }

        isUniquePhone = 1;
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[index].phone) == 0) 
            {
                isUniquePhone = 0;  // Checks for duplicate phone
                printf("\nEnter a unique phone number: ");
                break;
            }
        }
    } 
    while (!isUniquePhone);  // Loops until unique phone is entered

    int isUniqueEmail;
    do 
    {
        printf("Enter email (must contain atleast one '@' and '.com'): ");
        scanf(" %s", addressBook->contacts[index].email);
        while (!isValidEmail(addressBook->contacts[index].email)) 
        {
            printf(RED "Invalid email.  " RESET);
            printf("\nEnter again:");
            scanf(" %s", addressBook->contacts[index].email);  // Re-prompts until valid
        }

        isUniqueEmail = 1;
        for (int i = 0; i < addressBook->contactCount; i++) 
        {
            if (strcmp(addressBook->contacts[i].email, addressBook->contacts[index].email) == 0) 
            {
                isUniqueEmail = 0;  // Checks for duplicate email
                printf(RED "This email is already assigned to another contact:" RESET); 
                printf("\nEnter a unique email: ");
                break;
            }
        }
    } 
    while (!isUniqueEmail);  // Loops until unique email is entered

    addressBook->contactCount++;
    printf("Contact added successfully: %d. Name: %s, Phone: %s, Email: %s\n", 
           index + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, 
           addressBook->contacts[index].email);  // Confirms addition
}

// Searches for contacts based on name, phone, or email
void searchContact(AddressBook *addressBook) 
{
    int choice;
    char term[50];
    int match[100];
    int matchCount = 0;

    while (1) 
    {
        printf("Search by:\n");
        printf("1. Name\n2. Phone Number\n3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 3) 
            break;  // Ensures valid search option
        printf(RED "Invalid choice! Please try again.\n" RESET);
    }

    do 
    {
        switch (choice) 
        {
            case 1: printf("Enter name to search: "); break;
            case 2: printf("Enter phone number to search: "); break;
            case 3: printf("Enter email to search: "); break;
        }
        scanf(" %[^\n]s", term);

        if (choice == 1) 
        {
            if (!isValidName(term)) 
            {
                printf(RED "Invalid name\n" RESET);
                continue;  // Validates search term for name
            }
        } 
        else if (choice == 2) 
        {
            if (!isValidPhone(term)) 
            {
                printf(RED "Invalid phone number\n" RESET);
                continue;  // Validates search term for phone
            }
        } 
        else if (choice == 3) 
        {
            if (!isValidEmail(term)) 
            {
                printf(RED "Invalid email\n" RESET);
                continue;  // Validates search term for email
            }
        }
        break;
    } while (1);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        char *search;
        switch (choice) 
        {
            case 1: search = addressBook->contacts[i].name; 
            break;
            case 2: search = addressBook->contacts[i].phone; 
            break;
            case 3: search = addressBook->contacts[i].email; 
            break;
        }
        if (strstr(search, term) != NULL) 
            match[matchCount++] = i;  // Stores indices of matching contacts
    }

    if (matchCount == 0) 
    {
        printf(RED "No contacts found matching that criterion.\n" RESET);
        return;  // Exits if no matches
    } 
    else if (matchCount == 1 || choice != 1) 
    {
        int i = match[0];
        printf("Found: %d. Name: %s, Phone: %s, Email: %s\n", 
               i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);  // Displays single match
    } 
    else if (matchCount > 1 && choice == 1) 
    {
        printf("%d people found with matching name:\n", matchCount);
        for (int j = 0; j < matchCount; j++) 
        {
            int i = match[j];
            printf("%d. Name: %s, Phone: %s, Email: %s\n", 
                   i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);  // Lists multiple name matches
        }

        while (1) 
        {
            printf("What would you like to do?\n");
            printf("1. Refine by Phone Number\n2. Refine by Email\n3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice >= 1 && choice <= 3) 
                break;  // Ensures valid refinement choice
            printf(RED "Invalid choice! Please try again.\n\n" RESET);
        }

        if (choice == 3) 
        {
            printf("Exiting search.\n");
            return;  // Exits if user chooses to
        }

        char term2[50];
        do {
            if (choice == 1) 
                printf("Enter phone number");
            else 
                printf("Enter email ");
            scanf(" %[^\n]s", term2);

            if (choice == 1 && !isValidPhone(term2)) 
                printf(RED "Invalid phone number.\n" RESET);
            else if (choice == 2 && !isValidEmail(term2)) 
                printf(RED "Invalid email!\n" RESET);
            else 
                break;  // Validates refinement term
        } 
        while (1);

        int found = 0;
        for (int j = 0; j < matchCount; j++) 
        {
            int i = match[j];
            char *search = (choice == 1) ? addressBook->contacts[i].phone : addressBook->contacts[i].email;
            if (strstr(search, term2) != NULL) 
            {
                printf("Found: %d. Name: %s, Phone: %s, Email: %s\n", 
                       i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, 
                       addressBook->contacts[i].email);  // Displays refined match
                found++;
            }
        }
        if (found == 0) 
        {
            printf(RED "No contacts found with that %s.\n" RESET, (choice == 1) ? "phone number" : "email");
        }
    }
}

// Deletes a contact after searching and confirming
void deleteContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf(RED "No contacts available to delete.\n" RESET);
        return;  // Exits if address book is empty
    }

    int choice;
    char term[50];
    int match[100];
    int matchCount = 0;

    while (1) 
    {
        printf("Search by:\n");
        printf("1. Name\n2. Phone Number\n3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 3)
            break;  // Ensures valid search option
        printf(RED "Invalid choice! Please try again.\n\n" RESET);
    }

    switch (choice) 
    {
        case 1: printf("Enter name to search: "); 
        break;
        case 2: printf("Enter phone number to search: "); 
        break;
        case 3: printf("Enter email to search: "); 
        break;
    }
    scanf(" %[^\n]s", term);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        char *search;
        switch (choice) 
        {
            case 1: search = addressBook->contacts[i].name; 
            break;
            case 2: search = addressBook->contacts[i].phone; 
            break;
            case 3: search = addressBook->contacts[i].email; 
            break;
        }
        if (strstr(search, term) != NULL) 
            match[matchCount++] = i;  // Stores matching indices
    }

    if (matchCount == 0) 
    {
        printf(RED "No contacts found matching that criterion.\n" RESET);
        return;  // Exits if no matches
    }
    else if (matchCount == 1 || choice != 1) 
    {
        int index = match[0];
        printf("Found: %d. Name: %s, Phone: %s, Email: %s\n", 
               index + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, 
               addressBook->contacts[index].email);
        
        printf("Are you sure you want to delete contact %d?\n", index + 1);
        printf("1. Yes\n2. No\nEnter your choice: ");
        scanf("%d", &choice);
        
        if (choice != 1) 
        {
            printf("Deletion cancelled.\n");
            return;  // Cancels if user chooses no
        }

        for (int i = index; i < addressBook->contactCount - 1; i++) 
        {
            strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
            strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
            strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);  // Shifts contacts left
        }
        addressBook->contactCount--;
        printf("Contact %d deleted successfully.\n", index + 1);  // Confirms deletion
    } 
    else if (matchCount > 1 && choice == 1) 
    {
        printf("%d people found with matching name.\n", matchCount);
        while (1) 
        {
            printf("What would you like to do?\n");
            printf("1. Refine by Phone Number\n2. Refine by Email\n3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice >= 1 && choice <= 3) 
                break;  // Ensures valid refinement choice
            
            printf(RED "Invalid choice! Please try again.\n\n" RESET);
        }

        if (choice == 3) 
        {
            printf("Exiting delete.\n");
            return;  // Exits if user chooses to
        }

        char term2[50];
        if (choice == 1) 
        printf("Enter phone number: ");
        else printf("Enter email: ");
        scanf(" %[^\n]s", term2);

        int found = 0;
        int selectedIndex = -1;
        for (int j = 0; j < matchCount; j++) 
        {
            int i = match[j];
            char *search = (choice == 1) ? addressBook->contacts[i].phone : addressBook->contacts[i].email;
            if (strstr(search, term2) != NULL) 
            {
                found++;
                selectedIndex = i;  // Finds unique match
            }
        }

        if (found == 0) 
        {
            printf(RED "No contacts found with that %s.\n" RESET, (choice == 1) ? "phone number" : "email");
            return;
        }
        else if (found == 1) 
        {
            int index = selectedIndex;
            printf("Found: %d. Name: %s, Phone: %s, Email: %s\n", 
                   index + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, 
                   addressBook->contacts[index].email);
            
            printf("Are you sure you want to delete contact %d?\n", index + 1);
            printf("1. Yes\n2. No\nEnter your choice (1-2): ");
            scanf("%d", &choice);
            
            if (choice != 1) 
            {
                printf("Deletion cancelled.\n");
                return;  // Cancels if user chooses no
            }
            for (int i = index; i < addressBook->contactCount - 1; i++) 
            {
                strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);  // Shifts contacts left
            }
            addressBook->contactCount--;
            printf("Contact %d deleted successfully.\n", index + 1);  // Confirms deletion
        } 
        else 
        {
            printf(RED "Multiple contacts still match. Please refine further or use a unique identifier.\n" RESET);
            return;  // Prompts for more specific input
        }
    }
}

// Edits an existing contact after searching
void editContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf(RED "No contacts available to edit.\n" RESET);
        return;  // Exits if address book is empty
    }

    int searchChoice;
    char term[50];
    int match[100];
    int matchCount = 0;

    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &searchChoice);

    if (searchChoice < 1 || searchChoice > 3) 
    {
        printf(RED "Invalid choice! Please select 1, 2, or 3.\n" RESET);
        return;  // Validates search option
    }

    if (searchChoice == 1) 
        printf("Enter name to search: ");
    else if (searchChoice == 2) 
        printf("Enter phone number to search: ");
    else if (searchChoice == 3) 
        printf("Enter email to search: ");
    scanf(" %[^\n]s", term);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        char *field;
        if (searchChoice == 1) 
            field = addressBook->contacts[i].name;
        else if (searchChoice == 2) 
            field = addressBook->contacts[i].phone;
        else if (searchChoice == 3) 
            field = addressBook->contacts[i].email;
        if (strstr(field, term) != NULL) 
        {
            match[matchCount] = i;
            matchCount++;  // Stores matching indices
        }
    }

    if (matchCount == 0) 
    {
        if (searchChoice == 1) 
            printf(RED "No contacts found with that name.\n" RESET);
        else if (searchChoice == 2) 
            printf(RED "No contacts found with that phone number.\n" RESET);
        else if (searchChoice == 3) 
            printf(RED "No contacts found with that email.\n" RESET);
        return;  // Exits if no matches
    } 
    else if (matchCount == 1) 
    {
        int index = match[0];
        proceedToEdit(addressBook, index);  // Proceeds to edit single match
    } 
    else if (matchCount > 1) 
    {
        if (searchChoice == 1) 
        {
            printf("%d contacts found with matching name.\n", matchCount);

            int choice;
            while (1) 
            {
                printf("What would you like to do?\n");
                printf("1. Refine by Phone Number\n");
                printf("2. Refine by Email\n");
                printf("3. Exit\n");
                printf("Enter your choice (1-3): ");
                scanf("%d", &choice);

                if (choice >= 1 && choice <= 3) 
                break;  // Ensures valid refinement choice
                printf(RED "Invalid choice! Please try again.\n\n" RESET);
            }

            if (choice == 3) 
            {
                printf("Exiting edit.\n");
                return;  // Exits if user chooses to
            }

            char term2[50];
            int refineField;
            if (choice == 1) 
            {
                refineField = 2;
                printf("Enter phone number: ");
            }
            else if (choice == 2) 
            {
                refineField = 3;
                printf("Enter email: ");
            }
            scanf(" %[^\n]s", term2);

            int found = 0;
            int selectedIndex = -1;
            for (int j = 0; j < matchCount; j++) 
            {
                int i = match[j];
                char *search;
                if (refineField == 2) 
                    search = addressBook->contacts[i].phone;
                else if (refineField == 3) 
                    search = addressBook->contacts[i].email;
                if (strstr(search, term2) != NULL) 
                {
                    found++;
                    selectedIndex = i;  // Finds unique match
                }
            }

            if (found == 0) 
            {
                if (refineField == 2) 
                    printf(RED "No contacts found with that phone number.\n" RESET);
                else if (refineField == 3) 
                    printf(RED "No contacts found with that email.\n" RESET);
                return;
            }
            else if (found == 1) 
            {
                proceedToEdit(addressBook, selectedIndex);  // Proceeds to edit single match
            }
            else 
            {
                printf(RED "Multiple contacts still match.\n" RESET);
                return;  // Prompts for more specific input
            }
        }
    }
}

// Helper function to handle the actual editing of a contact
void proceedToEdit(AddressBook *addressBook, int index) 
{
    int option;
    while (1) 
    {
        printf("Select what you want to edit for contact %d:\n", index + 1);
        printf("1. Name\n2. Phone\n3. Email\n4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &option);
        
        if (option >= 1 && option <= 4) break;  // Ensures valid edit option
        
        printf(RED "Invalid option! Please try again.\n\n" RESET);
    }

    switch (option) 
    {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]s", addressBook->contacts[index].name);
            while (!isValidName(addressBook->contacts[index].name)) 
            {
                printf(RED "Invalid name. Enter again: " RESET);
                scanf(" %[^\n]s", addressBook->contacts[index].name);  // Updates name
            }
            printf("Name updated.\n");
            break;
        case 2: 
        {
            int isUniquePhone;
            char originalPhone[15];
            strcpy(originalPhone, addressBook->contacts[index].phone);
            do 
            {
                printf("Enter new phone (10 digits): ");
                scanf(" %s", addressBook->contacts[index].phone);
                while (!isValidPhone(addressBook->contacts[index].phone)) 
                {
                    printf(RED "Invalid phone. Enter again: " RESET);
                    scanf(" %s", addressBook->contacts[index].phone);  // Updates phone
                }

                isUniquePhone = 1;
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (i != index && strcmp(addressBook->contacts[i].phone, addressBook->contacts[index].phone) == 0) 
                    {
                        isUniquePhone = 0;  // Checks for uniqueness
                        printf(RED "This phone number is already assigned to another contact " RESET);
                        printf("\nEnter a unique number: ");
                        break;
                    }
                }
            } 
            while (!isUniquePhone);
            printf("Phone updated.\n");
            break;
        }
        case 3: 
        {
            int isUniqueEmail;
            char originalEmail[50];
            strcpy(originalEmail, addressBook->contacts[index].email);
            do 
            {
                printf("Enter new email: ");
                scanf(" %s", addressBook->contacts[index].email);
                while (!isValidEmail(addressBook->contacts[index].email)) 
                {
                    printf(RED "Invalid email. Enter again: " RESET);
                    scanf(" %s", addressBook->contacts[index].email);  // Updates email
                }

                isUniqueEmail = 1;
                for (int i = 0; i < addressBook->contactCount; i++) 
                {
                    if (i != index && strcmp(addressBook->contacts[i].email, addressBook->contacts[index].email) == 0) 
                    {
                        isUniqueEmail = 0;  // Checks for uniqueness
                        printf(RED "This email is already Present. Enter a unique email: " RESET);
                        break;
                    }
                }
            } 
            while (!isUniqueEmail);
            printf("Email updated.\n");
            break;
        }
        case 4:
            printf("No changes made.\n");
            break;  // Exits without changes
    }
}

// Lists all contacts in a formatted table
void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf(RED "No contacts available to list.\n" RESET);
        return;  // Exits if address book is empty
    }

    printf("\n--- Contact List ---\n");

    #define CYAN    "\033[36m"  // For "No" column
    #define GREEN   "\033[32m"  // For "Name" column
    #define YELLOW  "\033[33m"  // For "Phone" column
    #define MAGENTA "\033[35m"  // For "Email" column

    printf("+----+--------------------------------+--------------+---------------------------+\n");
    printf("| " RED "%-2s" RESET " | " RED "%-30s" RESET " | " RED "%-12s" RESET " | " RED "%-25s" RESET " |\n",
           "No", "Name", "Phone", "Email");  // Prints header
    printf("+----+--------------------------------+--------------+---------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("| " CYAN "%2d" RESET " | " GREEN "%-30s" RESET " | " YELLOW "%-12s" RESET " | " MAGENTA "%-25s" RESET " |\n",
               i + 1, 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);  // Prints each contact
        printf("+----+--------------------------------+--------------+---------------------------+\n");
    }

    printf("--- End of List ---\n");  // Marks end of list
}