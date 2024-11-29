#pragma once
#include <string>
namespace Eter {
	class Piece
	{
	public:

		//Constructors
		Piece();
		Piece(const char& value, const bool& isPlaced, const std::string& username, const bool& isIllusion);
		Piece(Piece&& other) noexcept;
		Piece(const Piece& other);
		Piece& operator=(const Piece& other);
		~Piece() = default;

		//Getters
		char GetValue() const;
		bool GetIsPlaced() const;
		const std::string& GetUserName() const;
		const bool& GetIsIllusion() const;
		
		//Setters
		void SetValue(const char& value);
		void SetIsPlaced(const bool& isPlaced);
		void SetUserName(const std::string& username);
		void SetIsIllusion(const bool& isIllusion);

		//Methods

	private:
		char m_value;
		bool m_isPlaced;
		std::string m_username;
		bool m_isIllusion;
	};
}


