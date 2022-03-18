#include "stdafx.h"

#include "Dialog.h"

#include "SDL_messagebox.h"

int ShowFatalDialog(const char *message)
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
         1,
         "OK"}};

    const SDL_MessageBoxColorScheme colorScheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {0, 0, 255},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {127, 0, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 255, 255}}};

    const SDL_MessageBoxData mboxData = {
        SDL_MESSAGEBOX_ERROR,
        NULL,
        "FATAL",
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonId = -1;
    if (SDL_ShowMessageBox(&mboxData, &buttonId) < 0)
    {
        std::cout << message << std::endl;
    }

    return buttonId;
}

int ShowErrorDialog(const char *message)
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Exit"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Ignore"}};

    const SDL_MessageBoxColorScheme colorScheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {0, 0, 255},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {127, 0, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 255, 255}}};

    const SDL_MessageBoxData mboxData = {
        SDL_MESSAGEBOX_ERROR,
        NULL,
        "ERROR",
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonId = -1;
    if (SDL_ShowMessageBox(&mboxData, &buttonId) < 0)
    {
        std::cout << message << std::endl;
    }

    return buttonId;
}

int ShowWarningDialog(const char *message)
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
         1,
         "OK"}};

    const SDL_MessageBoxColorScheme colorScheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {255, 127, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 255, 255}}};

    const SDL_MessageBoxData mboxData = {
        SDL_MESSAGEBOX_WARNING,
        NULL,
        "WARNING",
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonId = -1;
    if (SDL_ShowMessageBox(&mboxData, &buttonId) < 0)
    {
        std::cout << message << std::endl;
    }

    return buttonId;
}

int ShowInfoDialog(const char *message)
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
         1,
         "OK"}};

    const SDL_MessageBoxColorScheme colorScheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {0, 0, 255},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {0, 255, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 255, 255}}};

    const SDL_MessageBoxData mboxData = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        "INFO",
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonId = -1;
    if (SDL_ShowMessageBox(&mboxData, &buttonId) < 0)
    {
        std::cout << message << std::endl;
    }

    return buttonId;
}

int ShowPrompt(const char *caption, const char *message)
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
         1,
         "Yes"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
         2,
         "No"}};

    const SDL_MessageBoxColorScheme colorScheme = {
        {/* .colors (.r, .g, .b) */
         /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
         {255, 0, 255},
         /* [SDL_MESSAGEBOX_COLOR_TEXT] */
         {0, 255, 0},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
         {255, 255, 255},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
         {127, 127, 127},
         /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
         {255, 255, 255}}};

    const SDL_MessageBoxData mboxData = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        caption,
        message,
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonId = -1;
    if (SDL_ShowMessageBox(&mboxData, &buttonId) < 0)
    {
        std::cout << message << std::endl;
    }

    return buttonId;
}
