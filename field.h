#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field
{
public:
    Field(int rank, char file);
    std::vector<Field> sameRankFields() const;
    std::vector<Field> sameFileFields() const;
    std::vector<Field> sameDiagonalFields() const;
    std::vector<Field> knightJumpFields() const;
private:
    int m_rank; // red (od 1 do 8)
    char m_file; // linija (od 'a' do 'h')
};

#endif // FIELD_H
