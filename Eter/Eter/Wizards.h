#pragma once

#include "Board.h"
#include<string>
#include<vector>

namespace Eter {

    enum class MageType {
        FIRE,
        EARTH,
        AIR,
        WATER
    };

    class Wizards {
    public:
        Wizards();
        Wizards(std::string wizardName, MageType type, Board* gameBoard, std::string m_username);
        Wizards(const Wizards& other);
        ~Wizards()= default;
        const std::string& GetUserName() const;

       // Methods for each MageType, every MageType has two powers, the power will be determined by powerindex
        void fireMasterPower(int powerIndex, int row, int col);
        void earthMasterPower(int powerIndex, int row, int col, std::vector<Piece>& playerHand);
        void airMasterPower(int powerIndex, int row, int col);
        void waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow);

        //Methods for Powers determined by powerIndex
        void eliminateOpponentCard(int row, int col);
        void eliminateRow(int row);
        void eliminateCol(int col);
        void coverOpponentCard(int row, int col, std::vector<Piece>& playerHand);
        void createPit(int row, int col);
        void moveOwnStack();
        void gainExtraEtherCard();
        void moveOpponentStack();
        void moveEdgeRow();


    private:
        std::string m_name;
        MageType m_mageType;
        bool m_magicPowerUsed;
        int m_etherCards;
        Board* m_board;
        std::string m_username;

    };
}
