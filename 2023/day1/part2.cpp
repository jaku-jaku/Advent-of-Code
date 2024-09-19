/* [ Advent of Code - Day 1 / Part 2 ]
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

#ifndef ENABLE_PART_TWO
#   define ENABLE_PART_TWO          (ENABLE) // Disable to test Part 1, Isolate Part 2 changes
#endif // !ENABLE_PART_TWO

/* MACRO - Printing */
#define PRINT_ERROR_IN_RED(message) (std::cerr << "\033[31m [ERROR] " << (message) << "\033[0m" << std::endl);
#if ENABLE_DEBUG_PRINT
#   define DEBUG_PRINT(message)     (std::cerr << "\033[33m [DEBUG] " << (message) << "\033[0m" << std::endl);
#else
#   define DEBUG_PRINT(message)     // DO NOTHING!
#endif // ENABLE_DEBUG_PRINT

#if ENABLE_PART_TWO
#define NUMBER_ARR_SIZE (9U)
const std::string letters[NUMBER_ARR_SIZE] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
uint letter_progress[NUMBER_ARR_SIZE] = {0,0,0,0,0,0,0,0,0};

inline int progressNumberLetters(const char character){
    for (size_t i=0; i < NUMBER_ARR_SIZE; i++)
    {
        const std::string num = letters[i];
        if (num[letter_progress[i]] == character) {
            letter_progress[i] ++;
            if (letter_progress[i] == num.size())
                return (i + 1);
        }
        else
            letter_progress[i] = (num[0] == character);
    }
    return -1;
}
inline int progressNumberLettersReversed(const char character){
    for (size_t i=0; i < NUMBER_ARR_SIZE; i++)
    {
        const std::string num = letters[i];
        if (num[num.size() - letter_progress[i] - 1] == character) {
            letter_progress[i] ++;
            if (letter_progress[i] == num.size())
                return (i + 1);
        }
        else
            letter_progress[i] = (num[num.size() - 1] == character);
    }
    return -1;
}
#endif // ENABLE_PART_TWO

int main() {
    // std::ifstream infile("./test_part2.txt");
    std::ifstream infile("./puzzle.txt");
    std::string line;
    int total_sum = 0;

    while (std::getline(infile, line))
    {        
        int first_digit = -1;
        int last_digit = -1;
        
#if ENABLE_PART_TWO
        // zeroing the progress before
        memset(letter_progress, 0, sizeof(letter_progress));  // C style
        // OR: std::fill(letter_progress, letter_progress + NUMBER_ARR_SIZE, 0) // C++ idiomatic way from <algorithm>
#endif // ENABLE_PART_TWO
        
        // forward search the first digit:
        auto itr = line.begin();
        for (; itr < line.end() && first_digit == -1; itr ++) {
            if (std::isdigit(*itr)){
                first_digit = *itr - '0';
                break;
            }
            
#if ENABLE_PART_TWO
            // progress letters:
            first_digit = progressNumberLetters(*itr);
#endif // ENABLE_PART_TWO
        }
        
        // if no more left, sync last digit with first digit:
        if (itr >= line.end()) last_digit = first_digit;
        
#if ENABLE_PART_TWO
        // zeroing the progress before
        memset(letter_progress, 0, sizeof(letter_progress));
#endif // ENABLE_PART_TWO

        // traverse the reset in a reverse order:
        // NOTE: currently itr is the next pointer of the first digit (so itr <= itr_reversed) to ensure full traverse
        for (auto itr_reversed = line.end(); itr <= itr_reversed && last_digit == -1; itr_reversed --) {
            if (std::isdigit(*itr_reversed)){
                last_digit = *itr_reversed - '0';
                break;
            }
            
#if ENABLE_PART_TWO
            // progress letters:
            last_digit = progressNumberLettersReversed(*itr_reversed);
#endif // ENABLE_PART_TWO
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