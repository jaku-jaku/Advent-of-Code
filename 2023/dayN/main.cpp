/* [ Advent of Code - Day N ]
 *
 * author: Jack (Jianxiang) Xu
 * Date of completion: Sept. 18, 2024
 *
 * Debug: Debug prints can be enabled by flagging `ENABLE_DEBUG_PRINT` to `ENABLE`
 */

#include <fstream>  // ifstream
#include <sstream>  // getfile
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

    
    return EXIT_SUCCESS;
}