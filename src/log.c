#include "log.h"
#include "SDL_timer.h"
#include <stdio.h>
#include <strings.h>


static Logger logger;


static void log_with_level(const char* message, LogMessageLevel level) {
	if (level > logger.level)
		return;
	Log log;
	int i = 0;
	while(message[i] && i < LOG_MESSAGE_SIZE - 1) {
		log.message[i] = message[i];
		i++;
	}
	log.message[i] = '\0';
	log.level = level;
	log.id = ++logger.id;
	log.timestamp = SDL_GetTicks();

	int index = (logger.start + logger.length) % LOG_MESSAGE_SIZE;
	if (logger.logs[index].id != 0) {
		logger_remove();
	}

	logger.logs[(logger.start + logger.length) % LOG_MESSAGE_SIZE] = log;
	logger.length++;
}


void logger_create(LogMessageLevel level) {
	logger.level = level;
	logger.length = 0;
	logger.start = 0;
	logger.id = 0;
	for (int i = 0; i < LOG_MESSAGE_SIZE; i++) {
		logger.logs[i].id = 0;
		logger.logs[i].timestamp = 0;
	}
}


void logger_destroy() {

}


void log_message(const char* message) {
	log_with_level(message, LOG_LEVEL_MESSAGE);
}


void log_error(const char* message) {
	log_with_level(message, LOG_LEVEL_ERROR);
}


void log_warn(const char* message) {
	log_with_level(message, LOG_LEVEL_WARN);
}


void log_debug(const char* message) {
	log_with_level(message, LOG_LEVEL_DEBUG);
}


bool logger_remove() {
	if (logger.length == 0)
		return false;
	logger.length--;
	logger.logs[logger.start].id = 0;
	logger.start++;
	return true;
}


Log* logger_get(int i) {
	if (i >= logger.length)
		return 0;
	int index = (logger.start + logger.length - i - 1) % LOG_MESSAGE_SIZE;
	index = (index + LOG_MESSAGE_SIZE) % LOG_MESSAGE_SIZE;
	return logger.logs[index].id > 0 ? &logger.logs[index] : 0;
}


void logger_clear(int max_time) {
	Log* log = logger_get(logger.length - 1);
	int now = SDL_GetTicks();
	while (log) {
		if (now - log->timestamp < max_time)
			break;
		log->id = 0;
		logger.length--;
		logger.start++;
		logger.start = logger.start % LOG_MESSAGE_SIZE;
		log = logger_get(logger.length - 1);
	}
}

