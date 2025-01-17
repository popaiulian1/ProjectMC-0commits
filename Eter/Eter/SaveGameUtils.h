#pragma once
#include <filesystem>

namespace Eter {
	static std::string GenerateSaveFilename(const std::string& gameType) {
		int number = 1;
		std::string fileName;
		do {
			fileName = "savegame_" + gameType + "_" + std::to_string(number) + ".json";
			number++;
		} while (std::filesystem::exists("./SaveGames/"+fileName));
		return fileName;
	}

	static nlohmann::json LoadSaveFile(const std::string& filename) {
		std::ifstream file("./SaveGames/" + filename);
		if (file.is_open()) {
			nlohmann::json j;
			file >> j;
			file.close();
			std::cout << "\n ========= GAME LOADED SUCCSEFULLY ========= \n";
			return j;
		}
		else {
			std::cout << "\n ========== FILE COULD NOT BE FOUND ========== \n";
		}
	}
}