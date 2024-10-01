#include "vowel.hpp"
#include <algorithm>
#include <cstring>
#include <unordered_set>

void removeVowels(std::vector<std::string> &str_vec)
{
    const std::unordered_set<char> vowels = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U', 'y', 'Y'};

    for(auto &word: str_vec)
    {  
        word.erase(std::remove_if(begin(word), end(word), [vowels](const auto & x){
                    return vowels.count(x) > 0;            
        }
        ),end(word));
        
    }
}