#include "PowerExplosion.h"


Eter::PowerExplosion::PowerExplosion(const Matrix& affetedTiles)
    : m_triggeringPlayer{ nullptr }, m_affectedTiles{ affetedTiles }, m_wasUsed{ false } {}

//Getters
Eter::Player* Eter::PowerExplosion::GetTriggeringPlayer() const
{
    return m_triggeringPlayer;
}

Matrix Eter::PowerExplosion::GetAffectedTiles() const
{
    return m_affectedTiles;
}

bool Eter::PowerExplosion::GetWasUsed() const
{
    return m_wasUsed;
}


//Setters
void Eter::PowerExplosion::SetTriggeringPlayer(Player* triggeringPlayer)
{
    m_triggeringPlayer = triggeringPlayer;
}

void Eter::PowerExplosion::SetAffectedTiles(const Matrix& affectedTiles)
{
    m_affectedTiles = affectedTiles;
}

void Eter::PowerExplosion::SetWasUsed(const bool& wasUsed)
{
    m_wasUsed = wasUsed;
}


//Methods
void Eter::PowerExplosion::Trigger()
{
}

Matrix Eter::PowerExplosion::Rotate90Degrees()
{
    int rows = m_affectedTiles.size();
    int cols = m_affectedTiles[0].size();

    Matrix rotatedMatrix(cols, std::vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotatedMatrix[j][rows - 1 - i] = m_affectedTiles[i][j];
        }
    }

    return rotatedMatrix;
}
