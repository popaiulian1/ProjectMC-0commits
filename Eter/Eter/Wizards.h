#pragma once

#include "Board.h"
#include<string>
#include<vector>

namespace Eter {

    enum class MageType {
        FIRE,
        EARTH,
        AIR,
        WATER,
        UNKNOWN
    };

    class Wizards {
    public:

        //Constructors + Rule of Five
        Wizards();
        Wizards(std::string wizardName, MageType type, Board* gameBoard, std::string m_username);
        Wizards(const Wizards& other);
        ~Wizards() = default;
        Wizards(Wizards&& other) noexcept = default;
        Wizards& operator=(const Wizards& other) = default ;
        Wizards& operator=(Wizards&& other) noexcept = default;

        //Getters
        const std::string& GetUserName() const;
        const Eter::MageType& GetMageType() const;
		const std::string toStringMageType(MageType mageType) const;
		const Board* GetBoardWizard() const;

        //Setters
        void SetMageType(const Eter::MageType& type);
        void SetUserName(const std::string& username);
        void SetBoardForMage(Board* board);

        // Methods for each MageType, every MageType has two powers, the power will be determined by powerindex
        void fireMasterPower(int powerIndex, int row, int col);
        void earthMasterPower(int powerIndex, int row, int col, std::vector<Piece>& playerHand);
        void airMasterPower(int powerIndex, int row, int col);
        void waterMasterPower(int powerIndex, int srcRow, int srcCol, int destRow, int destCol);

        //Methods for Powers determined by powerIndex
        void eliminateOpponentCard(int row, int col);
        void eliminateRow(int row);
        void eliminateCol(int col);
        void coverOpponentCard(int row, int col, std::vector<Piece>& playerHand);
        void createPit(int row, int col);
        void moveOwnStack(int srcRow, int srcCol, int destRow, int destCol);
		void gainExtraEtherCard(int row, int col); 
		void moveOpponentStack(int srcRow, int srcCol, int destRow, int destCol);
        void moveEdgeRowCol();  




    private:
        std::string m_name;
        MageType m_mageType;
        bool m_magicPowerUsed;
        int m_etherCards;
        Board* m_board;
        std::string m_username;

    };
}