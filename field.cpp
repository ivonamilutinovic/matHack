#include "field.h"

Field::Field(int rank, char file)
    : m_rank(rank),
      m_file(file)
{}

std::vector<Field> Field::knightJumpFields() const
{
    std::vector<Field> result;
    if (m_rank - 2 >= 1 && m_file - 1 >= 'a')
        result.push_back(Field(m_rank - 2, m_file - 1));
    if (m_rank - 2 >= 1 && m_file + 1 <= 'h')
        result.push_back(Field(m_rank - 2, m_file + 1));
    if (m_rank + 2 <= 8 && m_file - 1 >= 'a')
        result.push_back(Field(m_rank + 2, m_file - 1));
    if (m_rank + 2 <= 8 && m_file + 1 <= 'h')
        result.push_back(Field(m_rank + 2, m_file + 1));
    if (m_rank - 1 >= 1 && m_file - 2 >= 'a')
        result.push_back(Field(m_rank - 1, m_file - 2));
    if (m_rank - 1 >= 1 && m_file + 2 <= 'h')
        result.push_back(Field(m_rank - 1, m_file + 2));
    if (m_rank + 1 <= 8 && m_file - 2 >= 'a')
        result.push_back(Field(m_rank + 1, m_file - 2));
    if (m_rank + 1 <= 8 && m_file + 2 <= 'h')
        result.push_back(Field(m_rank + 1, m_file + 2));
    return result;
}

std::vector<Field> Field::adjacentFields() const
{
    std::vector<Field> result;
    for (int i = (m_rank > 1 ? m_rank - 1 : m_rank); i <= (m_rank < 8 ? m_rank + 1 : m_rank); ++i)
        for (char j = (m_file > 'a' ? m_file - 1 : m_file); j <= (m_file < 'h' ? m_file + 1 : m_file); ++j)
            if (i != m_rank || j != m_file)
                result.push_back(Field(i, j));
    return result;
}

bool Field::operator==(const Field &rhs) const
{
    return (m_rank == rhs.m_rank) && (m_file == rhs.m_file);
}

std::ostream& Field::print(std::ostream &out) const
{
    return out << m_file << m_rank;
}

std::ostream& operator<<(std::ostream &out, const Field &f)
{
    return f.print(out);
}
