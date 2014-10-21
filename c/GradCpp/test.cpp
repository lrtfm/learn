#include "GradientDescent.hpp"

// double myfun(const Mvector &x);

double myfun(const Mvector &x)
{
    return x[0] * x[0] + x[1] * x[1] + x[0];
}

double myfun2(const Mvector &x)
{
    return 2*x[0] * x[0] + x[1] * x[1] + x[0];
}

int main(int argc, char **argv)
{
    FunctionWapper fWapper(2, myfun2);
    GradientDescent gradDescent(fWapper);

    Mvector ret(2);
    Mvector x0(2);
    x0[0] = 2;
    x0[1] = 3;
   
    x0.print("The initial x0");
    ret = gradDescent.solver(x0, 0.000001);
    ret.print("The return value");

    return 0;
}


