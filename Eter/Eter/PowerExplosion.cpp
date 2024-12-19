#include "PowerExplosion.h"

Eter::Player* Eter::PowerExplosion::GetTriggeringPlayer() const
{
    return m_triggeringPlayer;
}

Matrix Eter::PowerExplosion::GetAffectedTiles() const
{
    return m_affectedTiles;
}

void Eter::PowerExplosion::SetTriggeringPlayer(Player* triggeringPlayer)
{
    m_triggeringPlayer = triggeringPlayer;
}

void Eter::PowerExplosion::SetAffectedTiles(const Matrix& affectedTiles)
{
    m_affectedTiles = affectedTiles;
}
