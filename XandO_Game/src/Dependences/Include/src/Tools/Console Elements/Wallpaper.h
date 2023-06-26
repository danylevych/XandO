#pragma once

#include <string>
#include <vector>


namespace Core
{
	class Wallpaper final
	{
	private:
		std::string path;
		std::vector<std::u16string> wallpaper;

	public:
		Wallpaper();
		Wallpaper(const std::string& wallPath);

	public:
		void Refresh();
		void SetWall(const std::string& wallPath);

		std::vector<std::u16string> GetWallpaper();

	public:
		friend std::ostream& operator<<(std::ostream& out, const Wallpaper& wall);
	};
}