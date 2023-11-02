#include "Bar.h"

using namespace std;


// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar() {
    m_fileName = "Foo";
    m_data = new LL<string>();
}


// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename) {
    m_data = new LL<string>();
    m_fileName = filename;
}


// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar () {
    delete m_data;
    m_data = nullptr;
}


// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
//template <class T>
void Bar::Start() {
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    DisplayBars();
    Export();
}


// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile() {
    ifstream myFile(m_fileName);  // variable for file in use
    string nodeData;  // variable to hold each string that is loaded in
    int count = 0;  // keeps track of how many words loaded in


    // takes in string, separates by whitespace. Then it removes the punctuation from
    // that single string and adds it to m_data
    while (myFile >> nodeData) { // while ( myFile >> nodeData) same thing as getline(myFile, nodeData, whitespace)
        count++;

        RemovePunct(nodeData);

        m_data->Insert(nodeData);
    }

    // prints how many words were loaded in
    cout << count << " loaded" << endl;
}


// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& myString) {
    string newString = "";  // converting given string to this one without punctuation

    // turns all letters in string to lowercase and adds all non-punctuation to new string
    for (string::iterator it = myString.begin(); it != myString.end(); ++it) {
        *it = tolower(*it);
    }

    // removes punctuation if it's first or last character in string
    // this leaves in any apostrophes or dashes in words
    if (ispunct(myString[0])) {
        myString.erase(0, 1);
    }
    if (ispunct(myString[myString.size() - 1])) {
        myString.erase(myString.size() - 1, 1);
    }
}


// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon() {
    string choice;  // holds user answer

    // asks user if to remove common words
    do {
        cout << "Would you like to remove all common words? " << endl;
        
        getline(cin, choice);
    } while (choice != "yes" && choice != "y" && choice != "no" && choice != "n");

    // calls RemoveAt function for every word in EXCLUDE_LIST
    if (choice == "yes" || choice == "y") {
        for (vector<string>::const_iterator it = EXCLUDE_LIST.begin(); it < EXCLUDE_LIST.end(); ++it) {
            m_data->RemoveAt(*it);
        }
        cout << "All common word removed." << endl;
    }
}


// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles() {
    string choice;  // holds user choice to remove singles or not
    int size = m_data->GetSize();  // holds original size of LL
    int count = 0;  // amount of words that have been removed


    do {
        cout << "Would you like to remove all words with a frequency of 1? " << endl;

        cin >> choice;
    } while (choice != "yes" && choice != "y" && choice != "no" && choice != "n");


    if (choice == "yes" || choice == "y") {

        // iterates through Linked List and calls RemoveAt for any key where frequency is 1
        // then resets i to account for changing LL
        for (int i = 0; i < size; i++) {
            if ((*m_data)[i].second == 1) {
                m_data->RemoveAt((*m_data)[i].first);
                count++;
                i = -1;
            }
        }
        cout << count << " words removed. " << endl;
    }
}


// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData() {

    for (int i = 0; i < m_data->GetSize(); i++) {

        // adds each pair to m_dataSorted multimap by frequency (key int)
        m_dataSorted.insert(pair<int, string>((*m_data)[i].second, (*m_data)[i].first));
    }
}


// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars() {
    for (multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); ++it) {
        cout << setw(18) << it->second << ": ";
        for (int i = 0; i < it->first; i++) {
            cout << barChar;
        }
        cout << endl;
    }
}


// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export() {
    string exportFile;  // holds stuff to export to new file

    // asks name of file
    cout << "What do you want to name the new text file? " << endl;

    cin >> exportFile;

    // sends to file
    ofstream outfile (exportFile);

    cout << "Output to export file " << exportFile << endl;


    // displays data in new file
    for (multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); ++it) {
        outfile << setw(18) << it->second << ": ";
        for (int i = 0; i < it->first; i++) {
            outfile << barChar;
        }
        outfile << endl;
    }
}