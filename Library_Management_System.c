#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

#define SIZE 2

#pragma warning(disable:4996)

// --- USER-DEFINED FUNCTIONS --- //
void first_page(void);
void user_function(void);
void user_menu(char username[]);
void user_menu_display(void);
void add_profile_details(char username[], char file_name[]);
void view_profile_details(char username[], char filename[]);
void issue_book(char username[], char filename[]);
void view_issued_books(char username[]);
void membership_details(void);
void library_timings(void);

void show_rules(void);

void admin_menu(void);
void admin_menu_display(void);
void add_book(void);
void search_book(void);
void remove_book(void);
void add_categories(void); // to add categories of books
void show_categories(void); // to show the categories of the books along with their prices
void add_user(void);
void remove_user(void);

// *** Extra Functions *** //
int pass_validity(char pass[]);

// --- Structs --- //
struct book_details
{
	int id;
	char name[100];
	int price;
	int vol;
	int items;
	char category[31];
};
struct book_issue
{
	char name[31];
	int vol;
	int price;
	char date[25];
};

struct p
{
	char name[15];
	int e;
}price;

// *** Struct for User's login data *** //  -------------------------------------------------------------
struct user
{
	char name[31];
	char pass[31];
}user;

struct profile
{
	char name[31];
	char gender;
	char age[3];
	char ph[15];
	char* ptr;
	char email[30];
	char address[50];
	int books_issued;
};

// --- Global Variables --- //
int book_record = 0;

int main()
{
	// --- Temprary Default USER PASSWORDS --- //
	char password_admin[9] = "admin123";
	char password_user[5] = "user";

	int user = 1;
	first_page();

again:
	system("cls");
	do
	{
		printf("\n\n \4\4\4 Login Page \4\4\4\n\n");
		if (user < 1 || user>2)
		{
			printf("\n\t\t--- Invalid Option Selected ---");
		}
		printf("\n\t\t\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4");
		printf("\n\t\t\t Login As: ");
		printf("\n\t\t\t1. User\n\t\t\t2. Admin");
		printf("\n\t\t ---------------------------- ");
		printf("\n\t\t\tYour Choice: ");
		scanf(" %d", &user);
		printf("\n\t\t\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4\4");

	} while (user < 1 || user>2);

	// --- PASSWORD CHECKING FOR BOTH USERS --- //
	char password[10];
	do
	{
		switch (user)
		{
		case 1:
		{
			user_function();
			break;
		}
			
		// *** Case for Admin *** //  -------------------------------------------------------------
		case 2:
		{
			// --- PASSWORD CHECKING FOR ADMIN --- //
			int check;
			do
			{
				printf("\n\t\tEnter Admin Password: ");
				scanf(" %s", password);
				check = strcmp(password, password_admin);

				if (check != 0)
				{
					printf("\n\t\t ------ Wrong Password ------ ");
					int temp = 1;
					do
					{
						if (temp < 1 || temp>2) printf("\n\t --- Invalid Option Entered --- ");
						printf("\n\t\tSelect Option\n\t\t1. Retry\n\t\t2. Exit as Admin\n\t\tYour Option: ");
						scanf("%d", &temp);
					} while (temp < 1 || temp>2);

					switch (temp)
					{
					case 1:
						break;
					case 2:
					{
						goto again;
						break;
					}
					}
				}
			} while (check);

			printf("\n\t --- You have logged in as 'admin' successfully ---");
			printf("\n\nPress any key to continue .... ");
			_getwch();
			admin_menu();
			break;
		}
		}
	} while (0);
	
}

// ---------------------------- Definitions ---------------------------- //

void first_page(void)
{
	printf("\n\n\n\t\t\t\t\t\t\t\t\t--------------------------------------------------------------------------");
	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM \n");
	printf("\n\t\t\t\t\t\t\t\t\t--------------------------------------------------------------------------");


	printf("\n\n\n");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t");
	printf(" Project by TOHEED ASGHAR");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t");
	printf("\tBCSF21M039");

	_getwch();
}

