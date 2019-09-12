//**********************************************************************************************//
// Braden Mayew                                                                                 //
// COP 4530                                                                                     //
// Project 6 - Word, Number, and Character Usage Statistics                                     //
// ---------------------------------------- proj6.cpp ----------------------------------------- //
//**********************************************************************************************//

#include <iostream>
#include <map>
#include <ios>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
//#include <clock>

using namespace std;

// (1) Sequence Containers - store elements in linear manner
//		- vector, list, array, deque, forward_list
// (2) Associative Containers - based on the key concept
//		- ordered (sorted) and unordered
//		- ordered - map (one element per key) and multimap (multiple elements per key)
//			- key maps to value
//			- begin: key1 < key2 < key3 <...keyN < end
//			- map lookup: O(log(N))
//		- unordered - unordered_map and unordered_multimap: O(1)
// ----------------------------------------------------------------------------------- //
/*	test0
AAA001aaA1AAa01aaa01bb
Total 5 different characters, 5 most used characters:
No. 0: A                6
No. 1: a                6
No. 2: 0                4
No. 3: 1                4
No. 4: b                2

Total 2 different words, 2 most used words:
No. 0: aaa              4
No. 1: bb               1

Total 3 different numbers, 3 most used numbers:
No. 0: 01               2
No. 1: 001              1
No. 2: 1                1
-------------------------------------------------------------
test1
Fri Dec 26 22:15:35 EST 2003
Total 18 different characters, 10 most used characters:
No. 0:                  5
No. 1: 2                4
No. 2: 0                2
No. 3: 3                2
No. 4: 5                2
No. 5: :                2
No. 6: \n               1
No. 7: 1                1
No. 8: 6                1
No. 9: D                1

Total 3 different words, 3 most used words:
No. 0: fri              1
No. 1: dec              1
No. 2: est              1

Total 5 different numbers, 5 most used numbers:
No. 0: 26               1
No. 1: 22               1
No. 2: 15               1
No. 3: 35               1
No. 4: 2003             1    
-------------------------------------------------------------
test2
The transaction is expected to qualify as a tax-free reorganization 
in the United States with respect to the stock consideration. The 
transaction is expected to be completed in February 2004. Bear, 
Stearns & Co. Inc. advised North American Scientific and CIBC World 
Markets advised NOMOS on the transaction.       
Total 46 different characters, 10 most used characters:
No. 0:                  48
No. 1: e                30
No. 2: t                28
No. 3: a                22
No. 4: i                20
No. 5: n                19
No. 6: o                16
No. 7: r                16
No. 8: s                14
No. 9: c                13

Total 35 different words, 10 most used words:
No. 0: the              5
No. 1: transaction      3
No. 2: to               3
No. 3: is               2
No. 4: expected         2
No. 5: in               2
No. 6: advised          2
No. 7: qualify          1
No. 8: as               1
No. 9: a                1

Total 1 different numbers, 1 most used numbers:
No. 0: 2004             1
-------------------------------------------------------------
test3
*Input too long*
Total 96 different characters, 10 most used characters:
No. 0:                  216507
No. 1: e                134425
No. 2: t                95379
No. 3: i                91966
No. 4: n                87675
No. 5: o                85147
No. 6: a                82103
No. 7: s                70726
No. 8: r                67876
No. 9: c                50629

Total 8499 different words, 10 most used words:
No. 0: the              16726
No. 1: in               7408
No. 2: of               4820
No. 3: a                4492
No. 4: and              4215
No. 5: to               4188
No. 6: is               4188
No. 7: communication    3606
No. 8: for              2814
No. 9: that             2259

Total 931 different numbers, 10 most used numbers:
No. 0: 1                7798
No. 1: 2                5858
No. 2: 0                2713
No. 3: 3                2447
No. 4: 4                1667
No. 5: 5                1440
No. 6: 6                992
No. 7: 8                933
No. 8: 7                623
No. 9: 9                602
*/
// ----------------------------------------------------------------------------------- //   

// Function implemented to account for newline and tab characters with char map
void mostChar(int numChar, int Adjust, char mostUsed, int count) 
{
	if ((mostUsed == '\n') || (mostUsed == '\t')) { 
		if (mostUsed == '\n') {
			cout << "No. " << count << ": " << "\\n" << setw(Adjust-1) << numChar << endl; 
		}
		else if (mostUsed == '\t') {
			cout << "No. " << count << ": " << "\\t" << setw(Adjust-1) << numChar << endl; 
		}
	}
	else { cout << "No. " << count << ": " << mostUsed << setw(Adjust) << numChar << endl; }
}

