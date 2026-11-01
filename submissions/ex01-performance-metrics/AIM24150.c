
#include "metrics.h"
#include <math.h>

double speedup(double t1, double tN)
{
    if (tN <= 0.0)
        return 0.0;

    return t1 / tN;
}

double efficiency(double t1, double tN, int N)
{
    if (N <= 0)
        return 0.0;

    return speedup(t1, tN) / N;
}

double amdahl(double s, int N)
{
    if (N <= 0)
        return 0.0;

    return 1.0 / (s + (1.0 - s) / N);
}

double amdahl_limit(double s)
{
    if (s == 0.0)
        return -1.0;

    return 1.0 / s;
}

double gustafson(double s, int N)
{
    return N - s * (N - 1);
}

double karp_flatt(double S, int N)
{
    if (N == 1)
        return -1.0;

    return (1.0 / S - 1.0 / N) / (1.0 - 1.0 / N);
}

double arithmetic_intensity(double flops, double bytes)
{
    if (bytes <= 0.0)
        return 0.0;

    return flops / bytes;
}

double ridge_point(double peak_gflops, double bandwidth_gbs)
{
    if (bandwidth_gbs <= 0.0)
        return 0.0;

    return peak_gflops / bandwidth_gbs;
}

double attainable_gflops(double peak_gflops, double bandwidth_gbs,
                         double intensity)
{
    return fmin(peak_gflops, bandwidth_gbs * intensity);
}

int is_memory_bound(double peak_gflops, double bandwidth_gbs,
                   double intensity)
{
    double ridge = ridge_point(peak_gflops, bandwidth_gbs);

    return intensity < ridge ? 1 : 0;
}

double roofline_fraction(double peak_gflops, double bandwidth_gbs,
                        double intensity, double achieved_gflops)
{
    double attainable = attainable_gflops(
        peak_gflops, bandwidth_gbs, intensity);

    if (attainable <= 0.0)
        return 0.0;

    return achieved_gflops / attainable;
}
