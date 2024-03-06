#include <iostream>
#include <cmath>

class Complex{
    // Complex();
public:
    Complex (double = 0, double = 0); //чтобы не прописывать  Default constructor, неявно преобразует остальное в Complex
    bool operator<(const Complex&) const;
    Complex operator+ (const Complex&);
    bool operator>(const Complex&) const;
    Complex* getPtr();

    static size_t complexCounter; //можно получить доступ без объекта
    static double sum(double, double);
    
friend std::ostream& operator<< (std::ostream& ss, const Complex& comp);

//поля снизу
private:
    double re;
    double im;
};

// Complex::Complex(double re, double im){ //через присваивание, типа  int a; a=3;
//     this->re = re;
//     this->im = im;
// }

// Complex::Complex(): re(0), im(0){};
Complex::Complex(double re, double im): re(re), im(im){ //здесь инициализация (сразу присваиваем памяти), типа int a = 3;
    if (im == 0)
        throw std::invalid_argument ("Not a complex number");
    complexCounter++;
}; //из main re im

bool Complex::operator<(const Complex& other) const{
    return std::sqrt(std::pow(re, 2) + std::pow(im, 2)) < std::sqrt(std::pow(other.re, 2) + std::pow(other.im, 2));
}

Complex Complex::operator+(const Complex& other){
    return Complex {re + other.re, im + other.im};
}

std::ostream& operator<< (std::ostream& ss, const Complex& comp){
    ss << comp.re << (comp.im > 0 ? "+": "") << comp.im << "i";
    return ss;
}

Complex operator+ (double a, Complex& c){
    return c+a;
}

bool isGreater(const Complex& a, const Complex& b){
    return b < a;
}

bool Complex::operator>(const Complex& other) const{
    return other < *this;
}

Complex* Complex::getPtr(){
    return this;
}


size_t Complex::complexCounter = 0;

double Complex::sum(double a, double b){
    return a + b;
}

int main(){
    Complex comp {2, 3}; //Default constructor
    Complex comp2 {4, -10};
    std::vector<Complex> vectorComp;
    for (size_t i = 0; i < 4; i++){
        double re, im;
        std::cin >> re >> im;
        try{
            Complex comp3 {re, im};
            vectorComp.push_back(comp3);
        }
        catch(std::invalid_argument error){
            std::cerr << error.what();
        }
        catch(...){
            std::cerr << "smth wrong";
        }
    }

    
    // std::sort(vectorComp.begin(), vectorComp.end(), isGreater);
    std::sort(vectorComp.begin(), vectorComp.end(), std::greater<Complex>());

    // std::cout << comp.re << '\t' << comp.im << '\n';
    std::cout << (comp<comp2) << '\n';
    std::cout << 5 + comp << '\n';
    
    for (std::vector<Complex>::const_iterator it = vectorComp.begin(); it != vectorComp.end(); ++it){
        // it -> re = 5; //with const_iterator dont work
        std::cout << *it << '\n';
    }

    std::cout << &comp << '\n';
    std::cout << comp.getPtr() << '\n';

    std::cout << Complex::complexCounter << '\n';

    std::cout << comp.sum(4, 6) << '\n';
    std::cout <<Complex::sum(2, 7);

    
}