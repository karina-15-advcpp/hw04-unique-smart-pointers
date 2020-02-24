/* hw4_pc1_pill_box.cpp - Number of attempts to fill a pillbox
   Author:  Karina Elias
   Module:	04
   Project:	Homework 04 - Programming Project 1
   
   Problem Statement: Start with a pillbox having 10 empty slots. Your job is to
   	put 10 pills (lettered A, B, C... J) by selecting a slot randomly for each
	pill until finding an empty slot. For each pill, record the number of
	attempts it took to find an empty slot for that pill.
   
   Algorithm / Plan:
	   1. Include iostream, iomanip, memory, and ctime libraries
	   2. Create a structure with letter of pill variable, number of attempts
	   		variable and number of original_slot for extra credit sorting
	   3. Create constructor in struct with variables in step 2 initialized
	   4. In main, initialize random seed for different random numbers ea. run
	   5. Create array of 10 unique pionters to Pill structures
	   		Using unique pointers guarantees that ea. Pill can be referenced by
	   		1 and only 1 slot in the pillbox
	   6. Create a loop which processes a single pill (lettered A, B, C...
	   		through J).
	   7. Create an inner loop that creates a random number between 0-9 and
	   		track the number of attempts to find an open slot in the pillbox
	   8. If slot is not available try another random number and increase
	   		attempts by 1, otherwise create a new Pill structure for current
	   		pill letter, number of attempts it took to find an available slot
			for this pill and current (original) slot number
	   9. After all 10 pills have been placed into a slot in the pillbox, print
	   		a report showing:
	   			- slot number (0-9) (slots[i]->original_slot)
	   			- pill letter assigned to that slot (slot[i]->pill_letter)
	   			- number of attempts to find an available slot for that pill
	   				letter (slots[i]->attempts)
	   			- grand total of number of attempts for all pills
	   		e.g.
	   		  Slot  Pill  Attempts
			  ----  ----  --------
			     0     G       4
			     1     A       1
			     2     H       4
			     3     I       9
			     4     B       1
			     5     E       3
			     6     F       1
			     7     J       7
			     8     C       2
			     9     D       1
			
			  Total Attempts  31
	   10. Extra credit: Sort array of pointers by pill letter (w/o creating any
	   		additional pointers) using selection sort
	   11. Print report again showing the results by pill letter
*/

using namespace std;

/* libraries */
#include <iostream>
#include <iomanip>	// setw, setfill
#include <memory>	// unique_ptr
#include <ctime>	// time for random seed

/* constants */
const int NUMBER_OF_PILLS	= 10;	// size of pills array
const char PILL_ARR[10] 	= {'A', 'B', 'C', 'D', 'E',
							   'F', 'G', 'H', 'I', 'J'};	// pill letters, A=0
const char SPACE 			= ' ';	// setfill in report
const char HYPHEN			= '-';	// setfill in report
const int SLOT_WIDTH 		= 6;	// setw for slot and pill column in report
const int ATTEMPTS_WIDTH	= 10;	// setw for attempts column in report

//*******************************************************************
//							Pill structure							*
// Includes variables for pill letter, number of attempts and number*
// of original slot. Also includes constructor with variables		*
// initialized.														*
//*******************************************************************
struct Pill {
	/* data members */
	char pill_letter;	// letter of pill
	int attempts;		// number of attempts for pill
	int original_slot;	// number of slot placed in, used for sorting
	
	/* constructor */
	Pill(char letter, int attempt, int orig_slot)
	{
		pill_letter = letter;
		attempts = attempt;
		original_slot = orig_slot;
	}
};

/* function prototypes */
int fillPillbox(unique_ptr<Pill> []);
void sortByPillLetter(unique_ptr<Pill> []);
void printReport(unique_ptr<Pill> []);

int main() {
	
	/* variables */
	srand(time(NULL));	// initialize random seed
	// create an array of 10 unique pointers to Pill structures
	unique_ptr<Pill> slots[NUMBER_OF_PILLS];
	int total;			// total attempts for all pills
	
	total = fillPillbox(slots);	// call function to completely fill pillbox
	
	// print report sorted by slot and print total attempts made for all pills
	cout << "Report (sorted by Slot)" << endl;
	printReport(slots);
	cout << "  Total Attempts  " << total << endl << endl;

	sortByPillLetter(slots);	// extra credit: call function to sort by pill
	
	// print report sorted by pill letter
	cout << "Report (sorted by Pill)" << endl;
	printReport(slots);
	
	return 0;
}

