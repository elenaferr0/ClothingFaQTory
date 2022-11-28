#include "bracelet.h"
#include "models/material.h"

using Models::Material;
using Models::Accessories::Bracelet;

Bracelet::Bracelet(string color, list<Material> materials, unsigned int pearlNumber, double pearlDiameter)
  : Accessory(color, materials), pearlNumber(pearlNumber), pearlDiameter(pearlDiameter){}
