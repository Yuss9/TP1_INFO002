#!/bin/bash

# GITHUB 
echo "LIENS GITHUB : "
echo "https://github.com/Yuss9/TP1_INFO002"

# AIDE
echo "AIDE"
make
./main --help
echo ""

# QUESTIONS 1
echo "QUESTIONS 1"
./main test hash Salut Bob
echo ""

# QUESTIONS 2
echo "QUESTIONS 2"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test calculateN
echo ""

# QUESTIONS 4
echo "QUESTIONS 4"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test i2c
echo ""

# QUESTIONS 6
echo "QUESTIONS 6"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test h2i
echo ""

# QUESTIONS 7
echo "QUESTIONS 7"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test nouvelle_chaine
echo ""

# QUESTIONS 9
echo "QUESTIONS 9"
echo "En mode random :"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --randTable --size=5 --height=100 --width=200 test create_table
echo "En mode test prof :"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test create_table
echo ""

# QUESTIONS 10
echo "QUESTIONS 10"
echo "En mode random :"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --randTable --size=5 --height=100 --width=200 test save_table
echo "En mode test prof :"
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test save_table
echo ""

# QUESTIONS 11
echo "QUESTIONS 11"
echo "On ajoute dans un premier temps le fichier table.txt avec le tableau à l'intérieur"
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=3000 test save_table
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --size=4 --height=1000 --width=3000 test crack
echo ""

# Question 13
echo "Question 13"
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=1000 test stats
echo ""

# PARTIE 1 QUESTION 14
echo "PARTIE 1 QUESTION 14"
echo "Pour la partie 2 voir le README"
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=3000 test save_table
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --size=4 --height=1000 --width=3000 test crack
echo ""
echo "Fin du test.sh, Pour la partie 2 voir le README"