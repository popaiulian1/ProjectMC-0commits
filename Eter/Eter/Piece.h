#pragma once
#include <string>
namespace Eter {
	class Piece
	{
	public:
		Piece();
		Piece(const char& value, const bool& isPlaced, const std::string& username);
		Piece(const char& value); // This constructor is made to only be used with a placed piece currently so the value of m_isPlaced is set to true
		~Piece() = default;
		char GetValue() const;
		bool GetIsPlaced() const;
		const std::string& GetUserName() const;
		void SetValue(const char& value);
		void SetIsPlaced(const bool& isPlaced);
		void SetUserName(const std::string& username);
	private:
		char m_value;
		bool m_isPlaced;
		std::string m_username;
	};
}


