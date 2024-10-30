#pragma once
#include <string>

namespace Eter {
	class Player {
	public:
		Player(std::string username);
		~Player() = default;
		const std::string& GetUserName() const;
	private:
		std::string m_username;
	};
}
