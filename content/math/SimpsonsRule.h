/**
 * Author: bomba de tenedores
 * Description: Simpsons Rule
 */


double f(double x){ }
//simpsons rule
double integral(double a, double b){
    int n = 10000; //PAR
    double I = f(a) + f(b), h = (b-a)/n;
    FOR(i,0,n)
        I += ((i&1) ? 2:4) * f(a + h*i); 
    return I * h/3;
}