#include "field.h"

Field::Field(int rank, char file)
    : m_rank(rank),
      m_file(file)
{}

std::vector<Field> Field::sameRankFields() const
{
    std::vector<Field> result;
    for (char file = 'a'; file <= 'h'; ++file)
        if (file != m_file)
            result.push_back(Field(m_rank, file));
    return result;
}

std::vector<Field> Field::sameFileFields() const
{
    std::vector<Field> result;
    for (int rank = 1; rank <= 8; ++rank)
        if (rank != m_rank)
            result.push_back(Field(rank, m_file));
    return result;
}

std::vector<Field> Field::sameDiagonalFields() const
{
    std::vector<Field> result;
    char file = m_file - 1;
    int rank = m_rank - 1;
    for (; file >= 'a' && rank >= 1; --file, --rank)
        result.push_back(Field(rank, file));
    file = m_file - 1;
    rank = m_rank + 1;
    for (; file >= 'a' && rank <= 8; --file, ++rank)
        result.push_back(Field(rank, file));
    file = m_file + 1;
    rank = m_rank - 1;
    for (; file <= 'h' && rank >= 1; ++file, --rank)
        result.push_back(Field(rank, file));
    file = m_file + 1;
    rank = m_rank - 1;
    for (; file <= 'h' && rank <= 8; ++file, ++rank)
        result.push_back(Field(rank, file));
    return result;
}

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
