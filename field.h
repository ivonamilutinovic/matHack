#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <iostream>

class Field
{
public:
    Field(int rank, char file);
    std::vector<Field> knightJumpFields() const; // za pomeranje konja
    std::vector<Field> adjacentFields() const; // za pomeranje kralja
    inline int rank() const { return m_rank; }
    inline char file() const { return m_file; }
    bool operator==(const Field &rhs) const;
    std::ostream& print(std::ostream &out) const;
private:
    int m_rank; // red (od 1 do 8)
    char m_file; // linija (od 'a' do 'h')
};

std::ostream& operator<<(std::ostream &out, const Field &f);

#endif // FIELD_H