//*******************************************************************
//							fillPillbox								*
// Goes through pills A-J and attempts to find an empty pillbox slot*
// until all slots are filled. Returns the total number of attempts *
// made for all pills.												*
//*******************************************************************
int fillPillbox(unique_ptr<Pill> slots[])
{
	/* variables */
	int total,			// total count of all pill attempts
		attempts,		// attempts per pill
		random_slot;	// random slot number to attempt to place current pill
	
	// for loop to process each pill starting with A-J (10 pills)
	for(int i = 0; i < NUMBER_OF_PILLS; i++)
	{
		attempts = 0;	// reset attempts to 0 for each pill
		// display current pill letter (A=0, B=1, C=3, etc.)
		cout << "Slot  attempts for Pill " << PILL_ARR[i] << ": ";
		// attempts to find an open slot for current pill
		do
		{
			random_slot = rand() % 10;	// random number 0-9 (10 slots)
			cout << random_slot << " ";	// display random slot attempt
			attempts++;					// count + 1 for attempt made
		} while(slots[random_slot]);	// continue to look for available slot
		// display total number of attempts made for current pill letter
		cout << "\nTotal attempts for Pill " << PILL_ARR[i] << ": " << attempts
			<< endl << endl;
		// create a new Pill structure for current pill letter, attempts it
		//	it took, to find an available slot, and the slot number it ended in
		unique_ptr <Pill> new_pill(
								new Pill(PILL_ARR[i], attempts, random_slot));
		// use move function to assign pill letter to slot number in array
		slots[random_slot] = move(new_pill);
		total += attempts;	// add current pill attempts to total attempts
	}	// END FOR LOOP: start looking for available slot for the next pill
	
	return total;
}

//*******************************************************************
//							sortByPillLetter						*
// Extra credit: Sort array pointer by pill letter (w/o creating any*
// additional pointers) using selection sort.						*
//*******************************************************************
void sortByPillLetter(unique_ptr<Pill> slots[])
{
	// traverse through boundary of unsorted subarray
	for(int i = 0; i < NUMBER_OF_PILLS - 1; i++)
	{
		// find the minimum element in unsorted array
		for(int j = i + 1; j < NUMBER_OF_PILLS; j++)
		{
			// use swap function if letter is not in alphabetical order
			if(slots[i]->pill_letter > slots[j]->pill_letter)
			{
				// swap w/o creating new pointers
				slots[i].swap(slots[j]);
			}
		}
	}
}

//*******************************************************************
//							printReport								*
// Prints a report showing the slot number (0-9)					*
// (slots[i]->original_slot), pill letter assigned to that slot		*
// (slot[i]->pill_letter) and the number of attempts to find an		*
// available slot for that pill letter (slots[i]->attempts).		*
//*******************************************************************
void printReport(unique_ptr<Pill> slots[])
{
	// print column headers
	cout << right << setw(SLOT_WIDTH) << setfill(SPACE) << "SLOT";
	cout << setw(SLOT_WIDTH) << "PILL";
	cout << setw(ATTEMPTS_WIDTH) << "ATTEMPTS" << endl;
	// print horizontal divider
	cout << setw(2) << "";
	cout << setw(SLOT_WIDTH - 2) << setfill(HYPHEN) << "";
	cout << setw(2) << setfill(SPACE) << "";
	cout << setw(SLOT_WIDTH - 2) << setfill(HYPHEN) << "";
	cout << setw(2) << setfill(SPACE) << "";
	cout << setw(ATTEMPTS_WIDTH - 2) << setfill(HYPHEN) << "" << endl;
	// print data for each pill, slot, and attempts
	for(int i = 0; i < NUMBER_OF_PILLS; i++)
	{
		cout << setw(SLOT_WIDTH) << setfill(SPACE) << slots[i]->original_slot;
		cout << setw(SLOT_WIDTH) << slots[i]->pill_letter;
		cout << setw(ATTEMPTS_WIDTH) << slots[i]->attempts << endl;
	}
}
