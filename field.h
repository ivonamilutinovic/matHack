#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <memory>
#include "figures/figure.h"

class Field
{
public:
    Field(int rank, char file);
    std::vector<Field> sameRankFields() const; // za pomeranje topa i kraljice
    std::vector<Field> sameFileFields() const; // za pomeranje topa i kraljice
    std::vector<Field> sameDiagonalFields() const; // za pomeranje lovca i kraljice
    std::vector<Field> knightJumpFields() const; // za pomeranje konja
    std::vector<Field> adjacentFields() const; // za pomeranje kralja
    inline int rank() const { return m_rank; }
    inline char file() const { return m_file; }
private:
    int m_rank; // red (od 1 do 8)
    char m_file; // linija (od 'a' do 'h')
    std::unique_ptr<Figure> m_occupant;
};

#endif // FIELD_H
