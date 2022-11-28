#include "accessory.h"
#include<string.h>

using Models::Accessory;

Accessory::Accessory(string color, list<Material> materials)
  :Product(color, materials, Size::ONE_SIZE){}
