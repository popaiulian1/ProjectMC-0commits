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
        Wizards(std::string wizardName, MageType type, const Board* gameBoard);
        Wizards(const Wizards& other);
        ~Wizards()= default;

        void fireMasterPower(int powerIndex, int row, int col);
        void earthMasterPower(int powerIndex, int row, int col, std::vector<int>& playerHand);
        void airMasterPower(int powerIndex, int row, int col);
        void waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow);

    private:
        std::string name;
        MageType mageType;
        bool magicPowerUsed;
        int etherCards;
        const Board* board;

    };
}
