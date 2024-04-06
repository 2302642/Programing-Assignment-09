/*!*********************************************************************************************************************************************************************************************************************
\file       spelling.cpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202
\par        Section:         RSE
\par        Tutorial:        assignment 09
\par        File created on: 21/03/2024
\brief      checking the string for spelling, word starting with, word length, if lexicon, acronims

\par        File information:
            This file contains 
            2 namespace grouped functions
            - namespace STRING_UTILS
                - function to convert lower-case chracters in the specified string to upper-case
                - function to split a string into words

            - namespace SPELL_CHECKER
                - function to initialize the spell checker with the provided lexicon file
                - function to identify words starting with a specific character
                - function to identify the word lengths
                - function to identify word information in the string
                - function to identify if words are spelled corretcly regardless of caps or no caps
                - function to convert an acronym to words
***********************************************************************************************************************************************************************************************************************/
#include "spelling.hpp"
#include <fstream>          // forstd::ifstream
#include <sstream>          // for std::istringstream
#include <algorithm>        // for std::transform

namespace hlp2 {
//######################################################################################################################################################################################################################
//==================================================================================================================================================================================================================================================================
//|                                                                               STRING_UTILS CLASS FUNCTIONS                                                                                                                                                   |
//==================================================================================================================================================================================================================================================================
    std::string string_utils::upper_case(std::string const& str) {                                                                                  // function to convert the chracters in the specified string to uppercase
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);                                                                    // convert each character in the string to uppercase
        return result;
    }
    std::vector<std::string> string_utils::split(std::string const& words) {                                                                        // function to split a string into words
        std::vector<std::string> word;                                                                                                              // initilizing a vector to store the split words
        std::string letters;                                                                                                                        // initilizing a string to hold each word temporarily 
        std::istringstream input(words);                                                                                                            // creating an input string stream to read from the input string
        while (input >> letters) { word.push_back(letters); }                                                                                       // reading words from the input string stream and adding each word to the vector
        return word;                                                                                                                                // returning the vector of split words
    }
