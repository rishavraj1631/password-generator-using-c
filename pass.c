/*
Write a program that generates or verifies passwords
Rules for passwords:
at least 9 characters long and less then 15 characters
at least 2 numbers
at least 2 uppercase and 2 lowercase letters
at least 1 symbol
no common words (3,4 letter words) (Use a dictionary(text file))	[have 10 to 50 words]
old passwords not to be used again (write to text file, same as above)
Create a menu
-Generate a password (from the rules above)
-must be able to enter a password
-
Check these programs:
moreStrings (isAlpha : character)	C04RedDuck
convertor (ASCII)
*/

// includes
#include <stdio.h>	// printf, scanf, puts, NULL
#include <string.h>	// strstr
#include <stdlib.h> // srand, rand
#include <math.h>
#include <ctype.h>	// for isdigit
#include <time.h>	// for time

// function declarations
void menu();
void genPass();
void checkPass();
void oldPass();
void comWords();
int randomiser(int);

// definitions
#define PASS_LEN 15+1	// change to 30 if error

void main()
{
	// header
	printf("Rondon Password Generator & Verifier\n");
	printf("====================================");

	// menu
	menu();

	// end of program
	printf("\n\n");
	system("pause");
}	// end main

void menu()
{
	int myChoice;

	do
	{
		printf("\n1) Generate Password\n2) Check Password\n3) List Old Passwords\n4) List Common Words\n5) Exit\n\nChoice: ");
		scanf("%d", &myChoice);
		fflush(stdin);

		switch(myChoice)
		{
		case 1:	// Generate Password
			genPass();
			break;

		case 2:	// Checking Password
			checkPass();
			break;

		case 3: // List Old Passwords
			oldPass();
			break;

		case 4:
			comWords();
			break;

		case 5:	// Exit menu
			printf("\nThanks for using Roncon Password Generator\n\nGoodbye :)");
			break;

		default:
			break;
		}	// end switch
	}while(myChoice != 5);	// end doWhile
}	// end menu

