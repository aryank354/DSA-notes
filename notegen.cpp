#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iomanip> // Required for setfill and setw

using namespace std;

// Formats a link for the README files
string formatLink(const string& path, const string& text) {
    ostringstream oss;
    oss << "- [" << text << "](" << path << ")";
    return oss.str();
}

// Sanitizes a string by replacing spaces with underscores
string sanitize(const string& str) {
    string result;
    for (char c : str) {
        result += (c == ' ') ? '_' : c;
    }
    return result;
}

// Updates the root README.md if the topic isn't already listed
void updateRootReadme(const string& topic) {
    string rootReadmePath = "README.md";
    ifstream infile(rootReadmePath);
    if (!infile.is_open()) {
        cerr << "Warning: Could not open " << rootReadmePath << ". It will be created if possible.\n";
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(topic) != string::npos) {
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        ofstream outfile(rootReadmePath, ios::app);
        if (!outfile.is_open()) {
            cerr << "Error: Could not write to " << rootReadmePath << "\n";
            return;
        }
        outfile << formatLink("./DSA-Notes/" + topic + "/README.md", topic) << "\n";
        outfile.close();
    }
}

// Updates the topic's README.md by appending the new problem
// Change this function
void updateTopicReadme(const string& topicPath, const string& fileName, int problemNumber, const string& problemTitle) {
    string topicReadmePath = topicPath + "/README.md";
    ofstream outfile(topicReadmePath, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not write to " << topicReadmePath << "\n";
        return;
    }
    // Create the new link text including the problem number
    string linkText = to_string(problemNumber) + ". " + problemTitle;
    outfile << formatLink("./" + fileName, linkText) << "\n";
    outfile.close();
}

// Creates the markdown file with specific placeholders
void createProblemMarkdown(const string& fullPath, const string& title) {
    ofstream mdfile(fullPath);
    if (!mdfile.is_open()) {
        cerr << "Error: Could not create " << fullPath << "\n";
        return;
    }

    mdfile << "# " << title << "\n\n";
    mdfile << "### Problem link :-[paste here]\n\n";
    mdfile << "## ❓ Problem Statement\n\n";
    mdfile << "[PASTE_PROBLEM_STATEMENT_FROM_LEETCODE_HERE]\n\n";
    mdfile << "### example test cases\n\n";
    mdfile << "[PASTE_EXAMPLE_TEST_CASES_FROM_LEETCODE_HERE]\n\n";
    mdfile << "---\n";
    mdfile << "## 💡 Approaches\n\n";
    mdfile << "###📌 Best Approach from all of them below\n";
    mdfile << "[EXPLAIN_THE_BEST_APPROACH_LOGIC_HERE]\n";
    mdfile << "#### Code (C++)\n";
    mdfile << "```cpp\n// [PASTE_YOUR_BEST_APPROACH_CODE_SOLUTION_HERE]\n\n```\n";
    mdfile << "#### TC and SC\n";
    mdfile << "- **Time Complexity:** [ADD_TIME_COMPLEXITY_HERE]\n";
    mdfile << "- **Space Complexity:** [ADD_SPACE_COMPLEXITY_HERE]\n\n";
    mdfile << "---\n\n";

    mdfile << "### Approach 1\n";
    mdfile << "[EXPLAIN_APPROACH_1_LOGIC_HERE]\n";
    mdfile << "#### Code (C++)\n";
    mdfile << "```cpp\n// [PASTE_CODE_FOR_APPROACH_1_HERE]\n\n```\n";
    mdfile << "#### TC and SC\n";
    mdfile << "- **Time Complexity:** [ADD_TIME_COMPLEXITY_HERE]\n";
    mdfile << "- **Space Complexity:** [ADD_SPACE_COMPLEXITY_HERE]\n\n";
    mdfile << "---\n\n";

    mdfile << "### Approach 2\n";
    mdfile << "[EXPLAIN_APPROACH_2_LOGIC_HERE]\n";
    mdfile << "#### Code (C++)\n";
    mdfile << "```cpp\n// [PASTE_CODE_FOR_APPROACH_2_HERE]\n\n```\n";
    mdfile << "#### TC and SC\n";
    mdfile << "- **Time Complexity:** [ADD_TIME_COMPLEXITY_HERE]\n";
    mdfile << "- **Space Complexity:** [ADD_SPACE_COMPLEXITY_HERE]\n\n";
    mdfile << "---\n\n";

    mdfile << "## 📝 Notes\n\n";
    mdfile << "[ADD_ANY_ADDITIONAL_NOTES_OR_KEY_TAKEAWAYS_HERE]\n";

    mdfile.close();
}


int main() {
    string topic, problemTitle;
    int problemNumber;

    cout << "Enter topic (e.g., 01_Arrays): ";
    getline(cin, topic);

    cout << "Enter problem number (e.g., 1): ";
    cin >> problemNumber;
    if (cin.fail() || problemNumber < 0) {
        cerr << "Error: Invalid problem number\n";
        return 1;
    }
    cin.ignore(); 

    cout << "Enter problem title (e.g., Two Sum): ";
    getline(cin, problemTitle);

    string base = "DSA-Notes";
    string topicPath = base + "/" + topic;
    
    ostringstream fileNameStream;
    fileNameStream << setfill('0') << setw(3) << problemNumber << "_" << sanitize(problemTitle) << ".md";
    string fileName = fileNameStream.str();
    
    string fullPath = topicPath + "/" + fileName;

    if (!filesystem::exists(topicPath)) {
        if (!filesystem::create_directories(topicPath)) {
            cerr << "Error: Could not create directory " << topicPath << "\n";
            return 1;
        }
    }

    createProblemMarkdown(fullPath, problemTitle);
    updateTopicReadme(topicPath, fileName, problemNumber, problemTitle);
    updateRootReadme(topic);

    cout << "\n✅ Note created successfully at: " << fullPath << "\n";
    return 0;

    cout << "\n✅ Note created successfully at: " << fullPath << "\n";
    return 0;
}