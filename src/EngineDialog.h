/*
 * Engine.h - Engine Control Unit dialog
 *
 * Copyright (C) 2008-2012 Comer352L
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENGINEDIALOG_H
#define ENGINEDIALOG_H


#ifdef __WIN32__
	#include "windows\serialCOM.h"
#elif defined __linux__
	#include "linux/serialCOM.h"
#else
	#error "Operating system not supported !"
#endif
#include <QtGui>
#include "ControlUnitDialog.h"
#include "CUinfo_Engine.h"
#include "CUcontent_DCs_engine.h"
#include "CUcontent_MBsSWs.h"
#include "CUcontent_Adjustments.h"
#include "CUcontent_sysTests.h"
#include "ClearMemoryDlg.h"
#include "FSSMdialogs.h"
#include "AbstractDiagInterface.h"
#include "SSMprotocol.h"
#include "MBsSWsListeners.h"



class EngineDialog : public ControlUnitDialog
{
	Q_OBJECT

public:
    EngineDialog(AbstractDiagInterface *diagInterface,
                 QString language,
                 bool isMBsSWsReportingEnabled,
                 MBsSWsListeners& aMBsSWsListeners,
                 std::vector< std::pair<std::string, int> >* aMBsSWsConfiguration);

private:
	enum mode_dt {DCs_mode=1, MBsSWs_mode=2, Adaptions_mode=3, SysTests_mode};

	// Content backup parameters:
	std::vector<MBSWmetadata_dt> _lastMBSWmetaList;
	MBSWsettings_dt _MBSWsettings;
	// Selection buttons:
	QPushButton *_clearMemory_pushButton;
	// Info- and content-widgets:
	CUinfo_Engine *_infoWidget;
	CUcontent_DCs_engine *_content_DCs;
	CUcontent_MBsSWs *_content_MBsSWs;
	CUcontent_Adjustments *_content_Adjustments;
	// Current content/mode:
	mode_dt _mode;
    MBsSWsListeners& _MBsSWsListeners;

	void setup();
	void saveContentSettings();

private slots:
	void DCs();
    void measuringblocks(bool isMBsSWsReportingEnabled = false, std::vector< std::pair<std::string, int> >* aMBsSWsConfiguration = NULL);
	void adjustments();
	void systemoperationtests();
	void clearMemory();

};



#endif