void genPass()
{
	// constants
	const int MIN_LEN = 9;
	const int MAX_LEN = 15;
	const int MIN_NUM = 2;
	const int MIN_UPPER = 2;
	const int MIN_LOWER = 2;
	const int MIN_SPECIAL = 1;
	
	// arrays
	const char upperCase[26+1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char lowerCase[26+1] = "abcdefghijklmnopqrstuvwxyz";
	const char numbers[10+1] = "0123456789";
	const char specialChar[8+1] = "!$%^*?()";

	// variables
	int randVar;
	int counter;
	int tempInt;
	char tempChar;

	// password attributes
	char password[PASS_LEN];
	int passLen;

	// other
	int passOkay = 1;
	char oldPass[PASS_LEN];

	// shuffle
	int temp, lastNum;

	// strstr check
	char tempCom[5+1];
	char tempPass[PASS_LEN];

	// pointer
	FILE *fp;
	FILE *fpCom;

	// randomize seed
	srand(time(NULL));

	// length
	passLen = randomiser(7)+MIN_LEN;

	// loops
		for(counter = 0; counter < 2; counter++) // 2 Uppercase
		{
			randVar = randomiser(26);
			password[counter] = upperCase[randVar];
		}

		for(counter = 2; counter < 4; counter++) // 2 Lowercase
		{
			randVar = randomiser(26);
			password[counter] = lowerCase[randVar];
		}

		for(counter = 4; counter < 6; counter++) // 2 Numbers
		{
			randVar = randomiser(10);
			password[counter] = numbers[randVar];
		}

		for(counter = 6; counter < 7; counter++) // 1 Symbol
		{
			randVar = randomiser(8);
			password[counter] = specialChar[randVar];
		}

		for(counter = 7; counter < passLen; counter++) // Random Mix for remainder
		{
			randVar = randomiser(4);

			switch(randVar)
			{
				case 0:
					randVar = randomiser(26);
					password[counter] = upperCase[randVar];
					break;

				case 1:
					randVar = randomiser(26);
					password[counter] = lowerCase[randVar];
					break;

				case 2:
					randVar = randomiser(10);
					password[counter] = numbers[randVar];
					break;

				case 3:
					randVar = randomiser(8);
					password[counter] = specialChar[randVar];
					break;
			}
		}

	password[passLen] = '\0';

	// shuffle
	for(lastNum = passLen; lastNum > 1; lastNum--)
	{
		randVar = randomiser(lastNum);
		temp = password[randVar];
		password[randVar] = password[lastNum - 1];
		password[lastNum - 1] = temp;
	}

	// display new random password
	printf("Password: %s\n", password);

	// File Read/Append
	fp = fopen("oldPass.txt", "a+");
	fpCom = fopen("comWords.txt", "r");

    if (fp == NULL)
    {
        printf("\n\nFile does not exist\n");
    }
	else
	{
		printf("\n");
		while (fscanf(fp, "%s", oldPass) == 1)
		{
			if(strcmp(password,oldPass) == 0)
			{
				passOkay = 0;
				printf("Password already used, try again.\n");
			}
		}

		// to lower

		tempPass[passLen] = '\0';

		for(counter = 0; counter < passLen; counter++)
		{
			if(isalpha(password[counter]) != 0)
			{
				tempPass[counter] = tolower(password[counter]);
			}
			else
			{
				tempPass[counter] = password[counter];
			}
		}

		while (fscanf(fpCom, "%s", tempCom) == 1)
		{
			if(strstr(tempPass, tempCom))
			{
				passOkay = 0;
				printf("Password contains the common word \"%s\", which is dissallowed\n",tempCom);
			}
		}

		if(passOkay == 1)
		{
			printf("Password is okay :)\n");
			fprintf(fp, "%s\n", password);
		}
		else
		{
			printf("try again\n");
		}
		fclose(fp);
		fclose(fpCom);
	}
}	// genPass

void checkPass()
{
	// constants
	const int MIN_LEN = 9;
	const int MAX_LEN = 15;
	const int MIN_UPPER = 2;
	const int MIN_LOWER = 2;
	const int MIN_NUM = 2;
	const int MIN_SPECIAL = 1;
	
	// arrays
	const char upperCase[26+1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const char lowerCase[26+1] = "abcdefghijklmnopqrstuvwxyz";
	const char numbers[10+1] = "0123456789";
	const char specialChar[8+1] = "!$%^*?()";

	// variables
	char tempPass [PASS_LEN * 2];
	int iPos, jPos;

	// counters
	int upperCount = 0;
	int lowerCount = 0;
	int numCount = 0;
	int symCount = 0;
	int invalidCount = 0;

	// file handling
	FILE *fp;
	FILE *fpCom;
	int passOkay = 1;
	char tempCom[5+1];
	char oldPass[PASS_LEN];
	char lowerPass[PASS_LEN];
	int counter;
	//int passLen;

	// header
	printf("\nCheck Password\n");
	printf("==============\n");
	
	printf("\nRequirements:\n-------------\nMinimum Length: %d\nMaximum Length: %d\nUpper Case: %d\nLower Case: %d\nDigits: %d\nSymbols: %d\nCommon Invalid Symbols: \", $, &, British Pound & Percentage Signs\n", MIN_LEN, MAX_LEN, MIN_UPPER, MIN_LOWER, MIN_NUM, MIN_SPECIAL);
	
	printf("\nEnter a password: ");
	scanf("%s", tempPass);
	//printf("%s", tempPass);	// error when using british pound sign

	if(strlen(tempPass) >= MIN_LEN && strlen(tempPass) <= MAX_LEN)	// checks for min/max length
	{
		for (iPos = 0; iPos < strlen(tempPass); iPos++)	// checks each character
		{
			if(isalpha(tempPass[iPos]))
			{
				if(isupper(tempPass[iPos]))
				{
					upperCount++;
				}

				if(islower(tempPass[iPos]))
				{
					lowerCount++;
				}
			}
			else if(isdigit(tempPass[iPos])) // == 0;
			{
				numCount++;
			}
			else
			{
				for(jPos = 0; jPos < strlen(specialChar); jPos++)
				{
					if(tempPass[iPos] == specialChar[jPos])
					{
						symCount++;
					}
				}
			} // end of if
		} // end of for

		invalidCount = strlen(tempPass) - (upperCount + lowerCount + numCount + symCount);
		printf("\nUpper Case: %d\nLower Case: %d\nDigits: %d\nSymbols: %d\nInvalid Characters: %d", upperCount, lowerCount, numCount, symCount, invalidCount);
	
		if(upperCount >= MIN_UPPER && lowerCount >= MIN_LOWER && numCount >= MIN_NUM && symCount >= MIN_SPECIAL && invalidCount == 0)
		{
			// File Read/Append
			fp = fopen("oldPass.txt", "a+");
			fpCom = fopen("comWords.txt", "r");

			if (fp == NULL)
			{
				printf("\n\nFile does not exist\n");
			}
			else
			{
				printf("\n");
				while (fscanf(fp, "%s", oldPass) == 1)
				{
					if(strcmp(tempPass,oldPass) == 0)
					{
						passOkay = 0;
						printf("\nPassword already used, try again.\n");
					}
				}

				// to lower
				//tempPass[passLen] = '\0';

				for(counter = 0; counter < strlen(tempPass); counter++)
				{
					if(isalpha(tempPass[counter]) != 0)
					{
						lowerPass[counter] = tolower(tempPass[counter]);
					}
					else
					{
						lowerPass[counter] = tempPass[counter];
					}
				}

				while (fscanf(fpCom, "%s", tempCom) == 1)
				{
					if(strstr(tempPass, tempCom))
					{
						passOkay = 0;
						printf("\nPassword contains the common word \"%s\", which is dissallowed\n",tempCom);
					}
				}

				if(passOkay == 1)
				{
					printf("\nPassword is okay :)\n");
					fprintf(fp, "%s\n", tempPass);
				}
				else
				{
					printf("try again\n");
				}

				fclose(fp);
				fclose(fpCom);
			}
		}
		else
		{
			printf("\n\nYour password does not meet the requirement criteria\nTry Again.\n");
		}
	}
	else
	{
		printf("Invalid Password (Min Length: 9, Max Length: 15)\n");
	}
}	// checkPass

int randomiser(int num)
{
	// random number generation
	int randVar2;

	randVar2 = rand() % num; //  + 0
	return randVar2;
}

void oldPass()
{
	// other
	char oldPass[PASS_LEN];

	// pointer
	FILE *fp;

	// File Read
	fp = fopen("oldPass.txt", "r");

	// header
	printf("\nList of old Passwords\n");
	printf("=====================\n");

    if (fp == NULL)
    {
        printf("\nFile does not exist\n");
    }
	else
	{
		while (fscanf(fp, "%s", oldPass) == 1)
		{
			printf("%s\n", oldPass);
		}
		fclose(fp);
	}
}

void comWords()
{
	// other
	char comWords[5+1];

	// pointer
	FILE *fpCom;

	// File Read
	fpCom = fopen("comWords.txt", "r");

	// header
	printf("\nList of Common Words\n");
	printf("=====================\n");

    if (fpCom == NULL)
    {
        printf("\nFile does not exist\n");
    }
	else
	{
		while (fscanf(fpCom, "%s", comWords) == 1)
		{
			printf("%s\n", comWords);
		}
		fclose(fpCom);
	}
}

/* ENHANCEMENTS:
Could use ASCII table to check characters, using ranges.
Arrays seem simpler to use.
Could have added error handling is a comWords.txt file did not exist.
Didn't do this as the program will come bundled with this file.
As opposed to the oldPass.txt which will come empty.
 */