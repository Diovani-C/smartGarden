#include <Arduino.h>
#include <FS.h>

/**
 * @brief Append string to end of file
 * 
 * @param fs
 * @param path Path to the file
 * @param message Message to append
 */
void appendFile(fs::FS &fs, const char *path, const char *message);

/**
 * @brief Remove X number of lines from the beginning of the file
 * 
 * @param fs
 * @param path Path to the file
 * @param lineNumber Number of lines to remove
 */
void removeInitialLines(fs::FS &fs, const char *path, uint16_t lineNumber);