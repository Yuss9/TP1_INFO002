#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <cmath>
#include <sstream>
#include <cstring>
#include <vector>
#include <cmath>

#include <fstream>
#include <string>

#include <algorithm>
#include <locale>
#include <functional>

using namespace std;

struct Config
{
    string alphabet;
    int taille;
    long N;
    int alphabet_length;
    int height;
    int width;
    string hash;
    bool generateTableRandom = false;
};

Config globalConfig; // Variable globale pour stocker la configuration

vector<string> EMPREINTE;
vector<string> TEXTE;

// HELP FUNCTION START
int hexToDecimal(const std::string &hexValue)
{
    std::istringstream iss(hexValue);
    int decimalValue;
    iss >> std::hex >> decimalValue;
    return decimalValue;
}

void updateGlobalConfigN()
{
    if (globalConfig.alphabet.empty() || globalConfig.taille <= 0)
    {
        cerr << "Configuration invalide : alphabet vide ou taille non positive\n";
        exit(1);
    }

    int alphabetSize = globalConfig.alphabet.size();
    globalConfig.N = pow(alphabetSize, globalConfig.taille);
}

// HELP FUNCTION END

// QUESTION 1 START
void calculateHash(const char *input, unsigned char *output)
{
    SHA1((const unsigned char *)input, strlen(input), output);
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

        cout << "hash for = " << clear << endl;
        cout << "hash = ";
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            cout << hex << setw(2) << setfill('0') << (int)hash[i];
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
    globalConfig.N = pow(alphabetSize, globalConfig.taille);
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

    cout << "  h2i  : test function h2i, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test h2i \n";

    cout << "  nouvelle_chaine  : test function nouvelle_chaine, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test nouvelle_chaine \n";

    cout << "  create_table  : test function create_table, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test create_table \n";

    cout << "  save_table  : test function save open and affiche table, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test save_table \n";

    cout << "  crack  : test function crack, you need to create file table.txt CHECK README before ex : \n ./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --size=4 --height=1000 --width=3000 test crack \n";

    cout << "  stats  : test function stats ex : \n ./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=1000 test stats \n";
}
// QUESTION 3 END

// QUESTION 4 START

