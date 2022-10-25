#include <iostream>
#include <cstdarg>
#include <math.h>

class Polinom
{
private:
    int grad;
    int *coeficienti;

public:
    Polinom(int grad_ = 0, ...);
    Polinom(Polinom const &rhs);
    ~Polinom();

    Polinom operator+(const Polinom &obj);
    Polinom operator-(const Polinom &obj);
    Polinom operator*(const Polinom &obj);
    Polinom &operator=(const Polinom &obj);

    void setGrad(int grad_);
    void setValues();
    void printGrad();
    void printValues();

    int value_for(int x);
};

int main()
{
    // Polinom p1(2, 1, 5, 1);
    // Polinom p2(3, 2, 2, 2,6);
    // Polinom p3 = p1 + p2;
    // Polinom p4 = p1 - p2;
    // Polinom p5 = p1 * p2;
    // p1.printValues();
    // p2.printValues();
    // p3.printValues();
    // p4.printValues();
    // p5.printValues();
    Polinom p1(5);
    p1.printGrad();

    return 0;
}

// Constructori si destructor
Polinom::Polinom(int grad_, ...)
{
    grad = grad_++;
    coeficienti = new int[grad + 1]();
    va_list valist;
    va_start(valist, grad_);
    for (int i = 0; i <= grad; i++)
        coeficienti[i] = va_arg(valist, int);
}

Polinom::Polinom(Polinom const &rhs)
{
    grad = rhs.grad;
    coeficienti = new int[grad + 1];
    for (int i = 0; i <= grad; i++)
        coeficienti[i] = rhs.coeficienti[i];
}

Polinom::~Polinom()
{
    delete[] coeficienti;
}

// Supraincarcarea operatorilor
Polinom Polinom::operator+(Polinom const &obj)
{
    int maxGrad = std::max(grad, obj.grad);
    Polinom temp(maxGrad);
    for (int i = 0; i <= maxGrad; i++)
    {
        int value1 = (i <= grad) ? coeficienti[i] : 0;
        int value2 = (i <= obj.grad) ? obj.coeficienti[i] : 0;
        temp.coeficienti[i] = value1 + value2;
    }
    return temp;
}

Polinom Polinom::operator-(Polinom const &obj)
{
    int maxGrad = std::max(grad, obj.grad);
    Polinom temp(maxGrad);
    for (int i = 0; i <= maxGrad; i++)
    {
        int value1 = (i <= grad) ? coeficienti[i] : 0;
        int value2 = (i <= obj.grad) ? obj.coeficienti[i] : 0;
        temp.coeficienti[i] = value1 - value2;
    }
    return temp;
}

Polinom Polinom::operator*(Polinom const &obj)
{
    int newGrad = grad + obj.grad;
    Polinom temp(newGrad);
    for (int i = 0; i <= newGrad; i++)
        temp.coeficienti[i] = 0;

    for (int i = 0; i <= grad; i++)
        for (int j = 0; j <= obj.grad; j++)
            temp.coeficienti[i + j] += coeficienti[i] * obj.coeficienti[j];

    return temp;
}

Polinom &Polinom::operator=(Polinom const &obj)
{
    grad = obj.grad;
    coeficienti = new int[grad + 1];
    for (int i = 0; i <= grad; i++)
        coeficienti[i] = obj.coeficienti[i];

    return *this;
}

// Functii membre
void Polinom::setGrad(int grad_)
{
    grad = grad_;
}

void Polinom::setValues()
{
    if (grad == 0)
    {
        std::cout << "Introduceti gradul polinomului: ";
        std::cin >> grad;
        coeficienti = new int[grad + 1];
    }

    for (int i = 0; i <= grad; i++)
    {
        std::cout << "P[" << i << "] = ";
        std::cin >> coeficienti[i];
    }
}

void Polinom::printGrad()
{
    std::cout << grad << std::endl;
}

void Polinom::printValues()
{
    for (int i = 0; i < grad; i++)
        std::cout << coeficienti[i] << "*(x^" << i << ") + ";
    std::cout << coeficienti[grad] << " *(x^" << grad << ") \n";
}

int Polinom::value_for(int x)
{
    int sum = 0;
    for (int i = 0; i <= grad; i++)
        sum += coeficienti[i] * pow(x, i);

    return sum;
}