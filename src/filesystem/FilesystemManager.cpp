#include "FilesystemManager.h"

void FilesystemManager::begin(SystemManager &sys)
{
    this->sys = sys;
    logger.begin("[Filesystem]");

    if (!LittleFS.begin())
    {
        logger.println("Error has occurred while mounting LittleFS", FATAL);
        sys.requestRestart();
        return;
    }
}

String FilesystemManager::getFileContent(String path)
{
    File file = LittleFS.open(path, "r");
    String content = file.readString();
    file.close();

    return content;
}

std::vector<String> FilesystemManager::listDirectory(String dir_path)
{
    if (dir_path == "/") dir_path = "";
    
    std::vector<String> result;
    
    Dir dir = LittleFS.openDir(dir_path);
    while (dir.next())
    {
        if (dir.isDirectory())
        {
            auto files = listDirectory(dir_path + "/" + dir.fileName());
            result.insert(result.end(), files.begin(), files.end());
        }
        else if (dir.isFile())
        {
            result.push_back(dir_path + "/" + dir.fileName());
        }
    }

    return result;
}