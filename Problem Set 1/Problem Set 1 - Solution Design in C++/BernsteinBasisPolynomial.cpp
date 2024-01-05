#include "BernsteinBasisPolynomial.h"
#include <cmath>

BernsteinBasisPolynomial::BernsteinBasisPolynomial(unsigned int aV, unsigned int aN) :fFactor(Combination(aN, aV))
{

}

double BernsteinBasisPolynomial::operator()(double aX) const
{
	return fFactor() * pow((fFactor.getN() - fFactor.getK()), (1 - aX)) * pow(aX, fFactor.getK());
}