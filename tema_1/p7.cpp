#include <iostream>
#include <cstdarg>
#include <math.h>
#include <chrono>
#include <thread>
using namespace std::literals::chrono_literals;

class Polinom
{
private:
    int degree;
    int *coefficients;

public:
    explicit Polinom(int degree_ = 0, ...);
    Polinom(Polinom const &rhs);
    ~Polinom();

    Polinom operator+(const Polinom &obj);
    Polinom operator-(const Polinom &obj);
    Polinom operator*(const Polinom &obj);
    Polinom &operator=(const Polinom &obj);
    bool operator==(const Polinom &obj) const;
    bool operator!=(const Polinom &obj) const;

    friend std::ostream &operator<<(std::ostream &os, const Polinom &obj);
    friend std::istream &operator>>(std::istream &is, Polinom &obj);

    void setDegree(int degree_);
    void setCoefficients(int const coefficients_[]);
    int getDegree();
    const int *getCoefficients() const;
    // void setCoefficients(int fake_degree, ...);  Vezi linia ...

    int value_for(int x);
};

void meniuInteractiv()
{
    std::cout << "Exemplu:     p[1] = 2 4 2 1\n"
              << "                    ||_____|\n"
              << "gradul polinomului <┘   └> lista coeficientilor(de la a_0 la a_n)\n\n";

    int n = 0, nrPolinoame = 0;
    std::cout << "Introduceti numarul maxim de polinoame care va fi folosit in cadrul acestui program: ";
    std::cin >> n;

    Polinom *polinoame = new Polinom[n];

    char command = '0';
    bool status = true;
    while (status == true)
    {
        std::cout << "\nIntroduceti cifra corespunzatoare grupului de comenzi dorit:\n"
                  << "  1.Crearea, citirea, afisarea si copierea polinoamelor\n"
                  << "  2.Operatii aritmetice cu polinoame\n"
                  << "  3.Verificara egalitatii a doua polinoame\n"
                  << "  (Introduceti orice alt caracter pentru a incheia executarea programului)\n\n";
        std::cin >> command;
        switch (command)
        {
        case '1':
        {
            bool localStatus = true;
            while (localStatus == true)
            {
                std::this_thread::sleep_for(600ms);
                std::cout << "\n    Introduceti cifra corespunzatoare comenzii dorite:\n"
                          << "      1.Introduceti un polinom de la tastatura\n"
                          << "      2.Introduceti n polinoame de la tastatura\n"
                          << "      3.Setati gradul unui polinom\n"
                          << "      4.Setati coeficientii unui polinom\n"
                          << "      5.Copiati un polinom\n"
                          << "      6.Afisati un polinom\n"
                          << "      7.Afisati gradul unui polinom\n"
                          << "      8.Afisati coefficientii unui polinom\n"
                          << "      9.Afisati toate polinoamele\n"
                          << "      (Introduceti orice alt caracter pentru a merge la meniul initial)\n\n";
                std::cin >> command;
                std::cout << std::endl;

                switch (command)
                {
                case '1':
                    std::cout << "p[" << nrPolinoame << "] = ";
                    std::cin >> polinoame[nrPolinoame++];
                    break;

                case '2':
                    int nr;
                    std::cout << "Cate polinoame doriti sa introduceti? ";
                    std::cin >> nr;
                    for (int i = 0; i < nr; i++)
                    {
                        std::cout << "p[" << nrPolinoame << "] = ";
                        std::cin >> polinoame[nrPolinoame++];
                    }
                    break;

                case '3':
                {
                    int aux, auxDegree;
                    std::cout << "Selectati polinomul pe care doriti sa il alterati(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> aux;
                    std::cout << "Introduceti gradul dorit: ";
                    std::cin >> auxDegree;
                    polinoame[aux].setDegree(auxDegree);

                    if (aux == nrPolinoame)
                        nrPolinoame++;
                    break;
                }
                case '4':
                {
                    int aux;
                    std::cout << "Selectati polinomul pe care doriti sa il alterati(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> aux;

                    int auxDegree = polinoame[aux].getDegree();
                    int *auxCoefficients = new int[auxDegree + 1];
                    std::cout << "Introduceti coeficientii(" << auxDegree + 1 << "): ";
                    for (int i = 0; i <= auxDegree; i++)
                        std::cin >> auxCoefficients[i];
                    polinoame[aux].setCoefficients(auxCoefficients);

                    if (aux == nrPolinoame)
                        nrPolinoame++;
                    delete[] auxCoefficients;
                    break;
                }
                case '5':
                {
                    int source, destination;
                    std::cout << "Selectati sursa(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> source;
                    std::cout << "Selectati destinatia(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> destination;
                    polinoame[destination] = polinoame[source];
                    if (destination == nrPolinoame)
                        nrPolinoame++;
                    break;
                }
                case '6':
                {
                    int aux;
                    std::cout << "Selectati polinomul pe care doriti sa il afisati(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> aux;
                    std::cout << polinoame[aux];
                    break;
                }
                case '7':
                {
                    int aux;
                    std::cout << "Selectati polinomul de la care doriti sa afisati gradul(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> aux;
                    std::cout << polinoame[aux].getDegree();
                    break;
                }
                case '8':
                {
                    int aux;
                    std::cout << "Selectati polinomul de la care doriti sa afisati indicii(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> aux;
                    for (int i = 0; i <= polinoame[aux].getDegree(); i++)
                        std::cout << "a[" << i << "] = " << polinoame[aux].getCoefficients()[i] << std::endl;
                    std::cout << std::endl;
                    break;
                }
                case '9':
                {
                    for (int i = 0; i < nrPolinoame; i++)
                        std::cout << "p[" << i << "] = " << polinoame[i];
                    break;
                }
                default:
                    localStatus = false;
                    break;
                }
            }
            break;
        }
        case '2':
        {
            bool localStatus = true;
            while (localStatus == true)
            {
                std::this_thread::sleep_for(600ms);
                std::cout << "\n    Introduceti cifra corespunzatoare comenzii dorite:\n"
                          << "      1.Suma a doua polinoame\n"
                          << "      2.Diferenta a doua polinoame\n"
                          << "      3.Produsul a doua polinoame\n"
                          << "      4.Valoarea unui polinom intr-un anumit punct\n"
                          << "      (Introduceti orice alt caracter pentru a merge la meniul initial)\n\n";
                std::cin >> command;
                std::cout << std::endl;

                switch (command)
                {

                case '1':
                {
                    int destination, source1, source2;
                    std::cout << "Selectati destinatia(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> destination;
                    std::cout << "Selectati cei doi termeni(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> source1 >> source2;
                    if (destination == nrPolinoame)
                        nrPolinoame++;

                    polinoame[destination] = polinoame[source1] + polinoame[source2];
                    break;
                }
                case '2':
                {
                    int destination, source1, source2;
                    std::cout << "Selectati destinatia(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> destination;
                    std::cout << "Selectati cele descazutul si scazatorul(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> source1 >> source2;
                    if (destination == nrPolinoame)
                        nrPolinoame++;
                    polinoame[destination] = polinoame[source1] - polinoame[source2];
                    break;
                }
                case '3':
                {
                    int destination, source1, source2;
                    std::cout << "Selectati destinatia(de la 0 la " << nrPolinoame << "): ";
                    std::cin >> destination;
                    std::cout << "Selectati cei doi factori(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> source1 >> source2;
                    if (destination == nrPolinoame)
                        nrPolinoame++;
                    polinoame[destination] = polinoame[source1] * polinoame[source2];
                    break;
                }
                case '4':
                {
                    int aux, auxValue;
                    std::cout << "Selectati polinomul pentru care doriti sa calculati valoarea(de la 0 la " << nrPolinoame - 1 << "): ";
                    std::cin >> aux;
                    std::cout << "Selectati punctul in care doriti sa calculati valoarea: ";
                    std::cin >> auxValue;
                    std::cout << polinoame[aux].value_for(auxValue);
                    break;
                }
                default:
                    localStatus = false;
                    break;
                }
            }
            break;
        }
        case '3':
        {
            bool localStatus = true;
            while (localStatus == true)
            {
                std::this_thread::sleep_for(600ms);
                std::cout << "\n    Introduceti cifra corespunzatoare comenzii dorite:\n"
                          << "      1.Verificati daca polinoamele sunt egale\n"
                          << "      2.Verificati daca polinoamele sunt diferite\n"
                          << "      (Introduceti orice alt caracter pentru a merge la meniul initial)\n\n";
                std::cin >> command;
                std::cout << std::endl;

                if (command != '1' && command != '2')
                    break;

                int source1, source2;
                std::cout << "Selectati cele doua surse(de la 0 la " << nrPolinoame - 1 << "): ";
                std::cin >> source1 >> source2;
                switch (command)
                {
                case '1':
                {
                    if (polinoame[source1] == polinoame[source2])
                        std::cout << "Cele doua polinoame sunt egale!\n";
                    else
                        std::cout << "Cele doua polinoame nu sunt egale!\n";
                    break;
                }
                case '2':
                {
                    if (polinoame[source1] != polinoame[source2])
                        std::cout << "Cele doua polinoame sunt diferite!\n";
                    else
                        std::cout << "Cele doua polinoame nu sunt diferite!\n";
                    break;
                }
                default:
                    localStatus = false;
                    break;
                }
            }
            break;
        }
        default:
            status = false;
            break;
        }
    }
    delete[] polinoame;
}

