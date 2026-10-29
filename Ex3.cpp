/*
 * Ex3.cpp
 *
 *  Created on: 29 oct. 2026
 *      Author: hP
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// fonction pour remplacer un mot par un autre dans un texte
string remplacer(string texte, string ancien, string nouveau) {
    int pos = texte.find(ancien);
    while (pos != string::npos) {
        texte.replace(pos, ancien.length(), nouveau);
        pos = texte.find(ancien, pos + nouveau.length());
    }
    return texte;
}

// Classe abstraite
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;
    virtual ~Plugin() {}

    // factory
    static Plugin* creerPlugin(const string& type);
};

class CorrecteurOrthographique : public Plugin {
public:
    string nom() const {
        return "Correcteur orthographique";
    }
    string traiter(const string& texte) {
        string res = texte;
        res = remplacer(res, "bonjoure", "bonjour");
        res = remplacer(res, "beacoup", "beaucoup");
        res = remplacer(res, "maisson", "maison");
        res = remplacer(res, "seulment", "seulement");
        return res;
    }
};

class TraducteurAnglais : public Plugin {
public:
    string nom() const {
        return "Traducteur anglais";
    }
    string traiter(const string& texte) {
        string res = texte;
        res = remplacer(res, "bonjour", "hello");
        res = remplacer(res, "monde", "world");
        res = remplacer(res, "merci", "thank you");
        res = remplacer(res, "maison", "house");
        res = remplacer(res, "chat", "cat");
        return res;
    }
};

class AnalyseurStyle : public Plugin {
public:
    string nom() const {
        return "Analyseur de style";
    }
    string traiter(const string& texte) {
        int nbMots = 0;
        int phrasesLongues = 0;

        for (int i = 0; i < texte.length(); i++) {
            char c = texte[i];

            // un mot commence apres un espace (ou au debut)
            if (c != ' ' && (i == 0 || texte[i - 1] == ' ')) {
                nbMots++;
            }
            // fin de phrase
            if (c == '.' || c == '!' || c == '?') {
                if (nbMots > 15) {
                    phrasesLongues++;
                }
                nbMots = 0;
            }
        }
        if (nbMots > 15) {
            phrasesLongues++;
        }

        string message = "\n[Analyse] Phrases trop longues : " + to_string(phrasesLongues);
        return texte + message;
    }
};

// definition de la factory (apres les classes derivees)
Plugin* Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return new CorrecteurOrthographique();
    }
    else if (type == "traducteur") {
        return new TraducteurAnglais();
    }
    else if (type == "analyseur") {
        return new AnalyseurStyle();
    }
    return NULL;
}

int main() {
    vector<Plugin*> plugins;

    // simulation du chargement des plugins
    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("analyseur"));

    string texte;
    cout << "Entrez un texte : ";
    getline(cin, texte);

    for (int i = 0; i < plugins.size(); i++) {
        texte = plugins[i]->traiter(texte);
        cout << "\nPlugin applique : " << plugins[i]->nom() << endl;
        cout << "Texte : " << texte << endl;
    }

    // liberation de la memoire
    for (int i = 0; i < plugins.size(); i++) {
        delete plugins[i];
    }

    return 0;
}


