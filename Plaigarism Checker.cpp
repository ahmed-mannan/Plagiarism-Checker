#include <iostream>   // cin, cout
#include <fstream>    // ifstream (file reading)
#include <vector>     // vector
#include <string>     // string
#include <algorithm>  // transform, remove_if, min
#include <iomanip>    // fixed, setprecision
#include <limits>     // numeric_limits
using namespace std;

#define RESET     "\033[0m" // output design
#define ITALIC    "\033[3m"
#define BLINK     "\033[5m"
#define HIGHLIGHT "\033[7m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define PURPLE    "\033[35m"
#define CYAN      "\033[36m"

vector<int> computeLPS(string pattern) // creates Longest Prefix Suffix table
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    int i = 1, j = 0;

    while (i < m)
    {
        if (pattern[i] == pattern[j])
        {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

bool KMP(string text, string pattern) // returns true if pattern is found in text
{
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = computeLPS(pattern);

    int i = 0, j = 0;
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            if (j == m - 1)
                return true; // found match
            else
            {
                i++;
                j++;
            }
        }

        else
        {
            if (j != 0) // not the first element
                j = lps[j - 1];
            else
                i++;
        }
    }
    return false; // not found
}

int count_chunks(vector<string> file1, vector<string> file2) // returns number of chunks pattern/source file is divided in
{
    int n;
    int min_size = min(file1.size(), file2.size()); // decide n based on smaller file
    if (min_size < 50)
        n = 3;
    else if (min_size <= 300)
        n = 5;
    else
        n = 7;
    return n;
}

vector<string> create_chunks(vector<string> file1, int n)
{
    vector<string> chunks;
    for (int i = 0; i <= file1.size() - n; i++) // creates one chunk per iteration, i is where chunk starts from
    {
        string chunk = "";
        for (int j = 0; j < n; j++) // slides window by 1 word
        {
            chunk += file1[i + j] + " "; // adds j-th word starting from i-th index
        }
        chunks.push_back(chunk);
    }
    return chunks;
}

vector<string> readFile(string file_name) // Function to read and clean text file
{
    ifstream file(file_name);
    vector<string> updated_file;
    string word;
    while (file >> word) // extracting word by word from file
    {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end()); // remove punctuation
        transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lowercase
        if (!word.empty()) updated_file.push_back(word);
    }
    return updated_file;
}

double calc_percentage (int x, int y, int z)
{
    double p;
    if (z) // if chunk is empty
        p = 0;
    else
        p = (x * 100.0 / y);

    return p;
}

string to_string (vector<string> vs) // converts vector string to string
{
    string s = "";
    for (const string &w : vs) // for-each loop, copies words from vs into w
        s += w + " ";
    return s;
}

void plagiarism_checker ( vector<string> file1, vector<string> file2)
{
    int n = count_chunks(file1, file2);
    vector<string> chunks = create_chunks(file1, n);
    string text = to_string (file2); // KMP only works on string,  not vector string

    int matched = 0;
    //vector<string> matched_chunks;

    for (string &chunk : chunks) // Check each chunk in second file using KMP
    {
        if (KMP(text, chunk))
        {
            matched++;
            //matched_chunks.push_back(chunk); // store matched chunks
        }
    }

    double percentage = calc_percentage(matched, chunks.size(), chunks.empty());

    cout << "\nChosen n (chunk size): " << n << endl;
    cout << "Total Chunks: " << chunks.size() << endl;
    cout << "Matched Chunks: " << matched << endl;
    cout << "Plagiarism Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;

    if (percentage < 20.0)
        cout << GREEN << "Status: Good to go :)" << RESET << endl;
    else if (percentage < 50.0)
        cout << YELLOW << "Status: Almost bad :/" << RESET << endl;
    else
        cout << RED << "Status: Very bad. Stop using ChatGPT! >.<" << RESET << endl;

    /*if (!matched_chunks.empty()) // shows chunk details
    {
        cout << "\nMatched Chunks:\n";
        for (const string &mc : matched_chunks)
        {
            cout << "- " << mc << endl;
        }
    }*/
}

int main()
{
    string file_name1, file_name2;
    vector<string> file1, file2;
    int choice;

    while (true)
    {
        cout << HIGHLIGHT << CYAN << "\n===== Plagiarism Checker =====\n" << RESET;
        cout << "1. Check Plagiarism\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) // handles invalid non-integer inputs
        {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << BLINK << RED << "\nPlease enter a number only!" << RESET << endl;
            continue; // restart loop
        }

        switch(choice)
        {
        case 1:
            cout << "Enter Source File Name: ";
            cin >> file_name1;
            cout << "Enter Given File Name: ";
            cin >> file_name2;

            file1 = readFile(file_name1);
            file2 = readFile(file_name2);

            if(file1.empty() || file2.empty())
            {
                cout << "\nOne of the files is empty or not found!" << endl;
            }
            else
            {
                plagiarism_checker(file1, file2);
            }
            break;

        case 2:
            cout << PURPLE << ITALIC << RED << "Exiting program... Goodbye!" << RESET << endl;
            return 0;

        default:
            cout << BLINK << RED << "\nInvalid choice. Try again.\n" << RESET ; // for invalid integer choice
            break;
        }
    }
}