int main()
{
    meniuInteractiv();
    return 0;
}

// Constructori si destructor
Polinom::Polinom(int degree_, ...)
{
    degree = degree_++;
    coefficients = new int[degree + 1]();
    va_list valist;
    va_start(valist, degree_);
    for (int i = 0; i <= degree; i++)
        coefficients[i] = va_arg(valist, int);
    va_end(valist);
}

Polinom::Polinom(Polinom const &rhs)
{
    degree = rhs.degree;
    coefficients = new int[degree + 1];
    for (int i = 0; i <= degree; i++)
        coefficients[i] = rhs.coefficients[i];
}

Polinom::~Polinom()
{
    delete[] coefficients;
}

// Getters si Setters
int Polinom::getDegree()
{
    return degree;
}

const int *Polinom::getCoefficients() const
{
    return coefficients;
}

void Polinom::setDegree(int degree_)
{
    degree = degree_;
    delete[] coefficients;
    coefficients = new int[degree + 1]();
}

void Polinom::setCoefficients(int const coefficients_[])
{
    for (int i = 0; i <= degree; i++)
        coefficients[i] = coefficients_[i];
}

/*Alternativa pentru a putea apela getter ul pentru coeficienti din cadrul programului*/
/*
void Polinom::setCoefficients(int fake_degree, ...) // Un mic artificiu pentru a evita "warning: second parameter of ‘va_start’ not last named argument [-Wvarargs]"
{                                                   // Codul functioneaza si fara fake_degree
    int coef_0 = fake_degree;                       // Ce probleme ar putea aparea?
    fake_degree = degree;
    va_list valist;
    va_start(valist, fake_degree);
    coefficients[0] = coef_0;
    for (int i = 1; i <= degree; i++)
        coefficients[i] = va_arg(valist, int);
}
*/