void user_function(void)
{
	char again = 'Y';
	while (again == 'Y' || again == 'y')
	{
		system("cls");
		printf("\nEnter Your Username: ");
		char user_nm[31];
		scanf(" %s", user_nm);

		// *** checking this user name in our database *** //
		FILE* ptr = fopen("user.dat", "rb");
		if (ptr == NULL)
		{
			printf("\nSomething Went Wrong, Please Try Again Later ....");
			printf("\n\nPress any key to continue ...."); _getwch();
			exit(1);
		}

		struct user temp;
		fread(&temp, sizeof(struct user), 1, ptr);
		int check = 0;
		while (!feof(ptr))
		{
			if (!strcmp(temp.name, user_nm))
			{
				check = 1; break;
			}
			fread(&temp, sizeof(struct user), 1, ptr);
		}

		if (check == 0)
		{
			printf("\n\n ***\tNo Such User Name Exists in our Database\t*** ");
			
		}
		else
		{
			printf("\nEnter your password: "); char password[31]; scanf("%s", password);
			if (!strcmp(temp.pass, password))
			{
				// *** Calling User Function *** // ----------------------------------------------------
				user_menu(user_nm);
				again = 'n'; // To End Loop
			}
			else
			{
				printf("\n *--- Wrong Password ---*");
			}
		}

		do
		{
			if (again != 'N' && again != 'Y' && again != 'n' && again != 'Y')
			{
				printf("\n *** ---\t Sorry we didn't get your option \t --- ***");
			}
			printf("\n Want to Continue Login (Y/N): ");
			scanf(" %c", &again);
		} while (again != 'N' && again != 'y' && again != 'n' && again != 'Y');

	}
	
}
void user_menu(char username[])
{
	system("cls");

	char string[31];
	strcpy(string, "user_files/");
	strcat(string, username);
	strcat(string, ".dat");
	FILE* ptr = fopen(string, "rb");

	if (!ptr)
	{
		printf("\n --- \t *** \t Something Went Wrong, Please Try Again Later \t *** \t ---");
		printf("\n\nPress any key to continue ....");
		_getwch();
	}

	int option = 1;
	do {
		// --- Displaying User Menu --- //
		user_menu_display();
		if (option < 1 || option>11) { printf("\n --- Invalid Option Entered --- "); }
		printf("\n\nYour Option: ");
		scanf("%d", &option);

		switch (option)
		{
		case 1:
		{
			add_profile_details(username, string); break;
		}
		case 2:
		{
			view_profile_details(username, string); break;
		}
		case 3:
		{
			issue_book(username, string); break;
		}
		case 4:
		{
			view_issued_books(username); break;
		}
		case 5:
		{
			search_book(); break;
		}
		case 6:
		{
			show_categories(); break;
		}
		case 7:
		{
			show_rules(); break;
		}
		case 8:
		{
			membership_details(); break;
		}
		case 9:
		{
			library_timings(); break;
		}


		}

		system("cls");
	} while (option!=0);
	puts("");
}

void admin_menu(void)
{
	system("cls");
	
	int option = 1;
	do // Main do-while loop
	{
		// --- Displaying the Menu of Admin --- //
		admin_menu_display();

		do
		{
			if (option < 1 || option > 13)
			{
				printf("\n\n\t ------------------ Invalid Option ------------------ ");
			}
			printf("\n\nYour Option: "); scanf("%d", &option);
		} while (option < 1 || option > 13);


		switch (option)
		{
		case 1:
		{
			add_user();
			break;
		}
		case 2:
		{
			remove_user();
			break;
		}
		case 3:
		{
			add_book(); break;
		}
		case 4:
		{
			search_book(); break;
		}
		case 5:
		{
			remove_book();
			break;
		}
		case 7:
		{
			add_categories(); break;
		}
		case 8:
		{
			show_categories(); break;
		}
		}

		// Clearing the console
		system("cls");
	} while (option != 13);

}

