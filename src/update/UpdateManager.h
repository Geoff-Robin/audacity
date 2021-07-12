/*!********************************************************************
 Audacity: A Digital Audio Editor

 @file UpdateManager.h
 @brief Declare a class that handles managing of updates.

 Anton Gerasimov
 **********************************************************************/
#pragma once

#include "VersionId.h"
#include "VersionPatch.h"
#include "UpdateDataParser.h"

#include "Prefs.h"

#include <wx/string.h>
#include <wx/event.h>
#include <wx/timer.h>

/// A class that managing of updates.
/**
    Opt-in request and show update dialog by the scheduled time.
    Have a built-in check that allows avoiding multiplying update notifications
    when multiple Audacity windows are shown.
*/
class UpdateManager final : public wxEvtHandler
{
public:
    UpdateManager() = default;

    static UpdateManager& GetInstance();
    static void Start();

    void GetUpdates(bool ignoreNetworkErrors);

    VersionPatch GetVersionPatch() const;

private:
    UpdateDataParser mUpdateDataParser;
    VersionPatch mVersionPatch;

    wxTimer mTimer;

    void OnTimer(wxTimerEvent& event);

    /// Scheduling update time for avoiding multiplying update notifications.
    bool IsTimeForUpdatesChecking();

public:
    DECLARE_EVENT_TABLE()
};
