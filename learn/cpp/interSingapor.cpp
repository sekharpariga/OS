// Coding problem: 45 minute time limit.

// PROBLEM DEFINITION
// ------------------
// Reverse each word in the input string.
// The order of the words will be unchanged.
// A word is made up of letters and/or numbers.
// Other characters (spaces, punctuation) will not be reversed.

// NOTES
// ------
// Write production quality code
// We prefer clarity over performance (though if you can achieve both - great!)
// You can use the language that best highlights your programming ability
//    the template below is Python – but you can write
//    in Java/C++/C#/Haskell/etc if you feel you solve the
//    problem better in that language.
// A working solution is preferred (assert in main() should succeed)
// Bonus points for good tests

#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>

std::string reverse_words(const std::string &str)
{
    // TODO: Implement this function
    std::string result = "";
    std::string word = "";
    bool flagCompleteWord = true;

    /*
     *  Took unsigned long int
     *  To support upto 2^64 char length of big input string 
    */
    for(unsigned long int i = 0; i < str.length(); i++)
    {
        if(!isalnum(str[i]))
        {
            reverse(word.begin(), word.end());
            result = result + word + str[i];
            word = "";
            flagCompleteWord = false;
        }
        else
        {
            word = word + str[i];
            flagCompleteWord = true;
        }
    }

    if(flagCompleteWord)
    {
        reverse(word.begin(), word.end());
        result = result + word;
    }

    return result;
}

int main()
{
    std::string test_str = "String;   2be reversed...";
    std::string test_str2 = "sin#gapor;be5e reve44rsed453";
    std::string test_str3 = "in%$#check-.!@#..56..873..343523..**";
    std::string test_str4 = "...a...a....a...a....a...a....a";
    std::string test_str5 = "!@#$%^&*()_##sekhar#&&**^^%%$$##";
    std::string test_str6 = "Hello World!";
    std::string test_str7 = "*********";
    std::string test_str8 = ".*.*.*.*";
    std::string test_str9 = ".........BABA";
    std::string test_str10 = "BABA.....BABA....BABA";

    assert(reverse_words(test_str) == "gnirtS;   eb2 desrever...");
    assert(reverse_words(test_str2) == "nis#ropag;e5eb 354desr44ever");
    assert(reverse_words(test_str3) == "ni%$#kcehc-.!@#..65..378..325343..**");
    assert(reverse_words(test_str4) == "...a...a....a...a....a...a....a");
    assert(reverse_words(test_str5) == "!@#$%^&*()_##rahkes#&&**^^%%$$##");
    assert(reverse_words(test_str6) == "olleH dlroW!");
    assert(reverse_words(test_str7) == "*********");
    assert(reverse_words(test_str8) == ".*.*.*.*");
    assert(reverse_words(test_str9) == ".........ABAB");
    assert(reverse_words(test_str10) == "ABAB.....ABAB....ABAB");
    
    /*
     *  Testing code for each input string
     * 
     *  std::cout << test_str10 << std::endl;
     *  std::cout << reverse_words(test_str10) << std::endl;
     * 
     */

    return 0;
}
