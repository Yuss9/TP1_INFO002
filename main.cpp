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

// HELP FUNCTION START

void updateGlobalConfigN()
{
    int alphabetSize = globalConfig.alphabet.size();
    globalConfig.N = static_cast<int>(pow(alphabetSize, globalConfig.taille));
}

// HELP FUNCTION END

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

    cout << "Calcul de N en fonction de l'alphabet et de la taille en cours ...\n " << endl;

    int alphabetSize = globalConfig.alphabet.size();
    globalConfig.N = static_cast<int>(pow(alphabetSize, globalConfig.taille));
}

// Fonction pour tester le calcul de N
int test_config(const std::string &alphabet, int taille)
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

    return 0;
}

// QUESTION 2 END

// QUESTION 3 START

// Fonction pour afficher l'aide
void showHelp()
{
    cout << "Usage: ./program --alphabet=<alphabet> --size=<size> <command>\n";
    cout << "Commands:\n";
    cout << "  hash <s1> <s2> ... : compute hash of strings s1, s2, ...\n";
    cout << "  calculateN  : calculate N, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test calculateN \n";
    cout << "  i2c  : test function i2c, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test i2c \n";
}
// QUESTION 3 END

// QUESTION 4 START

string i2c(string alphabet, int taille, int n)
{
    string result;
    while (n > 0)
    {
        int remainder = n % alphabet.size();
        result = alphabet[remainder] + result;
        n = n / alphabet.size();
    }

    // rajoute des A devant si la taille de la chaine est inferieur a la taille
    while (result.length() < taille)
    {
        result = 'A' + result;
    }

    return result;
}

int test_i2c()
{
    updateGlobalConfigN();
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "N : " << globalConfig.N << "\n";

    cout << "Test de la fonction i2c : \n";
    cout << "i2c(1234) = " << i2c(globalConfig.alphabet, globalConfig.taille, 1234) << std::endl;
    cout << "i2c(" << globalConfig.N - 1 << ") = " << i2c(globalConfig.alphabet, globalConfig.taille, globalConfig.N - 1) << std::endl;
    return 1;
}

// QUESTION 4 END

// MAIN TEST FUNCTION

int main_test(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cout << "wrong number of arguments\n";
        return 1;
    }

    char *test = argv[0];
    if (std::strcmp("hash", test) == 0)
    {
        return test_hash(argc - 1, argv + 1);
    }
    else if (std::strcmp("calculateN", test) == 0)
    {
        return test_config(globalConfig.alphabet, globalConfig.taille);
    }
    else if (std::strcmp("i2c", test) == 0)
    {
        return test_i2c();
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // TODO le 2 est a definir encore
    if (argc < 2)
    {
        cerr << "Insufficient arguments\n";
        showHelp();
        return 1;
    }

    // parse command line arguments alphabet and size
    for (int i = 1; i < argc; ++i)
    {
        const char *arg = argv[i];

        if (strcmp(arg, "test") == 0)
        {
            return main_test(argc - i - 1, argv + i + 1);
        }

        if (strncmp(arg, "--help", 7) == 0)
        {
            cout << " Help menu : " << arg << "\n";
            showHelp();
            return 1;
        }

        if (strncmp(arg, "--alphabet=", 11) == 0)
        {
            globalConfig.alphabet = arg + 11;
        }

        if (strncmp(arg, "--size=", 7) == 0)
        {
            globalConfig.taille = atoi(arg + 7);
        }
    }
}