/**
 * Author: bomba de tenedores
 * Description: iterar sobre mascaras de bits
 */

typedef unsigned int uint;
uint nextMask(uint mask){
    uint t = mask | (mask - 1);
    return  (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(mask) + 1));
}
// Iterar sobre todos las mascaras de tamano N con m bits prendidos
for(uint mask = (1<<m)-1; !(mask & (1<<N)); mask = nextMask(mask)){}

//Iterar sobre todas las submascaras de mask de forma creciente (no incluye vacio)
for(uint s = 0 ; s = s - mask & mask ;) {}

//Iterar sobre todas las submascaras de mask de forma decreciente (no incluye vacio)
for(uint s = (mask-1) & mask ; s; s = (s-1) & mask )  {}