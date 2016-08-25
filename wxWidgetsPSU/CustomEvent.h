/**
 * @file CustomEvent.h
 */
#ifndef _CUSTOMEVENT_H_
#define _CUSTOMEVENT_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_START, wxThreadEvent); /**< Declare Thread Start Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent); /**< Declare Thread Compelete Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent); /**< Declare Thread Update Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW, wxThreadEvent); /**< Declare Thread Update Raw Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_COOK, wxThreadEvent); /**< Declare Thread Update Cook Event */

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_CMDNAME, wxThreadEvent); /**< Declare Thread Update CMD Name Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_SUMMARY, wxThreadEvent); /**< Declare Thread Update Summary Event */

wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_START, wxThreadEvent); /**< Declare ISP SEQUENCE START Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_UPDATE, wxThreadEvent); /**< Declare ISP SEQUENCE UPDATE Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, wxThreadEvent); /**< Declare ISP SEQUENCE Interrupt Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_END, wxThreadEvent); /**< Declare ISP SEQUENCE END Event */

wxDECLARE_EVENT(wxEVT_COMMAND_ISP_PROGRESS_UPDATE, wxThreadEvent); /**< Declare ISP Progress Update Event */

#endif