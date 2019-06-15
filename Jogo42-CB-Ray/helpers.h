#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

// Se v for vetor nulo, retorna v, caso contrario retorna v normalizado
Vector2 V2Norm(Vector2 v)
{
    return (Vector2Length(v) == 0) ? Vector2Zero() : Vector2Normalize(v);
}

#endif // HELPERS_H_INCLUDED
