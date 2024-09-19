/* [ Advent of Code - Day 1 / Part 1 ]
 *
 * author: Jack (Jianxiang) Xu
 * Date of completion: Sept. 18, 2024
 * Challenge: https://adventofcode.com/2023/day/1
 *
 * Debug: Debug prints can be enabled by flagging `ENABLE_DEBUG_PRINT` to `ENABLE`
 */

#include <fstream> // ifstream
#include <sstream> // getfile
#include <string> 
#include <iostream> // cerr

/* Feature Flag */
#define ENABLE                      (1)
#define DISABLE                     (0)
#ifndef ENABLE_DEBUG_PRINT
#   define ENABLE_DEBUG_PRINT       (ENABLE) // USER: debugging mode
#endif // !ENABLE_DEBUG_PRINT

/* MACRO - Printing */
#define PRINT_ERROR_IN_RED(message) (std::cerr << "\033[31m [ERROR] " << (message) << "\033[0m" << std::endl);
#if ENABLE_DEBUG_PRINT
#   define DEBUG_PRINT(message)     (std::cerr << "\033[33m [DEBUG] " << (message) << "\033[0m" << std::endl);
#else
#   define DEBUG_PRINT(message)     // DO NOTHING!
#endif // ENABLE_DEBUG_PRINT

int main() {
    std::ifstream infile("./puzzle.txt");
    std::string line;
    int total_sum = 0;
    while (std::getline(infile, line))
    {        
        int first_digit = -1;
        int last_digit = -1;
        
        // forward search the first digit:
        auto itr = line.begin();
        for (; itr < line.end() && first_digit == -1; itr ++) {
            if (std::isdigit(*itr)){
                first_digit = *itr - '0';
            }
        }
        
        
        // if no more left, sync last digit with first digit:
        if (itr >= line.end()) last_digit = first_digit;
        
        // traverse the reset in a reverse order:
        // NOTE: currently itr is the next pointer of the first digit (so itr <= itr_reversed) to ensure full traverse
        for (auto itr_reversed = line.end(); itr <= itr_reversed && last_digit == -1; itr_reversed --) {
            if (std::isdigit(*itr_reversed)){
                last_digit = *itr_reversed - '0';
            }
        }
        
        // if non found, sync last digit with first digit:
        if (last_digit == -1) last_digit = first_digit;
        
        // compute:
        if (last_digit < 0 || first_digit < 0)
        {
            PRINT_ERROR_IN_RED("- No digits found from this line: " + line);
        }
        else
        {
            DEBUG_PRINT(line + " #: " + std::to_string(first_digit * 10 + last_digit));
            total_sum += first_digit * 10 + last_digit;
        }
    }
    std::cout << "+ Total Sum: " << total_sum << std::endl;
    infile.close();
    return EXIT_SUCCESS;
}