//==================================================================================================================================================================================================================================================================
//|                                                                             SPELL_CHECKER CLASS FUNCTIONS                                                                                                                                                   |
//==================================================================================================================================================================================================================================================================
    spell_checker::spell_checker(const std::string &lexicon) : dictionary(lexicon) {}                                                               // function to initialize the spell checker with the provided lexicon file
    spell_checker::SCResult spell_checker::words_starting_with(char letter, size_t& count) const {                                                  // function to identify words starting with a specific character
        count = 0;                                                                                                                                  // initializing the count of words starting with the specified character
        std::ifstream file(dictionary);                                                                                                             // opening the lexicon file
        if (!file.is_open()) { return scrFILE_ERR_OPEN; }                                                                                           // returning  error if file cannot be opened
    
        std::string word;                                                                                                                           // initializing the variable to store each word read from the file
        while (file >> word) {                                                                                                                      // reading words from the file until the end of the file
            if (std::tolower(word[0]) == std::tolower(letter)) { count++; }                                                                         // incrementing count if the first character of the word matches the specified character
        }
        return scrFILE_OK;                                                                                                                          // returning 1
    }
    spell_checker::SCResult spell_checker::word_lengths(std::vector<size_t>& lengths, size_t count) const {                                         // function to identify the word lengths
        lengths.assign(count + 1, 0);                                                                                                               // Initializing the lengths vector with zeros, and with size one more than the specified count
        std::ifstream file(dictionary);                                                                                                             // opening the lexicon file
        if (!file.is_open()) { return scrFILE_ERR_OPEN; }                                                                                           // returning  error if file cannot be opened                       
        std::string word;                                                                                                                           // initializing the variable to store each word read from the file
        while (file >> word) {                                                                                                                      // reading words from the file until the end of the file
            size_t len = word.length();                                                                                                             // calculating the length of the current word.
            if (len <= count) { lengths[len]++; }                                                                                                   // incrementing count if the length of the word is within the specified count in the lengths vector.
        }
        return scrFILE_OK;                                                                                                                          // returning 1
    }
    spell_checker::SCResult spell_checker::get_info(lexicon_info& info) const {                                                                     // function to identify word information in the string
        std::ifstream file(dictionary);                                                                                                             // opening the lexicon file
        if (!file.is_open()) { return scrFILE_ERR_OPEN; }                                                                                           // returning  error if file cannot be opened    
        std::string word;                                                                                                                           // initializing the variable to store each word read from the file
        info.shortest = std::string::npos;                                                                                                          // initializing shortest word length to maximum possible value
        info.longest = 0;                                                                                                                           // initializing longest word length to 0
        info.count = 0;                                                                                                                             // initializing word count to 0
        while (file >> word) {                                                                                                                      // reading words from the file until the end of the file
            size_t len = word.length();                                                                                                             // getting the length of the current word
            if (len < info.shortest) {  info.shortest = len; }                                                                                      // checking if the current word is shorter than the shortest word found and updating the shortest word length
            if (len > info.longest)  {  info.longest = len;  }                                                                                      // checking if the current word is longer than the longest word found  and updating the longest word length
            info.count++;                                                                                                                           // incrementing the word count
        }
        return scrFILE_OK;                                                                                                                          // returning 1
    }
    spell_checker::SCResult spell_checker::spellcheck(std::string const& word) const {                                                              // function to identify if words are spelled corretcly regardless of caps or no caps
        std::ifstream file(dictionary);                                                                                                             // opening the lexicon file
        if (!file.is_open()) { return scrFILE_ERR_OPEN; }                                                                                           // returning  error if file cannot be opened    
        std::string word_check;                                                                                                                     // initializing the variable to store each word read from the file
        while (file >> word_check) {                                                                                                                // reading words from the file until the end of the file
            bool isMatch = true;                                                                                                                    // initializing the flag to indicate if the word matches
            for (size_t i = 0; i < word.length(); ++i) {                                                                                            // iterating through each character of the input word
                if (std::toupper(word_check[i]) != std::toupper(word[i])) { isMatch = false; break; }                                               // comparing characters and setting the match flag to false and exiting the loop if characters don't match
            }
            if (isMatch && word_check.length() == word.length()) { return scrWORD_OK; }                                                             // checking if the word from file matches input word and is of same length and returning WORD_OK if the word is found in the lexicon
        }
        return scrWORD_BAD;                                                                                                                         // returning 2
    }
    spell_checker::SCResult spell_checker::acronym_to_word(const std::string& acronym, std::vector<std::string>& words, size_t maxlen) const {      // function to convert an acronym to words
        std::ifstream file(dictionary);                                                                                                             // opening the lexicon file
        if (!file.is_open()) { return scrFILE_ERR_OPEN; }                                                                                           // returning  error if file cannot be opened       
        words.clear();                                                                                                                              // emptying the vector before fill it
   
        std::string word;                                                                                                                           // initializing the variable to store each word read from the file
        while (file >> word) {                                                                                                                      // reading words from the file until the end of the file
            if (word.length() <= maxlen || maxlen == 0) {                                                                   
                if (std::toupper(word[0]) == std::toupper(acronym[0])) {                                                                            // checking if the first character of the word matches the first character of the acronym
                    size_t pos = 0;                                                                                                                 // initializing index for tracking acronym characters
                    for (char c : word) {                                                                                                           // iterating through the word
                        if (std::toupper(c) == std::toupper(acronym[pos])) {                                                                        // if the current character matches the next character in the acronym, move to the next character in both
                            ++pos;                                                                                                       
                            if (pos == acronym.length()) { words.push_back(word);  break; }                                                         // If all characters of the acronym are found in the word in the same order, add it to the vector
                        }
                    }
                }
            }
        }
        return scrFILE_OK;                                                                                                                          // returning -1
    }
//######################################################################################################################################################################################################################
} // end namespace hlp2

