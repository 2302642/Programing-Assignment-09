/*!*********************************************************************************************************************************************************************************************************************
\file       spelling.hpp
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

#ifndef SPELLING_HPP
#define SPELLING_HPP

#include <string>
#include <vector>

namespace hlp2 {
    class string_utils {                                                                                                        // defining class string_utils
        public:
            static std::string upper_case(std::string const& str);                                                              // to convert lower-case chracters in the specified string to upper-case
            static std::vector<std::string> split(std::string const& words);                                                    // to split a string into words
    };

    class spell_checker {                                                                                                       // defining class spell_checker
        public:
            enum SCResult {                                                                                                     // Enumeration for spell check results
                scrFILE_OK = -1,                                                                                                // File operation successful
                scrFILE_ERR_OPEN = -2,                                                                                          // Error opening file
                scrWORD_OK = 1,                                                                                                 // Word spelled correctly
                scrWORD_BAD = 2                                                                                                 // Word misspelled
            };
            struct lexicon_info {                                                                                               // Structure for storing lexicon information
                size_t shortest;                                                                                                // Length of the shortest word
                size_t longest;                                                                                                 // Length of the longest word
                size_t count;                                                                                                   // Total number of words
            };

            spell_checker(const std::string &lexicon);                                                                          // Constructor to initialize the spell checker with the provided lexicon file
            SCResult words_starting_with(char letter, size_t& count) const;                                                     // to identify words starting with a specific character
            SCResult word_lengths(std::vector<size_t>& lengths, size_t count) const;                                            // to identify the word lengths
            SCResult get_info(lexicon_info& info) const;                                                                        // to identify word information in the string
            SCResult spellcheck(std::string const& word) const;                                                                 // to identify if words are spelled corretcly regardless of caps or no caps
            SCResult acronym_to_word(std::string const& acronym, std::vector<std::string>& words, size_t maxlen = 0) const;     // to convert an acronym to words

        private:
            std::string dictionary;                                                                                             // path to the lexicon file
    };

} // end namespace hlp2

#endif // SPELLING_HPP
