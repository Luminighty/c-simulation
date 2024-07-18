#ifndef _LOG_H_
#define _LOG_H_

#include <stdbool.h>


#define LOG_BUFFER_SIZE 128
#define LOG_MESSAGE_SIZE 32


typedef enum {
	LOG_LEVEL_MESSAGE,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_DEBUG
} LogMessageLevel;

typedef struct {
	LogMessageLevel level;
	const char* message;
	int timestamp;
	int id;
} Log;


typedef struct {
	Log logs[LOG_MESSAGE_SIZE];
	LogMessageLevel level;
	unsigned int id;
	int length;
	int start;
} Logger;


void logger_create(LogMessageLevel level);
void logger_destroy();

void log_message(const char* message);
void log_error(const char* message);
void log_warn(const char* message);
void log_debug(const char* message);
void logger_clear(int max_time);
bool logger_remove();
Log* logger_get(int i);


#endif // _LOG_H_H
