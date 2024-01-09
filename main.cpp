#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <cmath>

using namespace std;

struct Config
{
    string alphabet;
    int taille;
    int N;
};

Config globalConfig; // Variable globale pour stocker la configuration

// QUESTION 1 START
void calculateHash(const char *input, unsigned char *output)
{
    SHA1(reinterpret_cast<const unsigned char *>(input), strlen(input), output);
}

int test_hash(int argc, char *argv[])
{
    if (argc == 0)
    {
        cout << "wrong number of arguments\n";
        return 1;
    }

    cout << "fonction de hash = SHA1\n\n";

    for (int i = 0; i < argc; i++)
    {
        const char *clear = argv[i];
        unsigned char hash[SHA_DIGEST_LENGTH];
        calculateHash(clear, hash);

        cout << "SHA1 hash of \"" << clear << "\": ";
        for (int k = 0; k < SHA_DIGEST_LENGTH; k++)
        {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(hash[k]);
        }
        cout << "\n";
    }

    return 0;
}

// QUESTION 1 END
// QUESTION 2 START

// Fonction pour calculer N en fonction de alphabet et taille
void calculateN()
{
    if (globalConfig.alphabet.empty() || globalConfig.taille <= 0)
    {
        cerr << "Configuration invalide : alphabet vide ou taille non positive\n";
        exit(1);
    }

    int alphabetSize = globalConfig.alphabet.size();
    globalConfig.N = static_cast<int>(pow(alphabetSize, globalConfig.taille));
}

// Fonction pour tester le calcul de N
void testCalculateN(const std::string &alphabet, int taille)
{
    globalConfig.alphabet = alphabet;
    globalConfig.taille = taille;

    std::cout << "Configuration avant le calcul de N :\n";
    std::cout << "Alphabet : " << globalConfig.alphabet << "\n";
    std::cout << "Taille : " << globalConfig.taille << "\n";

    calculateN();

    std::cout << "Configuration après le calcul de N :\n";
    std::cout << "Alphabet : " << globalConfig.alphabet << "\n";
    std::cout << "Taille : " << globalConfig.taille << "\n";
    std::cout << "N : " << globalConfig.N << "\n";
}

// QUESTION 2 END

int main()
{
    testCalculateN("abcdefghijklmnopqrstuvwxyz", 4);
    return 0;
}
