#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur untuk simpul Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children; // Map karakter ke simpul Trie anak
    string description; // Deskripsi kata di simpul ini
    bool isEndOfWord; // Menandakan akhir dari sebuah kata

    TrieNode() : description(""), isEndOfWord(false) {} // Konstruktor untuk inisialisasi
};

// Kelas Trie
class Trie {
private:
    TrieNode* root; // Pointer ke simpul Trie root

public:
    Trie() {
        root = new TrieNode(); // Membuat simpul Trie root saat objek Trie dibuat
    }

    // Fungsi untuk memasukkan kata baru ke Trie
    void insert(string word, string meaning) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                node->children[c] = new TrieNode(); // Buat simpul anak jika belum ada
            }
            node = node->children[c];
        }
        if (node->isEndOfWord) {
            node->description = meaning;  // Update deskripsi jika kata sudah ada
            cout << "Successfully updated a slang word.\n"; // Pemberitahuan bahwa kata berhasil diperbarui
        } else {
            node->isEndOfWord = true;
            node->description = meaning;
            cout << "Successfully released new slang word.\n"; // Pemberitahuan bahwa kata baru berhasil dimasukkan
        }
    }

    // Fungsi untuk mencari arti dari sebuah kata dalam Trie
    string search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children.count(c)) {
                return "";
            }
            node = node->children[c];
        }
        return node->isEndOfWord ? node->description : "";
    }

    // Fungsi untuk mencari semua kata yang dimulai dengan sebuah prefiks
    vector<string> startsWith(string prefix) {
        vector<string> result;
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->children.count(c)) {
                return result;
            }
            node = node->children[c];
        }
        collectWords(node, prefix, result);
        sort(result.begin(), result.end());  // Urutkan hasil secara leksikografis
        return result;
    }

    // Fungsi rekursif untuk mengumpulkan semua kata dari simpul Trie tertentu
    void collectWords(TrieNode* node, string prefix, vector<string>& result) {
        if (node->isEndOfWord) {
            result.push_back(prefix + " (" + node->description + ")");
        }
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            collectWords(it->second, prefix + it->first, result);
        }
    }

    // Fungsi untuk mendapatkan semua kata dalam Trie
    vector<string> getAllWords() {
        vector<string> result;
        collectWords(root, "", result);
        sort(result.begin(), result.end());  // Urutkan hasil secara leksikografis
        return result;
    }
};

// Fungsi untuk memvalidasi apakah sebuah kata slang valid
bool isValidSlangWord(string word) {
    return word.length() > 1 && word.find(' ') == string::npos;
}

// Fungsi untuk memvalidasi deskripsi sebuah kata slang
bool isValidDescription(string description) {
    return description.find(' ') != string::npos;
}

int main() {
    Trie slangWords;
    int choice;

    do {
        cout << "\nBoogle Slang Word Application\n";
        cout << "1. Release a new slang word\n";
        cout << "2. Search a slang word\n";
        cout << "3. View all slang words starting with a certain prefix word\n";
        cout << "4. View all slang words\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string word, description;
                cout << "Input a new slang word [Must be more than 1 characters and contains no space]: ";
                cin >> word;
                while (!isValidSlangWord(word)) {
                    cout << "Invalid slang word. Must be more than 1 characters and contains no space. Try again: ";
                    cin >> word;
                }
                cout << "Input a new slang word description [Must be more than 2 words]: ";
                cin.ignore();
                getline(cin, description);
                while (!isValidDescription(description)) {
                    cout << "Invalid description. Must be more than 2 words. Try again: ";
                    getline(cin, description);
                }
                slangWords.insert(word, description);
                break;
            }
            case 2: {
                string word;
                cout << "Enter the slang word to search: ";
                cin >> word;
                while (!isValidSlangWord(word)) {
                    cout << "Invalid slang word. Must be more than 1 character and contain no spaces. Try again: ";
                    cin >> word;
                }
                string meaning = slangWords.search(word);
                if (meaning.empty()) {
                    cout << "There is no word \"" << word << "\" in the dictionary.\n";
                } else {
                    cout << "Slang word : " << word << "\n";
                    cout << "Description : " << meaning << "\n";
                }
                break;
            }
            case 3: {
                string prefix;
                cout << "Enter the prefix: ";
                cin >> prefix;
                vector<string> words = slangWords.startsWith(prefix);
                if (words.empty()) {
                    cout << "There is no prefix \"" << prefix << "\" in the dictionary.\n";
                } else {
                    cout << "Words starts with \"" << prefix << "\":\n";
                    for (const string& word : words) {
                        cout << word << "\n";
                    }
                }
                break;
            }
            case 4: {
                vector<string> words = slangWords.getAllWords();
                if (words.empty()) {
                    cout << "There is no slang word yet in the dictionary.\n";
                } else {
                    cout << "List of all slang words in the dictionary:\n";
                    for (const string& word : words) {
                        cout << word << "\n";
                    }
                }
                break;
            }
            case 5:
                cout << "Thank you... Have a nice day :)\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