string i2c(int taille, uint64_t n)
{
    string result;
    for (int i = 0; i < taille; i++)
    {
        uint64_t remainder = n % globalConfig.alphabet.size();
        result = globalConfig.alphabet[remainder] + result;
        n = n / globalConfig.alphabet.size();
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
    cout << "i2c(1234) = " << i2c(globalConfig.taille, 1234) << std::endl;
    cout << "i2c(" << globalConfig.N - 1 << ") = " << i2c(globalConfig.taille, globalConfig.N - 1) << std::endl;
    return 1;
}

// QUESTION 4 END

// QUESTION 6 START
uint64_t h2i(const unsigned char *hash, size_t t, uint64_t N)
{
    return (*((uint64_t *)hash) + t) % globalConfig.N;
}

/* uint64_t h2i(const unsigned char *hash, size_t t, uint64_t N)
{
    uint64_t value;
    std::memcpy(&value, hash, sizeof(uint64_t));

    return (value + t) % N;
}
 */
int test_h2i()
{
    updateGlobalConfigN();
    const char *texte = "oups";

    cout << "alphabet = \"" << globalConfig.alphabet << "\"" << endl;
    cout << "taille = " << globalConfig.taille << endl;
    cout << "N = " << globalConfig.N << endl;
    unsigned char hash[SHA_DIGEST_LENGTH];

    calculateHash(texte, hash);
    cout << "\n";

    int t = 1;
    uint64_t result = h2i(hash, t, globalConfig.N);
    cout << dec << "h2i(hash(\"" << texte << "\"), " << t << ") = " << result << endl;

    return 0;
}

// QUESTION 6 END

// QUESTION 7 START

// Fonction pour transformer un indice en chaîne résultante
uint64_t i2i(uint64_t index, uint64_t t)
{
    std::string value = i2c(globalConfig.taille, index);

    // add \0 to value
    std::stringstream ss;
    ss << value << "\0";
    value = ss.str().c_str();
    ////////////////////////////////////////////////////////////////////////////
    TEXTE.push_back(value);

    unsigned char hash[SHA_DIGEST_LENGTH];
    calculateHash(value.c_str(), hash);
    EMPREINTE.push_back((const char *)hash);

    return h2i((const unsigned char *)(hash), t, globalConfig.N);
}

// Fonction pour afficher un vecteur d'entiers
void afficher_vecteur(int idx1, const vector<int> &vecteur)
{
    for (int i = idx1; i < static_cast<int>(vecteur.size()); ++i)
    {
        cout << vecteur[i] << " ";
    }
    cout << "\n";

    EMPREINTE.clear();
    TEXTE.clear();
}

// Fonction pour générer une nouvelle chaine
uint64_t nouvelle_chaine(uint64_t idx1, int largeur)
{
    uint64_t idx2 = idx1;
    for (int i = 0; i < largeur - 1; i++)
    {
        idx2 = i2i(idx2, i + 1);
    }
    return idx2;
}

// Fonction pour afficher la chaine résultante
/* void afficher_chaine(int idx1, int largeur)
{
    vector<int> result = nouvelle_chaine(idx1, largeur);
    cout << "Chaine de longueur " << largeur << ": ";
    afficher_vecteur(idx1, result);
} */

int test_nouvelle_chaine()
{
    updateGlobalConfigN();
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "N : " << globalConfig.N << "\n";

    cout << "Test de la fonction nouvelle_chaine : \n";
    calculateN();

    cout << "i2c(1234) = " << i2c(globalConfig.taille, 1234) << endl;
    cout << "i2c(" << globalConfig.N - 1 << ") = " << i2c(globalConfig.taille, globalConfig.N - 1) << endl;

    uint64_t n1 = nouvelle_chaine(1, 1);
    uint64_t n2 = nouvelle_chaine(1, 10);
    uint64_t n3 = nouvelle_chaine(1, 100);
    uint64_t n4 = nouvelle_chaine(1, 1000);

    cout << "nouvelle_chaine(1, 1) = " << dec << n1 << endl;
    cout << "nouvelle_chaine(1, 10) = " << dec << n2 << endl;
    cout << "nouvelle_chaine(1, 100) = " << dec << n3 << endl;
    cout << "nouvelle_chaine(1, 1000) = " << dec << n4 << endl;

    /*  afficher_chaine(1, 1);
     afficher_chaine(1, 10);
     afficher_chaine(1, 100);
     afficher_chaine(1, 1000); */

    return 1;
}
// QUESTION 7 END

// QUESTION 9 START

int index_aleatoire()
{
    uint64_t random = rand();
    random = random << 32;
    random = random | rand();
    random = random % globalConfig.N;
    return random;
}

// Fonction pour créer la table arc-en-ciel
vector<pair<uint64_t, uint64_t>> creer_table(int largeur, int hauteur)
{
    vector<pair<uint64_t, uint64_t>> table;

    // Générer les chaînes suivantes

    uint64_t idx1 = 0;
    for (int i = 0; i < hauteur; ++i)
    {
        uint64_t idx1 = globalConfig.generateTableRandom ? index_aleatoire() : i;

        uint64_t result = nouvelle_chaine(idx1, largeur);
        table.push_back(make_pair(idx1, result));
    }

    // Trier la table par ordre croissant de la dernière colonne (les indices)
    sort(
        table.begin(),
        table.end(),
        [](const pair<int, int> &a, const pair<int, int> &b)
        { return a.second < b.second; });

    return table;
}

int test_create_table()
{
    updateGlobalConfigN();

    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Alphabet length : " << globalConfig.alphabet.size() << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "Nb clear texts : " << globalConfig.N << "\n";
    cout << "Height : " << globalConfig.height << "\n";
    cout << "Widht : " << globalConfig.width << "\n";

    srand(time(nullptr));
    vector<pair<uint64_t, uint64_t>> table = creer_table(globalConfig.width, globalConfig.height);
    cout << "Content:\n";
    for (const auto &entry : table)
    {
        cout << entry.first << ": --> " << entry.second << endl;
    }
    return 0;
}

// QUESTION 9 END

// QUESTION 10 START

// Fonction pour sauvegarder une table dans un fichier
void sauve_table(const string &filename, const vector<pair<uint64_t, uint64_t>> &table)
{
    // write table in file filename
    ofstream file(filename);

    // Vérifier si le fichier est ouvert avec succès
    if (!file.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier pour écriture." << endl;
        return;
    }

    // Écrire les paramètres de la table dans le fichier
    file << "Hash function: SHA1\n";
    file << "Alphabet:" << globalConfig.alphabet << "\n";
    file << "Alphabet length:" << globalConfig.alphabet.size() << "\n";
    file << "Size:" << globalConfig.taille << "\n";
    file << "Width:" << globalConfig.width << "\n";
    file << "Height:" << globalConfig.height << "\n";
    file << "Nb clear texts:" << globalConfig.N << "\n";
    file << "Content:\n";

    // Écrire les données de la table dans le fichier
    for (const auto &entry : table)
    {
        file << entry.first << " " << entry.second << "\n";
    }

    // Fermer le fichier
    file.close();
}

// Fonction pour ouvrir une table depuis un fichier
void ouvre_table(const string &filename, vector<pair<uint64_t, uint64_t>> &table)
{
    // read table from file filename
    ifstream file(filename);

    // Vérifier si le fichier est ouvert avec succès
    if (!file.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier pour lecture." << endl;
        return;
    }

    // Lire les paramètres de la table depuis le fichier
    string uselessline;
    string alphabet_length;
    string taille;
    string width;
    string height;
    string N;

    getline(file, uselessline);
    getline(file, globalConfig.alphabet);
    getline(file, alphabet_length);
    getline(file, taille);
    getline(file, width);
    getline(file, height);
    getline(file, N);

    // On extrait la valeur après les deux-points (:) dans le cas où vous voulez la récupérer
    size_t colonPos = globalConfig.alphabet.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.alphabet = globalConfig.alphabet.substr(colonPos + 1);
    }

    colonPos = alphabet_length.find(":");
    if (colonPos != string::npos)
    {
    }

    colonPos = taille.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.taille = stoi(taille.substr(colonPos + 1));
    }

    colonPos = width.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.width = stoi(width.substr(colonPos + 1));
    }

    colonPos = height.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.height = stoi(height.substr(colonPos + 1));
    }

    colonPos = N.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.N = stoi(N.substr(colonPos + 1));
    }

    // Content: is the empty line
    string emptyLine;
    getline(file, emptyLine);

    table.clear();
    std::vector<std::pair<uint64_t, uint64_t>> numberPairs;

    std::string line;
    uint64_t index, value;
    while (file >> index >> value)
    {
        table.emplace_back(index, value);
    }

    // Fermer le fichier
    file.close();
}

