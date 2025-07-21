#include <iostream>
#include <fstream>
#include <string>
#include <regex>

// Paths to your files
const std::string progress_path = "progress.md";
const std::string readme_path = "README.md";
const int total_problems = 120;

int count_done_problems() {
    std::ifstream file(progress_path);
    std::string line;
    int count = 0;
    std::regex done_regex("✅ Done");
    while (std::getline(file, line)) {
        if (std::regex_search(line, done_regex)) {
            count++;
        }
    }
    return count;
}

void update_readme(int solved) {
    std::ifstream infile(readme_path);
    std::string content, line;
    std::regex bar_regex(R"(https://progress-bar\.dev/\d+/\?scale=\d+&title=Problems%20Solved)");
    std::string new_bar = "https://progress-bar.dev/" + std::to_string(solved) +
                          "/?scale=" + std::to_string(total_problems) + "&title=Problems%20Solved";
    while (std::getline(infile, line)) {
        line = std::regex_replace(line, bar_regex, new_bar);
        content += line + "\n";
    }
    infile.close();

    std::ofstream outfile(readme_path);
    outfile << content;
    outfile.close();
}

int main() {
    int solved = count_done_problems();
    update_readme(solved);
    std::cout << "Progress bar updated: " << solved << " problems solved out of " << total_problems << std::endl;
    return 0;
}