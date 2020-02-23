using namespace std;

#include <iostream>
#include <iomanip>
#include <memory>
#include <ctime>

const int NUMBER_OF_PILLS = 10;
const char PILL_ARR[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
const char SPACE = ' ';
const int SLOT_WIDTH = 6;
const int ATTEMPTS_WIDTH = 10;

struct Pill {
	char pill_letter;
	int attempts;
	int original_slot;
	
	Pill(char letter, int attempt, int original_slot)
	{
		pill_letter = letter;
		attempts = attempt;
		this->original_slot = original_slot;
	}
};

// prototypes
void printReport(unique_ptr<Pill> []);

int main() {
	// initialize random seed
	srand(time(NULL));
	// create an array of 10 unique pointers to Pill structures
	unique_ptr<Pill> slots[NUMBER_OF_PILLS];
	int total,
		attempts,
		random_slot;
	for(int i = 0; i < NUMBER_OF_PILLS; i++)
	{
		attempts = 0;
		cout << "Slot attempts for Pill " << PILL_ARR[i] << ": ";
		do
		{
			random_slot = rand() % 10;
			
			cout << random_slot << " ";
			attempts++;
		} while(slots[random_slot]);
		
		cout << "\nTotal attempts for Pill " << PILL_ARR[i] << ": " << attempts << endl << endl;
		unique_ptr <Pill> new_pill(new Pill(PILL_ARR[i], attempts, random_slot));
		slots[random_slot] = move(new_pill);
		total += attempts;
	}
	cout << "Report (sorted by Slot)" << endl;
	printReport(move(slots));
	cout << "Total Attempts  " << total << endl;

	// extra credit: sort by pill letter
	for(int i = 0; i < NUMBER_OF_PILLS - 1; i++)
	{
		for(int j = i + 1; j < NUMBER_OF_PILLS; j++)
		{
			if(slots[i]->pill_letter > slots[j]->pill_letter)
			{
				int temp_slot = slots[i]->original_slot;
				slots[i]->original_slot = move(slots[j]->original_slot);
				slots[j]->original_slot = move(temp_slot);
				int temp_letter = slots[i]->pill_letter;
				slots[i]->pill_letter = move(slots[j]->pill_letter);
				slots[j]->pill_letter = move(temp_letter);
				int temp_attempts = slots[i]->attempts;
				slots[i]->attempts = move(slots[j]->attempts);
				slots[j]->attempts = move(temp_attempts);
			}
		}
	}
	
	cout << "Report (sorted by Pill)" << endl;
	printReport(slots);
	
	return 0;
}

void printReport(unique_ptr<Pill> slots[])
{
	cout << right << setw(SLOT_WIDTH) << setfill(SPACE) << "SLOT";
	cout << right << setw(SLOT_WIDTH) << setfill(SPACE) << "PILL";
	cout << right << setw(ATTEMPTS_WIDTH) << setfill(SPACE) << "ATTEMPTS" << endl;

	cout << right << setw(2) << setfill(SPACE) << "";
	cout << right << setw(SLOT_WIDTH - 2) << setfill('-') << "";
	cout << right << setw(2) << setfill(SPACE) << "";
	cout << right << setw(SLOT_WIDTH - 2) << setfill('-') << "";
	cout << right << setw(2) << setfill(SPACE) << "";
	cout << right << setw(ATTEMPTS_WIDTH - 2) << setfill('-') << "" << endl;
	
	for(int i = 0; i < NUMBER_OF_PILLS; i++)
	{
		cout << right << setw(SLOT_WIDTH) << setfill(SPACE) << slots[i]->original_slot;
		cout << right << setw(SLOT_WIDTH) << setfill(SPACE) << slots[i]->pill_letter;
		cout << right << setw(ATTEMPTS_WIDTH) << setfill(SPACE) << slots[i]->attempts << endl;
	}
}
