double CatmullRom (double* y, double dx, double t)
    {
    double m0 = (y[1] - y[-1]) / 2,
           m1 = (y[2] - y[ 0]) / 2;

    double t2   = t*t,
           t3   = t2 * t,
           t3_2 = t3 * 2,
           t2_3 = t2 * 3;

    double hermite00 =  t3_2 - t2_3 + 1;
    double hermite10 =  t3   - t2*2 + t;
    double hermite01 = -t3_2 + t2_3;
    double hermite11 =  t3   - t2;

    return hermite00 * y[0] + hermite10 * m0 * dx +
           hermite01 * y[1] + hermite11 * m1 * dx;
    }