// Function to print header of each section: displays the size of map and most used 
void printHeader(int size, int most, int t)
{
	if (t == 0) { cout << "Total of " << size << " different characters, " << most << " most used characters:" << endl; }
	else if (t == 1) { cout << "Total of " << size << " different words, " << most << " most used words:" << endl; }
	else if (t == 2) { cout << "Total of " << size << " different numbers, " << most << " most used numbers:" << endl; }
}

// Main Function
int main(void)
{
	map<char, int> CharacterStore;	// char and # of times its stored
	map<char, int> CharacterPos;	// only track when first encountered
	int charCount;
	char mostUsedChar;
	int CS_mapSize = 0;
	int CS_sizeCheck;	// if the map is smaller than 10 elements we only want to output mapSize() "most used" characters

	map<string, int> WordStore;
	map<string, int> WordPos;
	int wordCount;
	int WS_mapSize = 0;
	int WS_sizeCheck;	// if the map is smaller than 10 elements we only want to output mapSize() "most used" words
	string mostUsedWord;

	map<string, int> NumberStore;
	map<string, int> NumberPos;
	int numCount = 0;
	int NS_mapSize = 0;
	int NS_sizeCheck;	// if the map is smaller than 10 elements we only want to output mapSize() "most used" numbers
	string mostUsedNum;

	int rightAdjust = 0;
    string word;
    string number;
    char character;
    int type;
   
    char nextChar = cin.get();
    while (!cin.eof()) {	// beginning of while-loop
    	// is the input a digit?
   		if (isdigit(nextChar)) {
   			//clock_t start;
   			number = "";
   			// while the next char is a digit, append it to the entire number
    		while (isdigit(nextChar)) {
    			++CharacterStore[nextChar];
    			number = number + nextChar;
     			nextChar = cin.get();
    		}
    		//clock_t end = clock();
			//double time = (double) (start-end) / (CLOCKS_PER_SEC/1000);
			//cout << "The running time for WordStore iteration and print is: " << time << " milliseconds" << endl;
    		
    		//clock_t start;
    		// store the entire number into NumberStore map
    		map<string, int>::const_iterator NSitr; 
    		
   			NSitr = NumberStore.find(number);
   			//clock_t end = clock();
			//double time = (double) (start-end) / (CLOCKS_PER_SEC/1000);
			//cout << "The running time for WordStore iteration and print is: " << time << " milliseconds" << endl;
   			if (NSitr == NumberStore.end()) { // if == end() then "number" was not found inside of the NumberStore map
   				// Then the number is new, the numCount should be passed as value to NumberPos map
   				NumberPos[number] = numCount++;
   			}
    		++NumberStore[number];	// ++ (preincrement) auto-increments the value, i.e., the # of occurences of number
   		} 
   		
   		// is the input alpha?
   		else if (isalpha(nextChar)) {
   			
    		word = "";
    		// while the next char is an alpha character, append it to the entire word
    		while (isalpha(nextChar)) {
    			++CharacterStore[nextChar]; // ++ (preincrement) auto-increments the value, i.e., the # of occurences of char
     			char temp = tolower(nextChar);
     			word = word + temp;
     			nextChar = cin.get();
    		}
    		
   			// Check to see if the word has already been placed in the map
   			map<string, int>::const_iterator WSitr; 
   			
   			WSitr = WordStore.find(word);
   			
   			if (WSitr == WordStore.end()) { // if == end() then "word" was not found inside of the WordStore map
   				// Then the word is new, the wordCount should be passed as value to WordPos map
   				WordPos[word] = wordCount++;
   			}
   			++WordStore[word]; // ++ (preincrement) auto-increments the value, i.e., the # of occurences of word
   			
  		} 
  		
   		else {	// the character is none of the above, !isdigit && !isalpha
   			
    		++CharacterStore[nextChar];
    		nextChar = cin.get();
    		
   		}
   		
  	} // end of while-loop

// ----------------------------------------------------------------------------------- //
// CharacterStore Print Algorithm
  	//clock_t startChar = clock();
  	
  	// Top ten check
  	CS_mapSize = CharacterStore.size(); 
  	if (CS_mapSize < 10) { CS_sizeCheck = CS_mapSize; }
  	else { CS_sizeCheck = 10; }
  	cout << endl;
  	type = 0;
  	printHeader(CS_mapSize, CS_sizeCheck, type);
    if (!CharacterStore.empty()) {
    	// Loop only for the size of sizeCheck, because the top 10 could only be say 5 numbers, e.g., the entire map
    	for (int i = 0; i < CS_sizeCheck; i++) {
    		charCount = 0;
    		mostUsedChar = 0;
  			for (const auto cs : CharacterStore) {
  			    if (cs.second == charCount) {
					if ((static_cast<int>(cs.first) < static_cast<int>(mostUsedChar)))
                	{
                		rightAdjust = 21 - sizeof(cs.first); 
                    	mostUsedChar = cs.first;
                    	charCount = cs.second;
                	}
            	}
                else if ((cs.second > charCount)) {
                	rightAdjust = 21 - sizeof(cs.first); 
                    mostUsedChar = cs.first;
                    charCount = cs.second;
                }
    		}
    		//clock_t start;
    	CharacterStore.erase(mostUsedChar);
    	//clock_t end = clock();
			//double time = (double) (start-end) / (CLOCKS_PER_SEC/1000);
			//cout << "The running time for WordStore iteration and print is: " << time << " milliseconds" << endl;
    	mostChar(charCount, rightAdjust, mostUsedChar, i);
		}
	}

	//clock_t endChar = clock();
	//double Chartime = (double) (endChar-startChar) / (CLOCKS_PER_SEC/1000);
	//cout << "The running time for CharacterStore iteration and print is: " << Chartime << " milliseconds" << endl;

// ----------------------------------------------------------------------------------- //
// WordStore Print Algorithm
  	//clock_t startWord = clock();
  	
  	// Top ten check
  	rightAdjust = 0;
  	WS_mapSize = WordStore.size(); 
  	if (WS_mapSize < 10) { WS_sizeCheck = WS_mapSize; }
  	else { WS_sizeCheck = 10; }
  	cout << endl;
  	type = 1;
    printHeader(WS_mapSize, WS_sizeCheck, type);
    if (!WordStore.empty()) {
    	// Loop only for the size of sizeCheck, because the top 10 could only be say 5 numbers, e.g., the entire map
    	for (int i = 0; i < WS_sizeCheck; i++) {
    		wordCount = 0; 
    		mostUsedWord = ""; 
            // map<string, int>::iterator ws = WordStore.begin();
            for (const auto ws : WordStore) {
            	if (ws.second == wordCount) {
					if ((WordPos[ws.first] < WordPos[mostUsedWord]))
                	{
                		rightAdjust = 21 - ws.first.length(); 
                    	mostUsedWord = ws.first;
                    	wordCount = ws.second;
                	}
            	}
                else if ((ws.second > wordCount)) {
                	rightAdjust = 21 - ws.first.length(); 
                    mostUsedWord = ws.first;
                    wordCount = ws.second;
                }
			}	
		WordStore.erase(mostUsedWord);
		cout << "No. " << i << ": " << mostUsedWord << setw(rightAdjust) << wordCount << endl;
    	}	
	}

	//clock_t endWord = clock();
	//double Wordtime = (double) (endWord-startWord) / (CLOCKS_PER_SEC/1000);
	//cout << "The running time for WordStore iteration and print is: " << Wordtime << " milliseconds" << endl;

// ----------------------------------------------------------------------------------- //
// NumberStore Print Algorithm
	//clock_t startNum = clock();
  	
  	// Top ten check
  	rightAdjust = 0;
  	NS_mapSize = NumberStore.size(); 
  	if (NS_mapSize < 10) { NS_sizeCheck = NS_mapSize; }
  	else { NS_sizeCheck = 10; }
  	cout << endl;
  	type = 2;
    printHeader(NS_mapSize, NS_sizeCheck, type);
    if (!NumberStore.empty()) {
    	// Loop only for the size of sizeCheck, because the top 10 could only be say 5 numbers, e.g., the entire map
    	for (int i = 0; i < NS_sizeCheck; i++) {
    		numCount = 0; 
    		mostUsedNum = ""; 
            for (const auto ns : NumberStore) {
            	//cout << "\nNumber: " << ns.first << endl;
				if (ns.second == numCount) {
					if ((NumberPos[ns.first] < NumberPos[mostUsedNum]))
                	{
                		rightAdjust = 21 - ns.first.length(); 
                    	mostUsedNum = ns.first;
                    	numCount = ns.second;
                	}
            	}
                else if ((ns.second > numCount)) {
                	rightAdjust = 21 - ns.first.length(); 
                    mostUsedNum = ns.first;
                    numCount = ns.second;
                }
			}	
		NumberStore.erase(mostUsedNum);
		cout << "No. " << i << ": " << mostUsedNum << setw(rightAdjust) << numCount << endl;
    	}	
	}
	//clock_t endNum = clock();
	//double Numtime = (double) (endNum-startNum) / (CLOCKS_PER_SEC/1000);
	//cout << "The running time for NumberStore iteration and print is: " << Numtime << " milliseconds" << endl;
}