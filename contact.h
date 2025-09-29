#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct 
{
    char name[50];
    char phone[15];
    char email[50];
} Contact;

typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook); // Added declaration
int isValidName(char *name);
int isValidPhone(char *phone);
int isValidEmail(char *email);
void proceedToEdit(AddressBook *addressBook, int index);
void saveContactsToFile(AddressBook *addressBook);
#endif