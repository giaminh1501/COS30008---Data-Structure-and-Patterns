#include <iostream>
#include <stdexcept>

using namespace std;

//#define P1
//#define P2
//#define P3

#ifdef P1
#include "KeyProvider.h" 

int runP1(string argv[2])
{
    cout << "Testing KeyProvider with \"" << argv[0]
        << "\" and \"" << argv[1] << "\"" << endl;

    KeyProvider lKeyWord(argv[0]);
    string& lMessage = argv[1];

    for (char c : lMessage)
    {
        if (isalpha(c))
        {
            cout << *lKeyWord;
            lKeyWord << c;
        }
        else
        {
            cout << ' ';
        }
    }

    cout << "\n";

    for (char c : lMessage)
    {
        cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
    }

    cout << "\nCompleted" << endl;

    return 0;
}
#endif

#ifdef P2
#include "Vigenere.h" 

int runP2(string argv[2])
{
    Vigenere lSrambler(argv[0]);
    string lMessage = argv[1];

    // Test encoding 
    cout << "Encoding \"" << lMessage
        << "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;

    for (char c : lMessage)
    {
        cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
    }

    cout << "\n";

    string lEncodedMessage;

    for (char c : lMessage)
    {
        lEncodedMessage += lSrambler.encode(c);
    }

    cout << lEncodedMessage << "\nCompleted" << endl;

    // Test decoding 
    lSrambler.reset();

    cout << "Decoding \"" << lEncodedMessage
        << "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;

    for (char c : lEncodedMessage)
    {
        cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
    }

    cout << "\n";
    
    string lDecodedMessage;

    for (char c : lEncodedMessage)
    {
        lDecodedMessage += lSrambler.decode(c);
    }

    cout << lDecodedMessage << "\nCompleted" << endl;

    return 0;
}
#endif

#ifdef P3
#include "iVigenereStream.h" 

int runP3(string argv[2])
{
    iVigenereStream lInput([](Vigenere& aCipherProvider, char aCharacter)
        {
            return aCipherProvider.decode(aCharacter);
        }, argv[0], argv[1].c_str());

    if (!lInput.good())
    {
        cerr << "Cannot open input file: " << argv[1] << endl;

        return 2;
    }

    cout << "Decoding \"" << argv[1] << "\" using \"" << argv[0] << "\"." << endl;

    char lCharacter;
    while (lInput >> lCharacter)
    {
        cout << lCharacter;
    }
    
    lInput.close();

    cout << "Completed." << endl;

    return 0;
}
#endif

int main(int argc, char* argv[])
{
#ifdef P1
    string lArgv1[] = { "Relations", "To be, or not to be: that is the question:" };

    return runP1(lArgv1);
#endif

#ifdef P2
    string lArgv2[] = { "Relations", "To be, or not to be: that is the question:" };

    return runP2(lArgv2);
#endif

#ifdef P3
    string lArgv3[] = { "Relations", "sample_3.txt" };

    return runP3(lArgv3);
#endif
}
