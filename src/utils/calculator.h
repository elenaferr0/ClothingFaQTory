#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace Utils {
    class Calculator {
    public:
        static double computeWeightFrom(double volume, double specificWeight);

        static double computeSphereVolume(double radius);

        static double computeSphereSurface(double radius);

        static double computeRectangleArea(double height, double width);

        static double computeCilinderSurface(double radius, double height);

        static double computeTrapezoidalBasedPrismSurfaceFrom(double prismHeight, double baseHeight);

        static void squaredCmToSquaredMeters(double& cm);
    };
}

#endif // CALCULATOR_H
