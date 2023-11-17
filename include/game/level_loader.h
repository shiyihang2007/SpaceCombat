
#ifndef LEVLE_LOADER_H
#define LEVLE_LOADER_H

#include <map>
#include <string>
#include <vector>

struct Enemy {
	std::string type;
	float position;
	int count;
};

using Wave = std::vector<Enemy>;
using Level = std::vector<Wave>;

class LevelLoader {
	LevelLoader() {}

  public:
	static std::map<std::string, Level> levels;

	static auto LoadLevel(const char *levelName, const char *filePath)
		-> Level &;
	static auto GetLevel(const char *levelName) -> Level &;
	static void Clear();
};

#endif
