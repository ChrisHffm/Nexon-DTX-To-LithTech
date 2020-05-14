#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

bool ends_with(const std::wstring& filename, const std::string& ext)
{
	return ext.length() <= filename.length() &&
		std::equal(ext.rbegin(), ext.rend(), filename.rbegin());
}

int main()
{
	try
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator("files\\")) {
			if (entry.path().has_extension())
			{
				if (ends_with(entry.path().c_str(), ".DTX") || ends_with(entry.path().c_str(), ".dtx"))
				{
					std::fstream fileStream(entry.path().c_str());

					if (fileStream.is_open()) {
						fileStream.seekg(0, fileStream.end);
						int length = fileStream.tellg();
						fileStream.seekg(0, fileStream.beg);

						char buffer[8];

						fileStream.seekg(4, fileStream.beg);
						fileStream.read(buffer, 8);

						fileStream.seekg(4, fileStream.beg);
						fileStream.seekp(4, fileStream.beg);
						fileStream.write(buffer + 4, 4);
						fileStream.write(buffer, 4);
						fileStream.flush();
						fileStream.close();

						printf("%S converted\n", entry.path().c_str());
					}
				}
			}
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what();
	}

	getchar();

	return 1;
}