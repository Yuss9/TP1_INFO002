#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
#include <cmath>
#include <sstream>
#include <cstring>
#include <vector>

#include <fstream>
#include <string>
using namespace std;

struct Config
{
    string alphabet;
    int taille;
    int N;
    int alphabet_length;
    int height;
    int width;
};

Config globalConfig; // Variable globale pour stocker la configuration

vector<string> EMPREINTE;
vector<string> TEXTE;

// HELP FUNCTION START

void updateGlobalConfigN()
{
    if (globalConfig.alphabet.empty() || globalConfig.taille <= 0)
    {
        cerr << "Configuration invalide : alphabet vide ou taille non positive\n";
        exit(1);
    }

    int alphabetSize = globalConfig.alphabet.size();
    globalConfig.N = static_cast<int>(pow(alphabetSize, globalConfig.taille));
}

// HELP FUNCTION END

// QUESTION 1 START
void calculateHash(const char *input, unsigned char *output)
{
    // add 0 to input
    std::stringstream ss;
    ss << input << "\0";
    input = ss.str().c_str();
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
    cout << "  h2i  : test function h2i, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test h2i \n";
    cout << "  nouvelle_chaine  : test function nouvelle_chaine, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test nouvelle_chaine \n";
    cout << "  create_table  : test function create_table, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=5 --height=100 --width=200 test create_table \n";
    cout << "  save_table  : test function save open and affiche table, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=5 --height=100 --width=200 test save_table \n";
    cout << "  recherche_table  : test function recherche table, you need to give alphabet and size before ex : \n ./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=5 --height=100 --width=200 test recherche_table \n";
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
        result = alphabet.find('A') != std::string::npos ? 'A' + result : 'a' + result;
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

// QUESTION 6 START
uint64_t h2i(const unsigned char *hash, size_t t, int N)
{
    return (*((uint64_t *)hash) + t) % N;
}

int test_h2i()
{
    updateGlobalConfigN();
    const char *texte = "oups";
    unsigned char hash_result[20];

    cout << "alphabet = \"" << globalConfig.alphabet << "\"" << endl;
    cout << "taille = " << globalConfig.taille << endl;
    cout << "N = " << globalConfig.N << endl;
    unsigned char hash[SHA_DIGEST_LENGTH];

    calculateHash(texte, hash);

    cout << "hash(\"" << texte << "\") = ";
    for (int k = 0; k < SHA_DIGEST_LENGTH; k++)
    {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(hash[k]);
    }

    cout << "\n";

    int t = 1;
    uint64_t result = h2i(hash, t, globalConfig.N);
    cout << dec << "h2i(hash(\"" << texte << "\"), " << t << ") = " << result << endl;

    return 0;
}

// QUESTION 6 END

// QUESTION 7 START

// Fonction pour transformer un indice en chaîne résultante
uint64_t i2i(int t, int n)
{
    const char *value = i2c(globalConfig.alphabet, globalConfig.taille, n).c_str();
    TEXTE.push_back(value);

    unsigned char hash[SHA_DIGEST_LENGTH];
    calculateHash(value, hash);
    EMPREINTE.push_back((const char *)hash);

    return h2i((const unsigned char *)(hash), t, globalConfig.N);
}

// Fonction pour afficher un vecteur d'entiers
void afficher_vecteur(int idx1, const vector<int> &vecteur)
{
    for (int i = idx1; i < vecteur.size(); ++i)
    {
        cout << vecteur[i] << " ";
    }
    cout << "\n";

    EMPREINTE.clear();
    TEXTE.clear();
}

// Fonction pour générer une nouvelle chaine
vector<int> nouvelle_chaine(int idx1, int largeur)
{
    vector<int> result;
    int n = idx1;
    for (int i = 0; i < largeur - 1; ++i)
    {
        n = i2i(i + 1, n);
        result.push_back(n);
    }

    return result;
}

// Fonction pour afficher la chaine résultante
void afficher_chaine(int idx1, int largeur)
{
    vector<int> result = nouvelle_chaine(idx1, largeur);
    cout << "Chaine de longueur " << largeur << ": ";
    afficher_vecteur(idx1, result);
}

int test_nouvelle_chaine()
{
    updateGlobalConfigN();
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "N : " << globalConfig.N << "\n";

    cout << "Test de la fonction nouvelle_chaine : \n";
    calculateN();

    cout << "i2c(1234) = " << i2c(globalConfig.alphabet, globalConfig.taille, 1234) << endl;
    cout << "i2c(" << globalConfig.N - 1 << ") = " << i2c(globalConfig.alphabet, globalConfig.taille, globalConfig.N - 1) << endl;

    afficher_chaine(1, 1);
    afficher_chaine(1, 10);
    afficher_chaine(1, 100);
    afficher_chaine(1, 1000);

    return 1;
}
// QUESTION 7 END

// QUESTION 9 START

int index_aleatoire(int hauteur)
{
    // Le modulo permet de s'assurer que l'indice est dans la plage de la hauteur de la table
    return rand() % hauteur;
}

// Fonction pour créer la table arc-en-ciel
vector<pair<int, int>> creer_table(int largeur, int hauteur)
{
    vector<pair<int, int>> table;

    // Générer les chaînes suivantes

    for (int i = 0; i < hauteur; ++i)
    {
        int idx1 = index_aleatoire(hauteur);
        // int idx1 = i; // pour vous monsieur pour tester
        vector<int> chaine = nouvelle_chaine(idx1, largeur);
        table.push_back(make_pair(i, chaine.back()));
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
    cout << "Alphabet length : " << globalConfig.alphabet_length << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "Nb clear texts : " << globalConfig.N << "\n";
    cout << "Height : " << globalConfig.height << "\n";
    cout << "Widht : " << globalConfig.width << "\n";

    srand(time(nullptr));
    vector<pair<int, int>> table = creer_table(globalConfig.width, globalConfig.height);
    cout << "Content:\n";
    for (const auto &entry : table)
    {
        cout << setw(9) << entry.first << ": --> " << entry.second << endl;
    }
    return 0;
}

// QUESTION 9 END

// QUESTION 10 START

// Fonction pour sauvegarder une table dans un fichier
void sauve_table(const string &filename, const vector<pair<int, int>> &table)
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
    file << "Alphabet: " << globalConfig.alphabet << "\n";
    file << "Alphabet length: " << globalConfig.alphabet_length << "\n";
    file << "Size: " << globalConfig.taille << "\n";
    file << "Width: " << globalConfig.width << "\n";
    file << "Height: " << globalConfig.height << "\n";
    file << "Nb clear texts: " << globalConfig.N << "\n";
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
void ouvre_table(const string &filename, vector<pair<int, int>> &table)
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
        globalConfig.alphabet_length = stoi(alphabet_length.substr(colonPos + 2));
    }

    colonPos = taille.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.taille = stoi(taille.substr(colonPos + 2));
    }

    colonPos = width.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.width = stoi(width.substr(colonPos + 2));
    }

    colonPos = height.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.height = stoi(height.substr(colonPos + 2));
    }

    colonPos = N.find(":");
    if (colonPos != string::npos)
    {
        globalConfig.N = stoi(N.substr(colonPos + 2));
    }

    // Content: is the empty line
    string emptyLine;
    getline(file, emptyLine);

    table.clear();
    std::vector<std::pair<int, int>> numberPairs;
    int number1, number2;

    std::string line;
    int index, value;
    while (file >> index >> value)
    {
        table.emplace_back(index, value);
    }

    // Fermer le fichier
    file.close();
}

