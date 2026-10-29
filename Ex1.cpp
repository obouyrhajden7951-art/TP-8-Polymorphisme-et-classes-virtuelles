/*
 * Ex1.cpp
 *
 *  Created on: 29 oct. 2026
 *      Author: hP
 */
#include <iostream>
#include <string>
using namespace std;

// Classe abstraite
class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;
    virtual ~SortieAudio() {
        cout << "Destructeur de SortieAudio" << endl;
    }
};

class HautParleur : public SortieAudio {
public:
    void ouvrir() {
        cout << "Le haut-parleur est allume" << endl;
    }
    void jouer(const string& son) {
        cout << "Haut-parleur joue : " << son << endl;
    }
    void fermer() {
        cout << "Le haut-parleur est eteint" << endl;
    }
    ~HautParleur() {
        cout << "Destructeur de HautParleur" << endl;
    }
};

class CasqueBT : public SortieAudio {
public:
    void ouvrir() {
        cout << "Connexion Bluetooth du casque..." << endl;
    }
    void jouer(const string& son) {
        cout << "Casque BT joue : " << son << endl;
    }
    void fermer() {
        cout << "Casque BT deconnecte" << endl;
    }
    ~CasqueBT() {
        cout << "Destructeur de CasqueBT" << endl;
    }
};

class SortieHDMI : public SortieAudio {
public:
    void ouvrir() {
        cout << "Connexion HDMI etablie" << endl;
    }
    void jouer(const string& son) {
        cout << "HDMI joue : " << son << endl;
    }
    void fermer() {
        cout << "Connexion HDMI fermee" << endl;
    }
    ~SortieHDMI() {
        cout << "Destructeur de SortieHDMI" << endl;
    }
};

// Fonction qui teste n'importe quelle sortie audio
void tester(SortieAudio* s) {
    s->ouvrir();
    s->jouer("musique.mp3");
    s->fermer();
    cout << "----------------------" << endl;
}

int main() {
    SortieAudio* tab[3];

    tab[0] = new HautParleur();
    tab[1] = new CasqueBT();
    tab[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        tester(tab[i]);
    }

    // liberation de la memoire
    for (int i = 0; i < 3; i++) {
        delete tab[i];
    }

    return 0;
}

