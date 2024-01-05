#include "Polygon.h"
#include <stdexcept>

float Polygon::getSignedArea() const
{
    float Result = 0.0f;

    if (fNumberOfVertices > 2)
    {
        for (size_t i = 0; i < fNumberOfVertices; i++) 
        {
            size_t nextI = (i + 1) % fNumberOfVertices;
            Result = Result + fVertices[i].getX() * fVertices[nextI].getY() - fVertices[i].getY() * fVertices[nextI].getX();
        }
    }

    Result = Result/2;

    return Result;
}