#include "game/level_loader.h"

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

#include <string>
#include <utility>
#include <vector>

std::map<std::string, Level> LevelLoader::levels;

auto LevelLoader::LoadLevel(const char *levelName, const char *filePath)
	-> Level & {
	auto &level = levels[std::string(levelName)];

	YAML::Node waves = YAML::LoadFile(filePath);
	level.reserve(waves.size());
	for (const auto &wave : waves) {
		Wave tmp;
		tmp.reserve(wave.size());
		for (const auto &enemy : wave) {
			Enemy eny;
			eny.type = enemy["type"].as<std::string>();
			eny.count = enemy["count"].as<int>();
			eny.position = enemy["position"].as<float>();
			tmp.push_back(std::move(eny));
		}
		level.push_back(std::move(tmp));
	}
	return level;
}

auto LevelLoader::GetLevel(const char *levelName) -> Level & {
	return levels[levelName];
}

void LevelLoader::Clear() { levels.clear(); }
