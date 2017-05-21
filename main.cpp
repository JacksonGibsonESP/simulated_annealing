#include <iostream>
#include <random>
#include <chrono>

double f(double x1, double x2) {
    return (x1 * x1 + x2 - 11) * (x1 * x1 + x2 - 11) + (x1 + x2 * x2 - 7) * (x1 + x2 * x2 - 7);
}

void G(double * x1, double * x2) {
    static long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_real_distribution<double> distribution(-10, 10);
    *x1 = distribution(generator);
    *x2 = distribution(generator);
}

double my_rand(){
    static long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(seed);
    static std::uniform_real_distribution<double> distribution(0, 1);
    return distribution(generator);
}


double T(int i) {
    return exp(20 - i * 0.01);
}

int main() {
    int iteration = 0;
    double t = T(iteration);
    double x1, x2;
    G(&x1, &x2);
    while (t > 0.001) {
        double temp1, temp2;
        G(&temp1, &temp2);
        double dE = f(temp1, temp2) - f(x1, x2);
        if (dE <= 0) {
            x1 = temp1;
            x2 = temp2;
        } else {
            double p = exp(- dE / t);
            if (my_rand() <= p) {
                x1 = temp1;
                x2 = temp2;
            }
        }
        std::cout << x1 << " " << x2 << " " << f(x1, x2) << " " << t << "\n";
        ++iteration;
        t = T(iteration);
    }
    std::cout << iteration << "\n";
    return 0;
}