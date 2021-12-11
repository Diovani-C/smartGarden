#include "filesystem.hpp"

void appendFile(fs::FS &fs, const char *path, const char *message)
{
  File file = fs.open(path, FILE_APPEND);
  file.print(message);
}

void removeInitialLines(fs::FS &fs, const char *path, uint16_t lineNumber)
{
  File oldFile = fs.open(path, FILE_READ);
  File newFile = fs.open("/temp.txt", FILE_WRITE);

  uint16_t lineCounter = lineNumber;
  while (lineCounter > 0 && oldFile.available())
  {
    if (!oldFile.find('\n'))
      break;

    lineCounter--;
    delay(0);
  }

  while (oldFile.available())
  {
    const char characer = (char)oldFile.read();
    newFile.print(characer);
    delay(0);
  }

  oldFile.close();
  newFile.close();

  fs.remove(path);
  fs.rename("/temp.txt", path);
}