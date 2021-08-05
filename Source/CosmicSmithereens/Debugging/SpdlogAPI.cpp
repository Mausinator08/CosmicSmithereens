#include "stdafx.h"

#include "SpdLogAPI.h"
#include "Debug.h"

// spdlog Logging: defines
#if defined(_DEBUG) && !defined(PUBLIC_BUILD)

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#elif !defined(_DEBUG) && !defined(PUBLIC_BUILD)

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO

#elif !defined(_DEBUG) && defined(PUBLIC_BUILD)

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_ERROR

#endif

#define SPDLOG_WCHAR_FILENAMES
#define SPDLOG_EOL "\r\n"
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#define SPDLOG_FUNCTION __FUNCTION__

// spdlog Logging: includes
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/pattern_formatter.h"
#include "spdlog/cfg/env.h"
#include "spdlog/stopwatch.h"
#include "spdlog/cfg/helpers.h"
