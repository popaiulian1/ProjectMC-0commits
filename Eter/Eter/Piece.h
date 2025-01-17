#pragma once
#include <string>
#include <json.hpp>

namespace Eter {

	class Piece
	{
	public:

		//Constructors
		Piece();
		Piece(const char& value, const bool& isPlaced, const std::string& username, const bool& isIllusion, const bool& eterCard, const bool& isEliminated = false);
		Piece(Piece&& other) noexcept;
		Piece(const Piece& other);
		Piece& operator=(const Piece& other);
		~Piece() = default;

		//Getters
		char GetValue() const;
		bool GetIsPlaced() const;
		const std::string& GetUserName() const;
		const bool& GetIsIllusion() const;
		const bool& GetEterCard() const;
		const bool& GetIsEliminated() const;
		
		//Setters
		void SetValue(const char& value);
		void SetIsPlaced(const bool& isPlaced);
		void SetUserName(const std::string& username);
		void SetIsIllusion(const bool& isIllusion);
		void SetEterCard(const bool& eterCard);
		void SetIsEliminated(const bool& isEliminated);

		//Methods

	private:
		char m_value;
		bool m_isPlaced;
		std::string m_username;
		bool m_isIllusion;
		bool m_eterCard;
		bool m_isEliminated;
	};

	void to_json(nlohmann::json& j, const Piece& p);
	void from_json(const nlohmann::json& j, Piece& p);
}