void admin_menu_display(void)
{
	printf("\n\t ------------------ Select Option: ------------------ ");
	printf("\n 1. Add a New User");
	printf("\n 2. Remove a User");
	printf("\n 3. Add a Book");
	printf("\n 4. Search a Book");
	printf("\n 5. Remove a Book");
	printf("\n 6. Edit the prices of the books");
	printf("\n 7. Add Categories of Books");
	printf("\n 8. Show Categories of Books");
	printf("\n 9. Get Details of a User");
	printf("\n10. Edit timings of the Library");
	printf("\n11. Fee Management");
	printf("\n12. Error Reports by End Uses");
	printf("\n13. Exit");
}
void add_book(void)
{
	struct book_details book;
	
	system("cls");
	printf(" ----------------------------------- Add a Book Record -------------------------------------- ");

	printf("\nEnter the Book ID          : "); scanf("%d", &book.id);
	printf("\nEnter the Book Name        : "); scanf(" %[^\n]*%c", book.name);
	printf("\nEnter the price (Rs)       : "); scanf("%d", &book.price);
	printf("\nEnter the vol              : "); scanf("%d", &book.vol);
	printf("\nEnter total items of books : "); scanf("%d", &book.items);
	printf("\nEnter the Book category    : "); scanf(" %[^\n]*%c", book.category);

	printf("\n --------------------- The Book has been Added to Database Successfully ---------------------\n");

	// --- Writing in File --- //
	FILE* bookptr = NULL;
	bookptr = fopen("books.txt", "a");
	fseek(bookptr, 1, SEEK_CUR);
	fputs(book.name, bookptr);
	fprintf(bookptr, "\n%d %d %d %d %s\n", book.id, book.price, book.vol, book.items, book.category);
	fclose(bookptr);

	book_record++; // incrementing in the total # of books
	printf("\nPress any key to continue .... ");	_getwch();
}
void search_book(void)
{
	//searchbook: // at Line 390
	char more_search = 'y';
	while (more_search == 'y' || more_search == 'Y')
	{
		system("cls");
		printf("\n ----------------------------------- Search a Book -------------------------------------- ");

		char temp_name[50];
		printf("\n\n Enter the book name to Search: ");
		int ch; while ((ch = getchar()) != '\n' && ch != EOF); // buffer error eradication
		fgets(temp_name, sizeof(temp_name), stdin);

		FILE* bookptr = NULL;
		bookptr = fopen("books.txt", "r");
		if (!bookptr)
		{
			puts(" Error ... Please Try Again Later ...."); exit(1);
		}

		char string[50];
		int check = 0;

		fgets(string, sizeof(string), bookptr);

		// Checking the temp_name in our Database
		while (!feof(bookptr))
		{
			if (!strcmp(string, temp_name))
			{
				check = 1; break;
			}

			fgets(string, sizeof(string), bookptr);
		}

		if (check == 0) // Means no such book
		{
			printf("\n\n -------- No such book exists in Database --------\n");
		}
		else
		{
			int id, price, vol, items;
			char cat[50];

			fseek(bookptr, 1, SEEK_CUR);
			fscanf(bookptr, "%d %d %d %d", &id, &price, &vol, &items);
			fgets(cat, sizeof(cat), bookptr);

			printf("\n --------------------------------------------------------------------------------------------------");
			printf("\n\t\t\t\t     Book Details: ");
			printf("\n --------------------------------------------------------------------------------------------------\n");

			printf("\n Name of the book : %s", temp_name);
			printf(" Book ID          : %d", id);
			printf("\n Volume of Book   : %d", vol);
			printf("\n Category         :%s", cat);
			printf(" Book Quantity    : %d", items);
			printf("\n Price            : %d", price);

		}
		fclose(bookptr);

		// --- Asking whether to continue the search --- //
		do
		{
			if (more_search != 'N' && more_search != 'Y' && more_search != 'n' && more_search != 'y')
			{
				printf("\n Sorry! We didn't get your answer .... \n");
			}

			printf("\n\n Want to Search Any Other Book (Y/N): ");
			//int c; while ((c = getchar() != EOF && ch != '\n'));
			scanf("%c", &more_search);
		} while (more_search != 'N' && more_search != 'Y' && more_search != 'n' && more_search != 'y');

	}
	
	printf("\n\n");
	puts(" Press any key to continue ....");
	_getwch();

}
void add_categories(void)
{	
	system("cls");
	FILE* ptr = NULL;

	if ((ptr = fopen("prices.dat", "ab+")) == NULL)
	{
		printf("\n\n --- Something went wrong, Please Try Again Later --- ");
		puts("Press any key to continue ... ");  _getwch();
		exit(1);
	}

	int record = 1;
	do
	{
		if (record == 0)
		{
			printf("\n\t --- Invalid Number of Records --- ");
		}
		printf("\n Enter the number of records you want to Enter: ");
		scanf("%d", &record);
	} while (record == 0);

	for (int i = 1; i <= record; i++)
	{
		printf("\n Enter the Category of the book (no spaces allowed) : "); scanf("%s", price.name);
		printf("\n Enter the price of the book                        : "); scanf("%d", &price.e);

		fwrite(&price, sizeof(struct p), 1, ptr);
	}
	fclose(ptr);
	printf("\n");

	printf("\n\n Categories of Books Added Successfully ... ");
	printf("\n\nPress any key to continue ...");
	_getwch();
}
void remove_book(void)
{
	system("cls");
	printf("\n ----------------------------------- Remove a Book Record -------------------------------------- ");

	char temp_name[50];
	printf("\n\nEnter the book name to Remove: ");

	int ch; while ((ch = getchar()) != '\n' && ch != EOF); // buffer error eradication

	fgets(temp_name, sizeof(temp_name), stdin);

	FILE* bookptr = NULL;
	bookptr = fopen("books.txt", "r");
	if (!bookptr)
	{
		puts("Error ... Please Try Again Later ...."); exit(1);
	}

	FILE* temp = NULL;
	temp = fopen("temp.txt", "w");
	if (!temp)
	{
		puts("Error ... Please Try Again Later ...."); exit(1);
	}
;
	char string[50];
	int check = 0;

	fgets(string, sizeof(string), bookptr);

	while (!feof(bookptr))
	{
		if (!strcmp(string, temp_name))
		{
			fgets(string, sizeof(string), bookptr);
			strcpy(string, "\0");
			check = 1;
		}
		else
		{
			fputs(string, temp);
		}
		fgets(string, sizeof(string), bookptr);
	}

	if (check == 0)
	{
		printf("\n\n -------- No such book exists in Database --------\n");
	}
	else
	{
		printf("\n\n   --- Remove Successfull --- ");
	}

	fclose(bookptr);
	fclose(temp);
	
	remove("books.txt");
	int i = rename("temp.txt", "books.txt");

	printf("\nPress any key to continue ....");
	_getwch();

}
void add_user(void)
{
	system("cls");
	FILE* ptr = fopen("user.dat", "ab");
		if (ptr == NULL)
	{
		printf("\n\n --- Something went wrong, Please Try Again Later --- ");
		puts("Press any key to continue ... ");  _getwch();
		exit(1);
	}

	printf("\n Enter the User Name: ");
	//int ch; while ((ch = getchar()) != '\n' && ch != EOF); // Eliminating the buffer
	scanf(" %[^\n]s", &user.name);
	char pass[20];

	int temp=1;
	do
	{
		if (temp == 0)
		{
			printf("\n --- Not a Strong Password ---\n");
		}
		printf("\n Enter the primary Password for New User: ");
		scanf(" %[^\n]s", &user.pass);

		temp = pass_validity(user.pass);
	} while (temp == 0);

	fwrite(&user, sizeof(struct user), 1, ptr);
	fclose(ptr);

	// *** Usernames and Passwords of All Users are stored in user.dat file *** //

	// *** Creating a Seperate File for the New User *** // -------------------------------------------------------------
	char string[31];
	strcpy(string, "user_files/");
	strcat(string, user.name);
	strcat(string, ".dat");
	
	FILE *ptr_user = fopen(string, "wb");
	if (!ptr_user)
	{
		printf("\n\n --- Something went wrong, Please Try Again Later --- ");
		printf("\n\nPress any key to continue ... ");  _getwch();
		exit(1);
	}
	
	struct temp_struct
	{
		char name[31];
		//char pass[31];
		char gender;
		char age[2];
		char ph[13];
		char email[20];
		char address[50];
	};

	struct temp_struct t = { "", "", "20", "none", "none", "none" };
	strcpy(t.name, user.name);
	fwrite(&t, sizeof(t), 1, ptr_user);

	fclose(ptr_user);
	// *** File Created Successfully *** // -------------------------------------------------------------

	printf("\n\n --- *** New User Had Been Added Successfully *** --- ");
	printf("\n\nPress any key to continue .... ");
	_getwch();
}
void remove_user(void)
{
	system("cls");
	char again = 'y';
	do
	{

		printf("\n *.-------------------------------------------------------------------------------------.*");
		printf("\n \t\t\t     Remove a User ");
		printf("\n *.-------------------------------------------------------------------------------------.*\n\n");

		printf("\nEnter the User Name to Remove: ");
		char username[31];
		scanf(" %s", username);

		struct profile temp;
		char file_path[50]="";
		strcpy(file_path, "user_files/");
		strcat(file_path, username);
		strcat(file_path, ".dat");

		printf("\n ---- %s ---- \n", file_path);

		FILE* ptr = fopen(file_path, "rb");
		if (!ptr)
		{
			printf("\n\t\t ***--- Such User Doesnot Exists in Library's Database ---*** ");
		}
		else
		{
			fread(&temp, sizeof(temp), 1, ptr);

			printf("\n\n\t    ************ \t Your Details \t ************ \n");

			printf("\n\t\tName:        : %s", username);

			// *** Special Printing for Gender *** // ----------------------------------------------------------
			if (temp.gender == 'm')
				printf("\n\t\tGender       : %s", "Male");
			else if (temp.gender == 'f')
				printf("\n\t\tGender       : %s", "Female");
			else
				printf("\n\t\tGender       : %s", "Not Specified");

			printf("\n\t\tAge          : %s", temp.age);
			printf("\n\t\tEmail        : %s", temp.email);
			printf("\n\t\tAddress      : %s", temp.address);
			printf("\n\t\tPh#          : %s", temp.ph);
			printf("\n\t\tBooks Issued : %d", temp.books_issued);

			fclose(ptr);

			char sure = 'n';
			do
			{
				if (sure != 'n' && sure != 'y' && sure != 'N' && sure != 'Y')
				{
					printf("\n \t\t --- We didn't get your Anser, Please Try Again --- ");
				}
				printf("\n\n All data related to * %s * will be deleted permanently\n Are you sure you want to permanently delete the user (Y/N): ", username);
				scanf(" %c", &sure);
			} while (sure != 'n' && sure != 'y' && sure != 'N' && sure != 'Y');

			if (sure == 'y' || sure == 'Y')
			{
				remove(file_path);
				FILE* ptr2 = fopen("user.dat", "rb");
				if (!ptr2)
				{
					printf("\n\t\t --- This User can't be removed at this time, Please Try Again Later --- ");
					printf("\n\n Press any key to continue .... ");
					_getwch();
					exit(EXIT_SUCCESS);
				}

				FILE* ptr3 = fopen("temp.dat", "wb");
				if (!ptr3)
				{
					printf("\n\t\t ---  Something Went Wrong --- ");
					printf("\n\n Press any key to continue .... ");
					_getwch();
					exit(EXIT_SUCCESS);
				}

				struct user temp;
				fread(&temp, sizeof(temp), 1, ptr2);
				while (!feof(ptr2))
				{
					if (!strcmp(temp.name, username))
					{
						fread(&temp, sizeof(temp), 1, ptr2);
					}
					fwrite(&temp, sizeof(temp), 1, ptr3);
					fread(&temp, sizeof(temp), 1, ptr2);
				}

				fclose(ptr2); fclose(ptr3);
				remove("user.dat");
				int i = rename("temp.dat", "user.dat");

				char string_book_record[50];
				strcpy(string_book_record, "books_issuance_record/");
				strcat(string_book_record, username);
				strcat(string_book_record, ".dat");
				remove(string_book_record);

				printf("\n\n\t ---***---*** User Removed from Database ***---***---");
			}
		}
		char sure = 'n';
		do
		{
			if (sure != 'n' && sure != 'y' && sure != 'N' && sure != 'Y')
			{
				printf("\n \t\t --- We didn't get your Anser, Please Try Again --- ");
			}
			printf("\n\n\n Want to Remove Any other User(Y/N): ");
			int ch; while ((ch = getchar()) != '\n' && ch != EOF);
			scanf("%c", &again);
		} while (sure != 'n' && sure != 'y' && sure != 'N' && sure != 'Y');


	} while (again == 'y' || again == 'Y');

	printf("\n\nPress any key to continue .... ");
	_getwch();
	
}
void show_categories(void)
{
	system("cls");
	FILE *ptr = fopen("prices.dat", "rb+");
	if (ptr == NULL)
	{
		printf("\n --- Error --- "); exit(EXIT_FAILURE);
	}

	printf("\n\t   ====================================");
	printf("\n -------- Categories of Books with their Prices -------- ");
	printf("\n\t   ====================================");

	printf("\n\n\t Category\t\t Price");
	printf("\n\t--------------------------------");
	fread(&price, sizeof(struct p), 1, ptr);
	while (!feof(ptr)) {
		//printf("\n %s \t\t%d", price.name, price.e);
		printf("\n\t %s", price.name);
		printf(" \t\t");
		printf("%d", price.e);
		fread(&price, sizeof(struct p), 1, ptr);
	}
	fclose(ptr);

	printf("\n\nPress any key to continue .... ");
	_getwch();
}

