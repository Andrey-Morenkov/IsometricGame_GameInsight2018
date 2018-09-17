#pragma once

#include <string>

#include "SDL_log.h"
#include "ResultCode.h"

#define EMPTY_STRING_LENGTH 0
#define EMPTY_CONTAINER_SIZE 0
#define INVALID_POINTER nullptr

#define POINTER_VALIDATION(pointer)       \
if (pointer == INVALID_POINTER)           \
{                                         \
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s: pointer %s is NULL. Immediate exit. SDL_Error: %s", __FUNCTION__, std::string(#pointer), SDL_GetError()); \
	SDL_Delay(2000);                      \
	exit((int)ResultCode::ERROR);         \
}                    

#define STRING_VALIDATION(input_string)              \
if (input_string.length == EMPTY_STRING_LENGTH)      \
{                                                    \
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s: input string %s is empty. Immediate exit.", __FUNCTION__, std::string(#input_string)); \
	exit((int)ResultCode::ERROR);                    \
}       

#define POINTER_MUST_BE_EMPTY(pointer)         \
if (pointer != INVALID_POINTER)                \
{                                              \
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s: pointer %s is not empty,  but MUST be. Immediate exit.", __FUNCTION__, std::string(#pointer)); \
	exit((int)ResultCode::ERROR);              \
}     

#define CONTAINER_MUST_BE_EMPTY(container)     \
if (container.size() != EMPTY_CONTAINER_SIZE)  \
{                                              \
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s: container %s size = %d, but MUST be empty. Immediate exit.", __FUNCTION__, std::string(#container), container.size()); \
	exit((int)ResultCode::ERROR);              \
}         

#define INT_MUST_BE_GREATER_THAN_ZERO(integer)       \
if (integer <= 0)                                    \
{                                                    \
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s: number %s = %d, but MUST be > 0. Immediate exit.", __FUNCTION__, std::string(#integer), integer); \
	exit((int)ResultCode::ERROR);                    \
}    

#define LOG_INFO(payload, ...) \
SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, payload, __VA_ARGS__);

#define LOG_ERROR(payload, ...) \
SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, payload, __VA_ARGS__);

#define LOG_CRITICAL(payload, ...) \
SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, payload, __VA_ARGS__);