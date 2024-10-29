#pragma once

namespace Eter {
	class Piece
	{
	public:
		Piece();
		Piece(const int& value, const bool& isPlaced);
		~Piece() = default;
		int GetValue() const;
		bool GetIsPlaced() const;
		void SetValue(const int& value);
		void SetIsPlaced(const bool& isPlaced);
	private:
		int m_value;
		bool m_isPlaced;
	};
}