void user_menu_display(void)
{
	printf("\n\t ------------------ Select Option: ------------------ ");
	printf("\n 1. Enter Profile Details");
	printf("\n 2. View Details of His/Her Personal Data");
	printf("\n 3. Issue a Book");
	printf("\n 4. View Books Issued");
	printf("\n 5. Search Books");
	printf("\n 6. Show Categories of books");
	printf("\n 7. Show Rules and Regulations");
	printf("\n 8. Membership Details");
	printf("\n 9. View Timings of Library");
	printf("\n 0. Logout");
}
void add_profile_details(char username[], char filename[])
{
	struct profile temp_user = {"", "", "", "", "",""};
	system("cls");

	FILE* profile;
	profile = fopen(filename, "wb+");
	if (!profile)
	{
		printf("\n --- *** Something Went Wrong *** --- ");
		printf("\n\nPress any key to continue"); _getwch();
		exit(EXIT_FAILURE);
	}
	int ch; while ((ch = getchar()) != '\n' && ch != EOF);
	printf("\n Note: Due to Security Reasons, You are unable to Change your Name\n\n --- ***\t Contact Your Admin to Change your name \t *** --- \n");
	
	struct profile end_user;

	// *** Validation for Gender of the User *** // ----------------------------------------------------------
	end_user.gender = 'm';
	do
	{
		if (end_user.gender != 'm' && end_user.gender != 'f' && end_user.gender != 'o' && end_user.gender != 'M' && end_user.gender != 'F' && end_user.gender != 'O')
		{
			printf("\n *** Sorry for Inconvenience --- Please Try Again *** \n");
		}
		printf("\nEnter Your Gender (M/F/O): ");
		scanf(" %c", &end_user.gender);

	} while (end_user.gender != 'm' && end_user.gender != 'f' && end_user.gender != 'o' && end_user.gender != 'M' && end_user.gender != 'F' && end_user.gender != 'O');

	// *** Validation for Age of the User *** // -------------------------------------------------------------
	int condition = 0;
	printf("\nEnter Your Age: "); scanf(" %s", end_user.age);
	do
	{
		if (strlen(end_user.age) > 2)
		{
			printf("\n *** \t\t Invalid AGE Entered \t\t ***\n"); condition = 1;
			printf("\nEnter Your Age: "); scanf(" %s", end_user.age);
		}
		if (!(isdigit(end_user.age[0]) && isdigit(end_user.age[1])))
		{
			printf("\n *** \t\t We didn't get your age \t\t ***\n"); condition = 1;
			printf("\nEnter Your Age: "); scanf(" %s", end_user.age);
		}
		else if (end_user.age[0] == '8' || end_user.age[0] == '9' || end_user.age[0] == '0')
		{
			printf("\n *** \t\t Invalid AGE Entered \t\t ***\n"); condition = 1;
			printf("\nEnter Your Age: "); scanf(" %s", end_user.age);
		}
		else
			condition = 0;

	} while (condition == 1); // using condition variable to prevent long conditions in while_loop_condition

	printf("\nEnter you email: "); scanf(" %[^\n]s", end_user.email);
	printf("\nEnter your address: "); scanf(" %[^\n]s", end_user.address);

	int check_for_ph = 1;
	do
	{
		if (check_for_ph == 0)
		{
			printf("\n\t\t ****** Try Again with a Different Phone Number ******\n");
		}
		printf("\nEnter your phone number: "); scanf(" %[^\n]s", end_user.ph);

		int i = 0;
		end_user.ptr = end_user.ph;
		for (; i < strlen(end_user.ph); i++);
		{
			if (!isdigit(*end_user.ptr))
			{check_for_ph = 0; break; }
			end_user.ptr++;
		}
	} while (check_for_ph == 0);
	end_user.books_issued = 0;

	fwrite(&end_user, sizeof(end_user), 1, profile);
	rewind(profile);

	// *** Reading and showing the Data to User *** // ---------------------------------------------------
	struct profile none;
	fread(&none, sizeof(temp_user), 1, profile);

	printf("\n\n\t    ************ \t Your Details \t ************ \n");

	printf("\n\t\tName:        : %s", username);

	// *** Special Printing for Gender *** // ----------------------------------------------------------
	if (none.gender == 'm')
		printf("\n\t\tGender       : %s", "Male");
	else if (none.gender == 'f')
		printf("\n\t\tGender       : %s", "Female");
	else
		printf("\n\t\tGender       : %s", "Not Specified");

	printf("\n\t\tAge          : %s", none.age);
	printf("\n\t\tEmail        : %s", none.email);
	printf("\n\t\tAddress      : %s", none.address);
	printf("\n\t\tPh#          : %s", none.ph);
	printf("\n\t\tBooks Issued : %d", none.books_issued);

	// closing the file pointer
	fclose(profile);

	printf("\n\n\t------------- Your Profile Details have been added -------------\n");
	printf("\nPress any key to continue ... ");
	_getwch();
}
void view_profile_details(char username[], char filename[])
{
	struct profile current_user = { "", "", "", "", "","" };
	system("cls");

	FILE* profile;
	profile = fopen(filename, "rb");
	if (!profile)
	{
		printf("\n --- *** Something Went Wrong *** --- ");
		printf("\n\nPress any key to continue"); _getwch();
		exit(EXIT_FAILURE);
	}

	fread(&current_user, sizeof(current_user), 1, profile);

	printf("\n\n\t    ************ \t Your Details \t ************ \n");

	printf("\n\t\tName:        : %s", username);

	// *** Special Printing for Gender *** // ----------------------------------------------------------
	if (current_user.gender == 'm')
		printf("\n\t\tGender       : %s", "Male");
	else if (current_user.gender == 'f')
		printf("\n\t\tGender       : %s", "Female");
	else
		printf("\n\t\tGender       : %s", "Not Specified");

	printf("\n\t\tAge          : %s", current_user.age);
	printf("\n\t\tEmail        : %s", current_user.email);
	printf("\n\t\tAddress      : %s", current_user.address);
	printf("\n\t\tPh#          : %s", current_user.ph);
	printf("\n\t\tBooks Issued : %d", current_user.books_issued);
	printf("\n\n\t    **************************************************");

	fclose(profile);
	printf("\n\nPress any key to continue ....");
	_getwch();
}
void issue_book(char username[], char filename[])
{
	struct profile current_user;

	FILE* booksfile;
	booksfile = fopen("books.txt", "r");
	if (!booksfile)
	{
		printf("\n --- *** Something Went Wrong *** --- ");
		printf("\n\nPress any key to continue"); _getwch();
		exit(EXIT_FAILURE);
	}
	
	printf("\nNOTE: You can Issue books from here, they will be delivered to your home address\nBut to Return You can to appear to the Library ... ");

	int again = 0;
	do
	{
		system("cls");

		printf("\nEnter the Book Name to Issue: ");
		char book_name[31];
		int ch; while ((ch = getchar()) != '\n' && ch != EOF); // Eliminating the buffer
		fgets(book_name, sizeof(book_name), stdin);

		char temp[50];
		int check = 0;
		fgets(temp, sizeof(temp), booksfile);
		while (!feof(booksfile))
		{
			if (!strcmp(book_name, temp))
			{
				check = 1; break;
			}
			fgets(temp, sizeof(temp), booksfile);
		}

		if (check == 1)
		{
			// --- Now, the name of the books is stored in temp
			int id, price, vol, items;
			fseek(booksfile, 1, SEEK_CUR);
			fscanf(booksfile, "%d %d %d %d", &id, &price, &vol, &items);

			// Storing the time in which the books is issued
			time_t t; time(&t);
			char issuence_time[30];
			
			strcpy(issuence_time, ctime(&t));

			printf("\n\t\t ***----- Please Consider the Folling Details: -----***\n");
			printf("\n\t\t Name               : %s", temp);
			printf("\n\t\t Book ID            : %d", id);
			printf("\n\t\t Volume             : %d", vol);
			printf("\n\t\t Price for Issuance : Rs %d", price);
			printf("\n\t\t Time for Issuance  : %s", issuence_time);
			printf("\n\t\t ******************************************************\n");

			char sure = 'n';
			do
			{
				if (sure != 'n' && sure != 'N' && sure != 'Y' && sure != 'y')
				{
					printf("\n --- Sorry for Inconvenience, Please Try Again ---\n");
				}
				printf("\n Are you sure you want to proceed issuance of the book (Y/N): ");
				scanf("%c", &sure);
			} while (sure != 'n' && sure != 'N' && sure != 'Y' && sure != 'y');
			
			char path[50];
			if (sure == 'y' || sure == 'Y')
			{
				strcpy(path, "books_issuance_record/");
				strcat(path, username);
				strcat(path, ".dat");

				FILE* ptr = fopen(path, "ab+");
				if (!ptr)
				{
					printf("\n --- Something Went Wrong, Please Try Again Later --- ");
					exit(1);
				}

				// *** Storing the Issuance Details in Username File *** // --------------------------------------------
				struct book_issue data;

				// Storing Data in Struct
				strcpy(data.name, book_name);
				data.vol = vol;
				data.price = price;
				strcpy(data.date, issuence_time);

				fwrite(&data, sizeof(data), 1, ptr);
				fclose(ptr);

				// Defining the path
				char path2[50];
				strcpy(path2, "user_files/");
				strcat(path2, username);
				strcat(path2, ".dat");

				FILE *ptr2= fopen(path2, "rb");
				if (!ptr2)
				{
					printf("\n --- Something Went Wrong, Please Try Again Later --- ");
					exit(1);
				}

				struct profile temp_user;
				fread(&temp_user, sizeof(temp_user), 1, ptr2);
				fclose(ptr2);

				ptr = fopen(path2, "wb");
				temp_user.books_issued += 1;
				fwrite(&temp_user, sizeof(temp_user), 1, ptr2);
				fclose(ptr2);

				printf("\n\t\t      *----- Book Issuance Successfull -----* ");
			}
			else
			{
				printf("\n\t\t      *** --- You Cancelled Your Issuance --- ***");
			}
		}
		else
		{
			printf("\n *** --- \t No Record of Such Book in our Library \t --- ***");

			char sure = 'n';
			do
			{
				if (sure != 'n' && sure != 'N' && sure != 'Y' && sure != 'y')
				{
					printf("\n --- Sorry for Inconvenience, Please Try Again ---\n");
				}
				//int c; while ((c = getchar()) != '\n' && c != EOF);
				printf("\n Do You Want To Try Again (Y/N): ");
				scanf("%c", &sure);
			} while (sure != 'n' && sure != 'N' && sure != 'Y' && sure != 'y');
			
			if (sure == 'y' || sure == 'Y')
			{
				again = 1;
			}
			else
			{
				again = 0;
			}
		}


	} while (again == 1);
	
	printf("\n\nPress any key to continue ....");
	_getwch();
}
void view_issued_books(char username[])
{
	system("cls");
	char file_path[50];
	strcpy(file_path, "books_issuance_record/");
	strcat(file_path, username);
	strcat(file_path, ".dat");

	FILE* ptr = fopen(file_path, "rb+");
	
	if (!ptr)
	{
		printf("\n\n You don't have issued any book yet ....");
	}
	else
	{
		struct book_issue p;

		printf("\n\n *---------------------------------------------------------------------------*\n");
		printf("\n Book Name\n Volume \t\t Price \t\t Issuance Date\n");
		printf("\n *---------------------------------------------------------------------------*\n\n");


		int i = 1; // To Display count
		fread(&p, sizeof(p), 1, ptr);
		while (!feof(ptr))
		{
			printf("\n %d. %s %d \t\t %d \t\t %s", i, p.name, p.vol, p.price, p.date);
			fread(&p, sizeof(p), 1, ptr);
			i++;
		}

		printf("\n Total Boosks Issued: %d", i - 1);
	}

	printf("\n\nPress any key to continue ...."); _getwch();
}
void show_rules(void)
{
	system("cls");
	FILE* rules = NULL;
	rules = fopen("rules.txt", "r");

	if (!rules)
	{
		puts(" ... Error ...");
		puts(" --- Please Try Again later --- ");
		exit(1);
	}

	char temp[200];

	fgets(temp, sizeof(temp), rules);
	while (!feof(rules))
	{
		printf("%s", temp);
		fgets(temp, sizeof(temp), rules);
	}

	fclose(rules);
	printf("\n\n");
	puts("Press any key to continue ... ");
	_getwch();
}
void membership_details(void)
{
	system("cls");
	FILE* file = fopen("membership_details.txt", "r");
	if (file == NULL)
	{
		printf("\n Something Went Wrong, Please Try Again Later .... ");
		printf("\n\nPress any key to continue ...."); _getwch();

		exit(1);
	}

	char temp_string[100];
	fgets(temp_string, sizeof(temp_string), file);
	while (!feof(file))
	{
		printf("%s", temp_string);
		fgets(temp_string, sizeof(temp_string), file);
	}

	printf("\n\n\nPress any key to continue .... "); _getwch();
}
void library_timings(void)
{
	system("cls");
	FILE* file = fopen("library_timings.txt", "r");
	if (file == NULL)
	{
		printf("\n Something Went Wrong, Please Try Again Later .... ");
		printf("\n\nPress any key to continue ...."); _getwch();

		exit(1);
	}

	char temp_string[100];
	fgets(temp_string, sizeof(temp_string), file);
	while (!feof(file))
	{
		printf("%s", temp_string);
		fgets(temp_string, sizeof(temp_string), file);
	}

	printf("\n\n\n Press any key to continue .... "); _getwch();
}


// *** Extra Functions *** // ---------------------------------------------------------------------------------

int pass_validity(char pass[])
{
	int temp = 0;
	int l = 0, u = 0, s = 0, n = 0;

	for (int i = 0; pass[i] != '\0'; i++)
	{
		if (isalpha(pass[i]))
		{
			if (islower(pass[i]))
				l = 1;
			else if (isupper(pass[i]))
				u = 1;
		}
		else if (isdigit(pass[i]))
			n = 1;
		else if (ispunct(pass[i]))
			s = 1;
	}

	if (s + n + u + l == 4)
		return 1;
	else
		return 0;
}