void affiche_table(const vector<pair<int, int>> &table)
{
    // Afficher les paramètres de la table
    cout << "hash function: SHA1" << endl;
    cout << "Alphabet: " << globalConfig.alphabet << endl;
    cout << "Alphabet length: " << globalConfig.alphabet_length << endl;
    cout << "Size: " << globalConfig.taille << endl;
    cout << "Width: " << globalConfig.width << endl;
    cout << "Height: " << globalConfig.height << endl;
    cout << "Nb clear texts: " << globalConfig.N << endl;
    cout << "Content:" << endl;

    // Afficher les données de la table
    for (const auto &entry : table)
    {
        cout << setw(9) << entry.first << " --> " << entry.second << endl;
    }
}

int test_save_open_affiche_table()
{
    updateGlobalConfigN();

    cout << "AVANT CREATION TABLE" << endl;
    cout << "Affichage de la config : \n";
    cout << "Alphabet : " << globalConfig.alphabet << "\n";
    cout << "Alphabet length : " << globalConfig.alphabet_length << "\n";
    cout << "Taille : " << globalConfig.taille << "\n";
    cout << "Nb clear texts : " << globalConfig.N << "\n";
    cout << "Height : " << globalConfig.height << "\n";
    cout << "Widht : " << globalConfig.width << "\n";

    srand(time(nullptr));
    vector<pair<int, int>> table = creer_table(globalConfig.width, globalConfig.height);
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
        cout << setw(9) << entry.first << ": --> " << entry.second << endl;
    }
}

// QUESTION 10 END

// QUESTION 11 START

int recherche(vector<pair<int, int>> table, int hauteur, int idx, int *a, int *b)
{
    int i = 0;
    int j = hauteur - 1;
    while (i <= j)
    {
        int m = (i + j) / 2;
        if (table[m].second == idx)
        {
            // On cherche après
            int maxInclusif = m;
            while (maxInclusif < hauteur - 1 && table[maxInclusif + 1].second == idx)
            {
                maxInclusif++;
            }

            // On cherche avant
            int minInclusif = m;
            while (0 < minInclusif && table[minInclusif - 1].second == idx)
            {
                minInclusif--;
            }

            *a = minInclusif;
            *b = maxInclusif;

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
    vector<pair<int, int>> table;
    ouvre_table("table.txt", table);
    cout << endl;
    cout << "test recherche" << endl;
    int a, b;
    recherche(table, globalConfig.height, 11797675, &a, &b);
    cout << a << " " << b << endl;
}

// QUESTION 11 END

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
        }

        if (strncmp(arg, "--size=", 7) == 0)
        {
            globalConfig.taille = atoi(arg + 7);
        }

        if (strncmp(arg, "--alphabet_length=", 18) == 0)
        {
            globalConfig.alphabet_length = atoi(arg + 18);
        }

        if (strncmp(arg, "--width=", 8) == 0)
        {
            globalConfig.width = atoi(arg + 8);
        }
        if (strncmp(arg, "--height=", 9) == 0)
        {
            globalConfig.height = atoi(arg + 9);
        }
    }
}