#include "calculator.h"
#include <cmath>

using Utils::Calculator;

double Calculator::computeWeightFrom(double volume, double specificWeight) {
    return volume * specificWeight;
}

double Calculator::computeSphereVolume(double radius) {
    return 4 / 3 * M_PI * pow(radius, 3);
}

double Calculator::computeSphereSurface(double radius) {
    return 4 * M_PI * pow(radius, 2);
}

double Calculator::computeRectangleArea(double height, double width) {
    return height * width;
}

double Calculator::computeCilinderSurface(double radius, double height) {
    return 2 * M_PI * radius * height;
}

double Calculator::computeCubeSideFromVolume(double volume) {
    return cbrt(volume); // cube root
}

double Calculator::computeTrapezoidalBasedPrismSurfaceFrom(double prismHeight, double baseHeight) {
    /*
     * To simplify the calculations, we assume that the trapezoid placed on the prism base is
     * isosceles, and that the smaller base is half the bigger. Its height is also equal to
     * the smaller base size. This means that the area of the base is equivalent to
     * baseHeight * (baseHeight * (baseHeight / 2)) (as it can be considered as as rectangle).
     * = 3 * baseHeight^2 / 2
     * the smaller lateral surfaces are simply a rectangle = baseHeight * prismHeight
     * the bigger lateral surfaces are also rectangles = (baseHeight + baseHeight / 2) * prismHeight
     */
    double baseArea = 3 * pow(baseHeight, 2) / 2;
    double smallerLateralSurface = baseHeight * prismHeight;
    double biggerLateralSurface = (baseHeight + baseHeight / 2) * prismHeight;

    return 2 * baseArea + 2 * smallerLateralSurface + 2 * biggerLateralSurface;
}
