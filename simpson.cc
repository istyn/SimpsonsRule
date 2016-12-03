/*-----------------------------------------------------------
input:
    f   - function pointer
    a,b - end-points of the interval of integration
    n   - number of iterations
--------------------------------------------------------------*/
    double simpson(double(*f)(double), double a, double b, int n)
{
    //int i;
    double s, dx, x;
// if n is odd - add +1 interval to make it even
    n &= -2;
    s = 0.0;
    dx = (b-a)/static_cast<double>(n);

    #pragma omp parallel for shared(s,a) private(x)
    for ( int i=2; i<=n-1; i=i+2)
    {
        x = a+static_cast<double>(i)*dx;
        #pragma omp atomic
        s = s + 2.0*f(x) + 4.0*f(x+dx);
    }
    s = (s + f(a)+f(b)+4.0*f(a+dx) )*dx/3.0;
    return s;
}
