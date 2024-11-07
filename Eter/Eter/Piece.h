#pragma once
#include <string>
namespace Eter {
	class Piece
	{
	public:
		Piece();
		Piece(const int& value, const bool& isPlaced, const std::string& username);
		~Piece() = default;
		int GetValue() const;
		bool GetIsPlaced() const;
		const std::string& GetUserName() const;
		void SetValue(const int& value);
		void SetIsPlaced(const bool& isPlaced);
		void SetUserName(const std::string& username);
	private:
		int m_value;
		bool m_isPlaced;
		std::string m_username;
	};
}