// Supraincarcarea operatorilor
Polinom Polinom::operator+(Polinom const &obj)
{
    int maxdegree = std::max(degree, obj.degree);
    Polinom temp(maxdegree);
    for (int i = 0; i <= maxdegree; i++)
    {
        int value1 = (i <= degree) ? coefficients[i] : 0;
        int value2 = (i <= obj.degree) ? obj.coefficients[i] : 0;
        temp.coefficients[i] = value1 + value2;
    }
    return temp;
}

Polinom Polinom::operator-(Polinom const &obj)
{
    int maxdegree = std::max(degree, obj.degree);
    Polinom temp(maxdegree);
    for (int i = 0; i <= maxdegree; i++)
    {
        int value1 = (i <= degree) ? coefficients[i] : 0;
        int value2 = (i <= obj.degree) ? obj.coefficients[i] : 0;
        temp.coefficients[i] = value1 - value2;
    }
    return temp;
}

Polinom Polinom::operator*(Polinom const &obj)
{
    int newdegree = degree + obj.degree;
    Polinom temp(newdegree);
    for (int i = 0; i <= newdegree; i++)
        temp.coefficients[i] = 0;

    for (int i = 0; i <= degree; i++)
        for (int j = 0; j <= obj.degree; j++)
            temp.coefficients[i + j] += coefficients[i] * obj.coefficients[j];

    return temp;
}

Polinom &Polinom::operator=(Polinom const &obj)
{
    degree = obj.degree;
    this->setDegree(degree);
    for (int i = 0; i <= degree; i++)
        coefficients[i] = obj.coefficients[i];

    return *this;
}

bool Polinom::operator==(Polinom const &obj) const
{
    if (degree != obj.degree)
        return false;
    for (int i = 0; i <= degree; i++)
        if (coefficients[i] != obj.coefficients[i])
            return false;
    return true;
}
bool Polinom::operator!=(Polinom const &obj) const
{
    return !(*this == obj);
}

std::ostream &operator<<(std::ostream &os, const Polinom &obj)
{
    int i;
    os << obj.coefficients[0];
    if (obj.degree >= 1)
        os << " + " << obj.coefficients[1] << "*x";
    for (i = 2; i <= obj.degree; i++)
        os << " + " << obj.coefficients[i] << "*(x^" << i << ")";
    os << std::endl;

    return os;
}

std::istream &operator>>(std::istream &is, Polinom &obj)
{
    is >> obj.degree;
    delete[] obj.coefficients;
    obj.coefficients = new int[obj.degree + 1];

    for (int i = 0; i <= obj.degree; i++)
        is >> obj.coefficients[i];

    return is;
}

// Alte functii membre

int Polinom::value_for(int x)
{
    int sum = 0;
    for (int i = 0; i <= degree; i++)
        sum += coefficients[i] * pow(x, i);

    return sum;
}