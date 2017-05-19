/**
 * @file CustomEvent.h
 */
#ifndef _CUSTOMEVENT_H_
#define _CUSTOMEVENT_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

wxDECLARE_EVENT(wxEVT_COMMAND_MONITOR_START, wxThreadEvent); /**< Declare Monitor Start Event */

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_START, wxThreadEvent); /**< Declare Thread Start Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_COMPLETED, wxThreadEvent); /**< Declare Thread Compelete Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE, wxThreadEvent); /**< Declare Thread Update Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_RAW, wxThreadEvent); /**< Declare Thread Update Raw Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY, wxThreadEvent); /**< Declare Thread Update Query Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS, wxThreadEvent); /**< Declare Thread Update Coefficients Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_COOK, wxThreadEvent); /**< Declare Thread Update Cook Event */

wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_CMDNAME, wxThreadEvent); /**< Declare Thread Update CMD Name Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_SUMMARY, wxThreadEvent); /**< Declare Thread Update Summary Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_STDPAGE, wxThreadEvent); /**< Declare Thread Update STD Page Event */
wxDECLARE_EVENT(wxEVT_COMMAND_SENDTHREAD_UPDATE_STATUSPAGE, wxThreadEvent); /**< Declare Thread Update Status Page Event */

wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_START, wxThreadEvent); /**< Declare ISP SEQUENCE START Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_UPDATE, wxThreadEvent); /**< Declare ISP SEQUENCE UPDATE Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_INTERRUPT, wxThreadEvent); /**< Declare ISP SEQUENCE Interrupt Event */
wxDECLARE_EVENT(wxEVT_COMMAND_ISP_SEQUENCE_END, wxThreadEvent); /**< Declare ISP SEQUENCE END Event */

wxDECLARE_EVENT(wxEVT_COMMAND_ISP_PROGRESS_UPDATE, wxThreadEvent); /**< Declare ISP Progress Update Event */

wxDECLARE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_START, wxThreadEvent); /**< Declare QUERY SEQUENCE START Event */
wxDECLARE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_UPDATE, wxThreadEvent); /**< Declare QUERY SEQUENCE UPDATE Event */
wxDECLARE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_INTERRUPT, wxThreadEvent); /**< Declare QUERY SEQUENCE Interrupt Event */
wxDECLARE_EVENT(wxEVT_COMMAND_QUERY_SEQUENCE_END, wxThreadEvent); /**< Declare QUERY SEQUENCE END Event */


wxDECLARE_EVENT(wxEVT_COMMAND_RELOAD_HEX_FILE, wxThreadEvent); /**< Declare Reload HEX File Event */

wxDECLARE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_END, wxThreadEvent); /**< Declare E2PROM Write End Event */
wxDECLARE_EVENT(wxEVT_COMMAND_E2PROM_READ_END, wxThreadEvent); /**< Declare E2PROM Read End Event */

wxDECLARE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT, wxThreadEvent); /**< Declare E2PROM Write Interrupt Event */
wxDECLARE_EVENT(wxEVT_COMMAND_E2PROM_READ_INTERRUPT, wxThreadEvent); /**< Declare E2PROM Read Interrupt Event */

wxDECLARE_EVENT(wxEVT_IOTHREAD_REQ_PAUSE, wxThreadEvent);/**< Declare IO Thread Pause */
wxDECLARE_EVENT(wxEVT_IOTHREAD_REQ_RESUME, wxThreadEvent);/**< Declare IO Thread Resume */

#endif
