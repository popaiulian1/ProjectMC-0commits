#include "PowerExplosion.h"


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
