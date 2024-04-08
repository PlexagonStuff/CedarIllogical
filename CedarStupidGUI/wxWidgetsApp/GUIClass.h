///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 30 2011)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUICLASS_H__
#define __GUICLASS_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class GUIClass
///////////////////////////////////////////////////////////////////////////////
class GUIClass : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText4;
		wxFilePickerCtrl* m_filePicker1;
		wxStaticText* m_staticText1;
		wxFilePickerCtrl* m_filePicker11;
		wxStaticText* m_staticText11;
		wxButton* startbutton;
		wxTextCtrl* simulationspace;
		
		// Virtual event handlers, overide them in your derived class
		virtual void CircuitFileAdded( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void VectorFileAdded( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void StartSimulation( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIClass( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CedarStupid"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~GUIClass();
	
};

#endif //__GUICLASS_H__