void affiche_table(const vector<pair<uint64_t, uint64_t>> &table)
{
    // Afficher les paramètres de la table
    cout << "hash function: SHA1" << endl;
    cout << "Alphabet: " << globalConfig.alphabet << endl;
    cout << "Alphabet length: " << globalConfig.alphabet.size() << endl;
    cout << "Size: " << globalConfig.taille << endl;
    cout << "Width: " << globalConfig.width << endl;
    cout << "Height: " << globalConfig.height << endl;
    cout << "Nb clear texts: " << globalConfig.N << endl;
    cout << "Content:" << endl;

    // Afficher les données de la table
    for (const auto &entry : table)
    {
        cout << entry.first << " --> " << entry.second << endl;
    }
}

int test_save_open_affiche_table()
{
    updateGlobalConfigN();

    cout << "AVANT CREATION TABLE" << endl;
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Alphabet length : " << globalConfig.alphabet.size() << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "Nb clear texts : " << globalConfig.N << "\n";
    cout << "Height : " << globalConfig.height << "\n";
    cout << "Widht : " << globalConfig.width << "\n";

    srand(time(nullptr));
    vector<pair<uint64_t, uint64_t>> table = creer_table(globalConfig.width, globalConfig.height);
    cout << endl;
    sauve_table("table.txt", table);
    cout << endl;
    ouvre_table("table.txt", table);
    cout << endl;
    cout << "APRES CREATION TABLE" << endl;
    // affiche_table(table);

    // print table
    cout << "test affiche table" << endl;
    for (const auto &entry : table)
    {
        cout << entry.first << ": --> " << entry.second << endl;
    }
    return 0;
}

// QUESTION 10 END

// QUESTION 11 START

int recherche(vector<pair<uint64_t, uint64_t>> table, int hauteur, uint64_t idx, int *a, int *b)
{
    int i = 0;
    int j = hauteur - 1;
    while (i <= j)
    {
        int m = (i + j) / 2;
        if (table[m].second == idx)
        {

            *a = m;
            *b = m;
            while (*a > 0 && table[*a - 1].second == idx)
            {
                (*a)--;
            }

            while (*b < hauteur - 1 && table[*b + 1].second == idx)
            {
                (*b)++;
            }

            return *b - *a + 1;
        }
        else if (table[m].second < idx)
        {
            i = m + 1;
        }
        else
        {
            j = m - 1;
        }
    }
    return 0;
}

int test_recherche()
{
    updateGlobalConfigN();
    vector<pair<uint64_t, uint64_t>> table;
    ouvre_table("table.txt", table);
    cout << endl;
    cout << "test recherche" << endl;
    int a, b;
    recherche(table, globalConfig.height, 1651094, &a, &b);
    cout << a << " " << b << endl;

    return 0;
}

bool verifyHash(const unsigned char *data, const unsigned char *storedHash)
{
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        if (data[i] != storedHash[i])
        {
            return false;
        }
    }
    return true;
}

int testVerifyHash()
{
    const char *data = "CODE";
    unsigned char storedHash[SHA_DIGEST_LENGTH];

    // Calculer le hash pour les données de test
    SHA1((const unsigned char *)data, strlen(data), storedHash);

    cout << endl;
    // Tester la fonction verifyHash
    if (verifyHash((const unsigned char *)data, storedHash))
    {
        cout << endl;
        std::cout << "Le hash est correct. Les données n'ont pas été altérées.\n";
        return 0; // Succès
    }
    else
    {
        std::cerr << "Le hash ne correspond pas. Les données ont été altérées.\n";
        return 1; // Échec
    }
}

