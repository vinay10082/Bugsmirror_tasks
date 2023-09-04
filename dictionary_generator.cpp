#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class dictionary_class
{
public:
    map<string, string> dictionary;
    dictionary_class()
    {
        ifstream file("dictionary.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                istringstream iss(line);
                string word, meaning;
                getline(iss, word, ':');
                getline(iss, meaning);
                dictionary[word] = meaning;
            }
            file.close();
        }
    }

    void save_dictionary()
    {
        ofstream file("dictionary.txt");
        if (file.is_open())
        {
            for (const auto &entry : dictionary)
            {
                file << entry.first << ":" << entry.second << endl;
            }
            file.close();
        }
    }

    void add_word()
    {
        string word, meaning;
        cout << "Enter the word: ";
        cin >> word;
        cin.ignore();
        cout << "Enter the meaning: ";
        getline(cin, meaning);
        dictionary[word] = meaning;
        cout << "'" << word << "' added to the dictionary." << endl;
        save_dictionary();
    }

    void search_word()
    {
        string word;
        cout << "Enter the word to search: ";
        cin >> word;
        cin.ignore();
        auto it = dictionary.find(word);
        if (it != dictionary.end())
        {
            cout << "Meaning of '" << word << "': " << it->second << endl;
        }
        else
        {
            cout << "'" << word << "' not found in the dictionary." << endl;
        }
    }

    void remove_word()
    {
        string word;
        cout << "Enter the word to remove: ";
        cin >> word;
        cin.ignore();
        auto it = dictionary.find(word);
        if (it != dictionary.end())
        {
            dictionary.erase(it);
            cout << "'" << word << "' removed from the dictionary." << endl;
            save_dictionary();
        }
        else
        {
            cout << "'" << word << "' not found in the dictionary." << endl;
        }
    }
};

int main()
{
    cout << "Dictionary Console Tool" << endl;
    dictionary_class dic;

    while (true)
    {
        cout << "\nOptions:" << endl;
        cout << "1. Add word-meaning pair" << endl;
        cout << "2. Search for a word" << endl;
        cout << "3. Remove a word-meaning pair" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            dic.add_word();
            break;
        case 2:
            dic.search_word();
            break;
        case 3:
            dic.remove_word();
            break;
        case 4:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
