#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

struct Vec3 {
    float x;
    float y;
    float z;
};

// fonctions utiles pour les vecteurs
float norme(Vec3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float produitScalaire(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float distance(Vec3 a, Vec3 b) {
    Vec3 d = {a.x - b.x, a.y - b.y, a.z - b.z};
    return norme(d);
}

// Classe abstraite
class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;
    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    Vec3 couleur;
public:
    LumiereDirectionnelle(Vec3 d, Vec3 c) {
        direction = d;
        couleur = c;
    }
    float intensite(const Vec3& position) {
        // l'intensite ne depend pas de la position
        return (couleur.x + couleur.y + couleur.z) / 3;
    }
};

class LumierePonctuelle : public Lumiere {
private:
    Vec3 position;
    float attenuation;
public:
    LumierePonctuelle(Vec3 p, float a) {
        position = p;
        attenuation = a;
    }
    float intensite(const Vec3& point) {
        float d = distance(position, point);
        return 1 / (1 + attenuation * d * d);
    }
};

class LumiereSpot : public Lumiere {
private:
    Vec3 position;
    Vec3 direction;
    float angle; // angle d'ouverture en degres
public:
    LumiereSpot(Vec3 p, Vec3 d, float a) {
        position = p;
        direction = d;
        angle = a;
    }
    float intensite(const Vec3& point) {
        Vec3 v = {point.x - position.x, point.y - position.y, point.z - position.z};
        float d = norme(v);
        if (d == 0) {
            return 1;
        }
        // cosinus de l'angle entre la direction du spot et le point
        float cosA = produitScalaire(v, direction) / (d * norme(direction));
        float angleRad = (angle / 2) * 3.14159 / 180;

        if (cosA < cos(angleRad)) {
            return 0; // le point est hors du cone
        }
        return 1 / (1 + d * d);
    }
};

// vecteur global de lumieres
vector<unique_ptr<Lumiere>> lumieres;

float calculerEclairage(const Vec3& point) {
    float somme = 0;
    for (int i = 0; i < lumieres.size(); i++) {
        somme = somme + lumieres[i]->intensite(point);
    }
    return somme;
}

int main() {
    lumieres.push_back(make_unique<LumiereDirectionnelle>(Vec3{0, -1, 0}, Vec3{0.8, 0.8, 0.8}));
    lumieres.push_back(make_unique<LumierePonctuelle>(Vec3{0, 5, 0}, 0.1));
    lumieres.push_back(make_unique<LumiereSpot>(Vec3{0, 10, 0}, Vec3{0, -1, 0}, 40));

    Vec3 p1 = {0, 0, 0};
    Vec3 p2 = {3, 0, 0};
    Vec3 p3 = {10, 0, 10};

    cout << "Eclairage au point 1 : " << calculerEclairage(p1) << endl;
    cout << "Eclairage au point 2 : " << calculerEclairage(p2) << endl;
    cout << "Eclairage au point 3 : " << calculerEclairage(p3) << endl;

    return 0;
}