int verifie_candidat(const unsigned char *h, int t, uint64_t idx, std::string &clair)
{
    for (int i = 1; i < t; i++)
    {
        idx = i2i(idx, i);
    }
    clair = i2c(globalConfig.taille, idx);
    unsigned char h2[SHA_DIGEST_LENGTH];
    calculateHash(clair.c_str(), h2);
    if (verifyHash(h2, h) == 1)
    {
        return 1;
    }

    return 0;
}

uint64_t inverse(vector<pair<uint64_t, uint64_t>> &table, const unsigned char *h, std::string &clair, int largeur, int hauteur)
{
    for (int t = largeur - 1; t > 0; t--)
    {
        uint64_t idx = h2i(h, t, globalConfig.N);

        for (int i = t + 1; i < largeur; i++)
        {
            idx = i2i(idx, i);
        }

        int a, b;
        if (recherche(table, hauteur, idx, &a, &b) > 0)
        {
            for (int i = a; i <= b; i++)
            {
                if (verifie_candidat(h, t, table[i].first, clair) == 1)
                {
                    cout << endl
                         << "Résultat : " << clair << endl;
                    return 1;
                }
            }
        }
    }
    std::cout << "Rien trouvé" << std::endl;
    return 0;
}

int test_crack()
{
    updateGlobalConfigN();
    vector<pair<uint64_t, uint64_t>> table;
    ouvre_table("table.txt", table);

    cout << endl;

    if (globalConfig.hash.empty())
    {
        cout << "test inverse for word CODE" << endl;

        std::string clair;
        unsigned char hash[SHA_DIGEST_LENGTH];
        calculateHash("CODE", hash);

        cout << "hash = ";
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            cout << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        cout << endl;
        inverse(table, hash, clair, globalConfig.width, globalConfig.height);
    }
    else
    {
        cout << "test inverse for hash " << globalConfig.hash << endl;

        std::string clair;
        unsigned char hash[SHA_DIGEST_LENGTH];
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            hash[i] = hexToDecimal(globalConfig.hash.substr(i * 2, 2));
        }

        cout << "hash = ";
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            cout << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        cout << endl;
        inverse(table, hash, clair, globalConfig.width, globalConfig.height);
    }

    return 0;
}

// QUESTION 11 END

// QUESTION 13 START
double stats()
{
    double m = globalConfig.height;
    double v = 1.0;
    for (int i = 0; i < globalConfig.width; i++)
    {
        v = v * (1 - m / globalConfig.N);
        m = (double)globalConfig.N * (1 - exp(-m / globalConfig.N));
    }
    return 100 * (1 - v);
}

int test_stats()
{
    updateGlobalConfigN();
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Alphabet length : " << globalConfig.alphabet.size() << "\n";
    cout << "Height : " << globalConfig.height << "\n";
    cout << "Width : " << globalConfig.width << "\n";

    cout << "Test de la fonction stats : \n";
    cout << "stats = " << stats() << " %" << std::endl;

    return 1;
}

// QUESTION 13 END

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
    else if (std::strcmp("h2i", test) == 0)
    {
        return test_h2i();
    }
    else if (std::strcmp("nouvelle_chaine", test) == 0)
    {
        return test_nouvelle_chaine();
    }
    else if (std::strcmp("create_table", test) == 0)
    {
        return test_create_table();
    }
    else if (std::strcmp("save_table", test) == 0)
    {
        return test_save_open_affiche_table();
    }
    else if (std::strcmp("recherche_table", test) == 0)
    {
        return test_recherche();
    }
    else if (std::strcmp("verify_hash", test) == 0)
    {
        return testVerifyHash();
    }
    else if (std::strcmp("crack", test) == 0)
    {
        return test_crack();
    }
    else if (std::strcmp("stats", test) == 0)
    {
        return test_stats();
    }
    else
    {
        std::cout << "unknown test\n";
        return 1;
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
            globalConfig.alphabet_length = globalConfig.alphabet.size();
        }

        if (strncmp(arg, "--size=", 7) == 0)
        {
            globalConfig.taille = atoi(arg + 7);
        }

        if (strncmp(arg, "--width=", 8) == 0)
        {
            globalConfig.width = atoi(arg + 8);
        }
        if (strncmp(arg, "--height=", 9) == 0)
        {
            globalConfig.height = atoi(arg + 9);
        }

        if (strncmp(arg, "--randTable", 11) == 0)
        {
            globalConfig.generateTableRandom = true;
        }

        if (strncmp(arg, "--hash=", 7) == 0)
        {
            globalConfig.hash = arg + 7;
        }
    }
}