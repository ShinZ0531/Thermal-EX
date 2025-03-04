#include "mult5.h"

// Main program
int main(int, char **)
{
    if (mult5(6) != 30) {
	throw "5*6 != 30";
    }
}