#pragma once

enum ERROR_USER_RESONSE { EXIT = 1,
                                IGNORE = 2 };
enum PROMPT_USER_RESONSE { YES = 1,
                                 NO = 2 };

int ShowFatalDialog(const char *message);
int ShowErrorDialog(const char *message);
int ShowWarningDialog(const char *message);
int ShowInfoDialog(const char *message);
int ShowPrompt(const char *caption, const char *message);
