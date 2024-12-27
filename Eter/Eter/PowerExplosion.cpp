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
void Eter::PowerExplosion::Trigger(Board& board, Player& player) {

    if (m_wasUsed == true) {
        throw std::runtime_error("Power Explosion Has Already Been Used In This Round!");
    }

    if (!m_triggeringPlayer) {
        throw std::runtime_error("Triggering Player Must Be Set Before Triggering Power Explosion");
    }

    ApllyExplosion(board, player);
    m_wasUsed = true;

    std::cout << "\nPower Explosion Was Triggered By Player " << m_triggeringPlayer->GetUserName();
}

Matrix Eter::PowerExplosion::Rotate90Degrees() {
  
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

void Eter::PowerExplosion::ApllyExplosion(Board& board, Player& player) {

    auto gameBoard = board.GetBoardReference();
    
    size_t indexRow = 0;
    size_t indexCol = 0;
    
    for (auto& row : gameBoard) {
        indexRow++;
        for (auto& tile : row) {
            indexCol++;
            if (m_affectedTiles[indexRow][indexCol] == 1) { // m_affedtedTiles[][] is 1 means the piece has to return to owners hand
                Piece topPiece = tile.value().GetTopValue();
                player.AddPiece(topPiece);
                tile.value().GetValue().pop_back();
            }
            else if (m_affectedTiles[indexRow][indexCol] == 2) { // ejects the piece from the play
                tile.value().GetValue().pop_back();
            }
        }
    }
}
