# OpenLib
This library provides a convenient and multi-platform shell to load dynamic libraries explicitly in C++

# API documentation

## Class: DL

|metod|description|
|-|-|
|DL(const std::filesystem::path& path, std::vector<std::string> sims = {}, bool allLoad = false)|the library specified in the path will be loaded (an extension will automatically be added depending on the system), then all symbolic links from sims will be placed in the database|
|template\<typename T = void*\><br>T getSim(std::string simStr)|If this symbolic link is not in the database, it will be loaded from the file, saved to the database and returned from the|
|template\<typename T = void*\><br>T getSimFromDB(std::string simStr)|method returns a symbolic link from the database|
|template\<typename T = void*\><br>T getSimFromLib(std::string simStr)|method returns a symbolic reference from the library|
