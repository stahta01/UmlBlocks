#include "ClassDialog.hpp"

#include <wx/xrc/xmlres.h>

// Event table
BEGIN_EVENT_TABLE(ClassDialog,wxDialog)
	EVT_CLOSE(								ClassDialog::OnClose)
    EVT_LISTBOX(XRCID("lstVars"),			ClassDialog::OnVarListBox)
    EVT_LISTBOX(XRCID("lstFuncs"),			ClassDialog::OnFuncListBox)
    EVT_LISTBOX(XRCID("lstInherit"),		ClassDialog::OnInheritListBox)
    EVT_LISTBOX(XRCID("lstParams"),			ClassDialog::OnParamsListBox)

    EVT_BUTTON(XRCID("btnCreate"),			ClassDialog::OnCreateBtn)
    EVT_BUTTON(XRCID("btnCancel"),			ClassDialog::OnCancelBtn)
    EVT_BUTTON(XRCID("btnInheritDel"),		ClassDialog::OnInheritDelBtn)
    EVT_BUTTON(XRCID("btnInheritAdd"),		ClassDialog::OnInheritAddBtn)
    EVT_BUTTON(XRCID("btnVarNew"),			ClassDialog::OnVarNewBtn)
    EVT_BUTTON(XRCID("btnVarDel"),			ClassDialog::OnVarDelBtn)
    EVT_BUTTON(XRCID("btnVarUp"),			ClassDialog::OnVarUpBtn)
    EVT_BUTTON(XRCID("btnVarDown"),			ClassDialog::OnVarDownBtn)
    EVT_BUTTON(XRCID("btnFuncNew"),			ClassDialog::OnFuncNewBtn)
    EVT_BUTTON(XRCID("btnFuncDel"),			ClassDialog::OnFuncDelBtn)
    EVT_BUTTON(XRCID("btnFuncUp"),			ClassDialog::OnFuncUpBtn)
    EVT_BUTTON(XRCID("btnFuncDown"),		ClassDialog::OnFuncDownBtn)
    EVT_BUTTON(XRCID("btnParamNew"),		ClassDialog::OnParamNewBtn)
    EVT_BUTTON(XRCID("btnParamDel"),		ClassDialog::OnParamDelBtn)
    EVT_BUTTON(XRCID("btnParamUp"),			ClassDialog::OnParamUpBtn)
    EVT_BUTTON(XRCID("btnParamDown"),		ClassDialog::OnParamDownBtn)

    EVT_CHOICE(XRCID("chcInheritClass"),	ClassDialog::OnInheritChoice)
END_EVENT_TABLE()

ClassDialog::ClassDialog(wxWindow* parent) {
	wxXmlResource::Get()->LoadObject(this,parent,_T("ClassDialog"),_T("wxDialog")); // Loads the entire thing

    // Prepare easy access, sacrificing memrory for performance
    m_lstVars = 			XRCCTRL(*this, "lstVars", 				wxListBox);
    m_lstFuncs = 			XRCCTRL(*this, "lstFuncs", 				wxListBox);
	m_lstInherit = 			XRCCTRL(*this, "lstInherit",			wxListBox);
	m_lstParams = 			XRCCTRL(*this, "lstParams",				wxListBox);

    m_btnCreate = 			XRCCTRL(*this, "btnCreate",				wxButton);
    m_btnCancel = 			XRCCTRL(*this, "btnCancel",				wxButton);
    m_btnInheritDel = 		XRCCTRL(*this, "btnInheritDel",			wxButton);
    m_btnInheritAdd = 		XRCCTRL(*this, "btnInheritAdd",			wxButton);
    m_btnVarNew = 			XRCCTRL(*this, "btnVarsNew",			wxButton);
    m_btnVarDel = 			XRCCTRL(*this, "btnVarsDel",			wxButton);
    m_btnVarUp = 			XRCCTRL(*this, "btnVarsUp",				wxButton);
    m_btnVarDown = 			XRCCTRL(*this, "btnVarsDown",			wxButton);
    m_btnFuncNew = 			XRCCTRL(*this, "btnFuncsNew",			wxButton);
    m_btnFuncDel = 			XRCCTRL(*this, "btnFuncsDel",			wxButton);
    m_btnFuncUp = 			XRCCTRL(*this, "btnFuncsUp",			wxButton);
    m_btnFuncDown = 		XRCCTRL(*this, "btnFuncsDown",			wxButton);
    m_btnParamsNew = 		XRCCTRL(*this, "btnParamsNew",			wxButton);
    m_btnParamsDel = 		XRCCTRL(*this, "btnParamsDel",			wxButton);
    m_btnParamsUp = 		XRCCTRL(*this, "btnParamsUp",			wxButton);
    m_btnParamsDown = 		XRCCTRL(*this, "btnParamsDown",			wxButton);

	m_txtClassName = 		XRCCTRL(*this, "txtClassName",			wxTextCtrl);
	m_txtInheritExtClass = 	XRCCTRL(*this, "txtInheritExtClass",	wxTextCtrl);
	m_txtClassDesc = 		XRCCTRL(*this, "txtClassDesc",			wxTextCtrl);
	m_txtMemberName = 		XRCCTRL(*this, "txtMemberName",			wxTextCtrl);
	m_txtMemberExtType =	XRCCTRL(*this, "txtMemberExtType",		wxTextCtrl);
	m_txtParamsName = 		XRCCTRL(*this, "txtParamsName",			wxTextCtrl);
	m_txtParamsExtType = 	XRCCTRL(*this, "txtParamsExtType",		wxTextCtrl);
	m_txtParamsDefVal = 	XRCCTRL(*this, "txtParamsDefVal",		wxTextCtrl);

	m_chcInheritClass = 	XRCCTRL(*this, "chcInheritClass",		wxChoice);
	m_chcMemberType = 		XRCCTRL(*this, "chcMemberType",			wxChoice);
	m_chcMemberAccess =		XRCCTRL(*this, "chcMemberAccess",		wxChoice);
	m_chcParamsType = 		XRCCTRL(*this, "chcParamsType",			wxChoice);

	m_chkAttAbstract =		XRCCTRL(*this, "chkAttAbstract",		wxCheckBox);
	m_chkMemberArray =		XRCCTRL(*this, "chkMemberArray",		wxCheckBox);
	m_chkMemberStatic =		XRCCTRL(*this, "chkMemberStatic",		wxCheckBox);
	m_chkMemberConst =		XRCCTRL(*this, "chkMemberConst",		wxCheckBox);
	m_chkMemberPointer =	XRCCTRL(*this, "chkMemberPointer",		wxCheckBox);
	m_chkMemberReference =	XRCCTRL(*this, "chkMemberReference",	wxCheckBox);
	m_chkMemberVirtual =	XRCCTRL(*this, "chkMemberVirtual",		wxCheckBox);
	m_chkMemberPVirtual =	XRCCTRL(*this, "chkMemberPVirtual",		wxCheckBox);
	m_chkParamsStatic =		XRCCTRL(*this, "chkParamsStatic",		wxCheckBox);
	m_chkParamsConst =		XRCCTRL(*this, "chkParamsConst",		wxCheckBox);
	m_chkParamsArray =		XRCCTRL(*this, "chkParamsArray",		wxCheckBox);
	m_chkParamsPointer =	XRCCTRL(*this, "chkParamsPointer",		wxCheckBox);
	m_chkParamsReference =	XRCCTRL(*this, "chkParamsReference",	wxCheckBox);

	m_spcMemberArraySize =	XRCCTRL(*this, "spcMemberArraySize",	wxSpinCtrl);
	m_spcMemberPointerDpth =XRCCTRL(*this, "spcMemberPointerDpth",	wxSpinCtrl);
	m_spcParamsPointerDpth =XRCCTRL(*this, "spcParamsPointerDpth",	wxSpinCtrl);

	m_sxtInheritExtClass =	XRCCTRL(*this, "sxtInheritExtClass",	wxStaticText);
	m_sxtMemberExtType =	XRCCTRL(*this, "sxtMemberExtType",		wxStaticText);
	m_sxtMemberArraySize =	XRCCTRL(*this, "sxtMemberArraySize",	wxStaticText);
	m_sxtMemberPointerDpth =XRCCTRL(*this, "sxtMemberPointerDpth",	wxStaticText);
	m_sxtParams =			XRCCTRL(*this, "sxtParams",				wxStaticText);
	m_sxtParamsType =		XRCCTRL(*this, "sxtParamsType",			wxStaticText);
	m_sxtParamsExtType =	XRCCTRL(*this, "sxtParamsExtType",		wxStaticText);
	m_sxtParamsDefVal =		XRCCTRL(*this, "sxtParamsDefVal",		wxStaticText);
	m_sxtParamsPointerDpth =XRCCTRL(*this, "sxtParamsPointerDpth",	wxStaticText);

	// Load Types
	m_chcMemberType->Append(wxT("bool"));
	m_chcMemberType->Append(wxT("char"));
	m_chcMemberType->Append(wxT("unsigned char"));
	m_chcMemberType->Append(wxT("short"));
	m_chcMemberType->Append(wxT("unsigned short"));
	m_chcMemberType->Append(wxT("int"));
	m_chcMemberType->Append(wxT("unsigned int"));
	m_chcMemberType->Append(wxT("long"));
	m_chcMemberType->Append(wxT("unsigned long"));
}

ClassDialog::~ClassDialog() {
}

//-------------------------------------------------
// ***Functions***
//-------------------------------------------------
void ClassDialog::SelectMember(MemberGroup l, int selection) {
	if (l == Variables && m_SelectedMemberList == Functions) {
		m_chcMemberType->Delete(0);
		m_chcMemberType->Delete(0);
	}
	else if (l == Functions && m_SelectedMemberList == Variables){
		m_chcMemberType->Insert(wxT("Constructor"),0);
		m_chcMemberType->Insert(wxT("Destructor"),1);
	}

	m_SelectedMemberList = l;
	m_SelectedMemberItem = selection;

}
void ClassDialog::SelectParameter(int selection) {
	m_SelectedParamItem = selection;
}

void ClassDialog::LoadMember() {
	// Check if there's even anything chosen
	if (m_SelectedMemberItem == -1)
		return; // In that case, don't do anything

	Member* mem;
	if (m_SelectedMemberList == Variables)
		mem = &m_Variables[m_SelectedMemberItem];
	else
		mem = &m_Functions[m_SelectedMemberItem];

	// Setting shared controls
	m_txtMemberName->SetValue(mem->GetName());									// Name

	// The functions can only get ctor and dtor assigned if they're functions anyways,
	// but for the sake of performance, less if's to run through as a variable or something
	if (m_SelectedMemberList == Functions) {
		if (mem->GetType() == wxT("ctor"))
			m_chcMemberType->SetSelection(0);
		else if (mem->GetType() == wxT("dtor"))
			m_chcMemberType->SetSelection(1);
	}
	else																		// Type
		m_chcMemberType->SetSelection(m_chcMemberType->FindString(mem->GetType()));

	m_sxtMemberExtType->Disable();
	m_txtMemberExtType->Disable();
	m_chcMemberAccess->SetSelection(mem->GetAccessLevel());						// Access

	m_chkMemberArray->SetValue(mem->IsArray());									// Array
	m_spcMemberArraySize->SetValue(mem->GetArraySize());
	if (mem->IsArray()) {
	m_sxtMemberArraySize->Enable();
	m_spcMemberArraySize->Enable();
	}
	else {
	m_sxtMemberArraySize->Disable();
	m_spcMemberArraySize->Disable();
	}

	m_chkMemberStatic->SetValue(mem->IsStatic());								// Static
	m_chkMemberConst->SetValue(mem->IsConst());									// Const

	m_chkMemberPointer->Disable();
	m_chkMemberReference->Disable();
	m_spcMemberPointerDpth->Disable();
	m_sxtMemberPointerDpth->Disable();
	if (mem->IsPointer()) {
		m_chkMemberPointer->Enable();
		m_spcMemberPointerDpth->Enable();
		m_sxtMemberPointerDpth->Enable();
	}
	if (mem->IsReference()) {
		m_chkMemberReference->Enable();
	}
	m_chkMemberPointer->SetValue(mem->IsPointer());								// Pointer
	m_spcMemberPointerDpth->SetValue(mem->GetPointerDepth());					// Pointer Depth
	m_chkMemberReference->SetValue(mem->IsReference());							// Reference
	// Variable specifics
	if (m_SelectedMemberList == Variables){
		// Casting
		MemberVar* memv = static_cast<MemberVar*>(mem);

		// Enable/Disabling controls
		m_chkMemberVirtual->Disable();
		m_chkMemberPVirtual->Disable();
		m_sxtParams->Disable();
		m_lstParams->Disable();
		m_btnParamsNew->Disable();
		m_btnParamsDel->Disable();
		m_btnParamsUp->Disable();
		m_btnParamsDown->Disable();
		m_chkParamsPointer->Disable();
		m_sxtParamsPointerDpth->Disable();
		m_spcParamsPointerDpth->Disable();
		m_chkParamsReference->Disable();
		m_sxtParamsName->Disable();
		m_txtParamsName->Disable();
		m_sxtParamsType->Disable();
		m_chcParamsType->Disable();
		m_sxtParamsExtType->Disable();
		m_txtParamsExtType->Disable();
		m_chkParamsArray->Disable();
		m_sxtParamsDefVal->Disable();
		m_txtParamsDefVal->Disable();
		m_chkParamsStatic->Disable();
		m_chkParamsConst->Disable();

		// Set Controls
		m_chkMemberPVirtual->SetValue(false);
		m_lstParams->Clear();
		m_lstParams->SetSelection(-1);
		m_chkParamsPointer->SetValue(false);
		m_spcParamsPointerDpth->SetValue(wxT(""));
		m_chkParamsReference->SetValue(false);
		m_txtParamsName->Clear();
		m_chcParamsType->SetSelection(-1);
		m_txtParamsExtType->Clear();
		m_txtParamsDefVal->Clear();
		m_chkParamsStatic->SetValue(false);
		m_chkParamsConst->SetValue(false);
	}
	// Function specifics
	else{
		// Casting
		MemberFunc* memf = static_cast<MemberFunc*>(mem);

		// Enable/Disabling controls
		m_chkMemberVirtual->Enable();
		m_chkMemberPVirtual->Disable();
		m_sxtParams->Enable();
		m_lstParams->Enable();
		m_btnParamsNew->Enable();
		m_btnParamsDel->Enable();
		m_btnParamsUp->Enable();
		m_btnParamsDown->Enable();
		m_chkParamsPointer->Enable();
		m_sxtParamsPointerDpth->Disable();
		m_spcParamsPointerDpth->Disable();
		m_chkParamsReference->Enable();
		m_sxtParamsName->Enable();
		m_txtParamsName->Enable();
		m_sxtParamsType->Enable();
		m_chcParamsType->Enable();
		m_sxtParamsExtType->Disable();
		m_txtParamsExtType->Disable();
		m_chkParamsArray->Enable();
		m_sxtParamsDefVal->Enable();
		m_txtParamsDefVal->Enable();
		m_chkParamsStatic->Enable();
		m_chkParamsConst->Enable();

		// Set Controls
		// Clear, fill and deselect everything in the Parameters list
		m_lstParams->Clear();
		for (unsigned int i=0; i<memf->GetParameterCount();i++)
			m_lstParams->Append(memf->GetParameter(i).GetName());
		m_lstParams->SetSelection(-1);

		// General function controls
		if (memf->IsVirtual())
		{
			m_chkMemberVirtual->SetValue(memf->IsVirtual());	// Virtual
			m_chkMemberPVirtual->Enable();
		}
		m_chkMemberPVirtual->SetValue(memf->IsPureVirtual());	// Pure Virtual

		// Clearing parameter controls
		m_txtParamsName->Clear();								// Name
		m_chcParamsType->SetSelection(-1);						// Type
		m_txtParamsExtType->Clear();							// Ext Type
		m_txtParamsDefVal->Clear();								// Default Value
		m_chkParamsStatic->SetValue(false);						// Static
		m_chkParamsConst->SetValue(false);						// Const
		m_chkParamsPointer->SetValue(false);					// Pointer
		m_spcParamsPointerDpth->SetValue(wxT(""));				// Pointer Depth
		m_chkParamsReference->SetValue(false);					// Reference
	}
}
void ClassDialog::SaveMember() {
	// Check if there's even anything chosen
	if (m_SelectedMemberItem == -1)
		return; // In that case, don't do anything

	Member* mem;
	if (m_SelectedMemberList == Variables)
		mem = &m_Variables[m_SelectedMemberItem];
	else
		mem = &m_Functions[m_SelectedMemberItem];

	// Save shared controls' values
	mem->SetName(m_txtClassName->GetValue()); 					// Name

	// If we are at the last selection on the list			// Type
	if (m_chcMemberType->GetSelection()+1 == m_chcMemberType->GetCount())
		// And there has been written an external type
		if (!(m_txtMemberExtType->IsEmpty()))
			mem->SetType(m_txtMemberExtType->GetValue()); // use it then
		else // If not, default to int
			mem->SetType(wxT("int"));
	else // So if were not at the last selection
		if (m_SelectedMemberList == Functions) { // Check if we're a function
			// Constructor is first, 0
			if (m_chcMemberType->GetSelection() == 0)
				mem->SetType(wxT("ctor"));
			// Then the destructor, 1
			else if (m_chcMemberType->GetString(m_chcMemberType->GetSelection()) == wxT("Destructor"))
				mem->SetType(wxT("dtor"));
		}
		// If it's not a function, valid function or the last selection,
		// do as expected, use the selected type
		else
			mem->SetType(m_chcMemberType->GetString(m_chcMemberType->GetSelection()));

	switch (m_chcMemberAccess->GetSelection()) {				// Access
	case 0: mem->SetAccessLevel(Public); break;
	case 1: mem->SetAccessLevel(Protected); break;
	case 2: mem->SetAccessLevel(Private); break;
	}
	mem->IsArray(m_chkMemberArray->GetValue());					// Array
	mem->SetArraySize(m_spcMemberArraySize->GetValue());		// Array Size
	mem->IsStatic(m_chkMemberStatic->GetValue()); 				// Static
	mem->IsConst(m_chkMemberConst->GetValue()); 				// Const
	mem->IsPointer(m_chkMemberPointer->GetValue());				// Pointer
	mem->SetPointerDepth(m_spcMemberPointerDpth->GetValue());	// Pointer Depth
	mem->IsReference(m_chkMemberReference->GetValue());			// Reference

	// Variable specifics
	if (m_SelectedMemberList == Variables){
		// Casting
		MemberVar* memv = static_cast<MemberVar*>(mem);
	}
	// Function specifics
	else{
		// Casting
		MemberFunc* memf = static_cast<MemberFunc*>(mem);

		// General function control
		memf->IsVirtual(m_chkMemberVirtual->GetValue());		// Virtual
		memf->IsPureVirtual(m_chkMemberPVirtual->GetValue());	// Pure Virtual

		// Save Selected Parameter
		SaveParameter();
	}
}

void ClassDialog::LoadParameter() {
	// Check if there's even anything chosen
	if (m_SelectedParamItem == -1)
		return; // In that case, don't do anything

	// Fetch parameter to load from
	MemberVar* param = &(m_Functions[m_SelectedMemberItem].GetParameter(m_SelectedParamItem));

	// Set the controls with appropriate info
	m_txtParamsName->SetValue(param->GetName()); 									// Name
	m_chcParamsType->SetSelection(m_chcParamsType->FindString(param->GetType()));	// Type
	m_sxtParamsExtType->Disable();
	m_txtParamsExtType->Disable();
	m_chkParamsArray->SetValue(param->IsArray());				// Array

	m_txtParamsDefVal->SetValue(param->GetDefaultValue());		// Default Value
	m_chkParamsStatic->SetValue(param->IsStatic());				// Static
	m_chkParamsConst->SetValue(param->IsConst());				// Const

	m_chkParamsPointer->Disable();
	m_chkParamsReference->Disable();
	m_spcParamsPointerDpth->Disable();
	m_sxtParamsPointerDpth->Disable();
	if (param->IsPointer()) {
		m_chkParamsPointer->Enable();
		m_spcParamsPointerDpth->Enable();
		m_sxtParamsPointerDpth->Enable();
	}
	if (param->IsReference()) {
		m_chkParamsReference->Enable();
	}
	m_chkParamsPointer->SetValue(param->IsPointer());			// Pointer
	m_spcParamsPointerDpth->SetValue(param->GetPointerDepth());	// Pointer Depth
	m_chkParamsReference->SetValue(param->IsReference());		// Reference
}
void ClassDialog::SaveParameter() {
	// Check if there's even anything chosen
	if (m_SelectedParamItem == -1)
		return; // In that case, don't do anything

	MemberVar* param = &(m_Functions[m_SelectedMemberItem].GetParameter(m_SelectedParamItem));

	// Save control's values
	param->SetName(m_txtParamsName->GetValue()); 				// Name
	if (m_chcParamsType->GetSelection()+1 == m_chcParamsType->GetCount() && !(m_txtParamsExtType->IsEmpty())) // Type
		param->SetType(m_txtParamsExtType->GetValue());
	else
		param->SetType(m_chcParamsType->GetString(m_chcParamsType->GetSelection()));
	param->IsArray(m_chkParamsArray->GetValue());				// Array
	param->SetDefaultValue(m_txtParamsDefVal->GetValue());		// Default Value
	param->IsStatic(m_chkParamsStatic->GetValue());				// Static
	param->IsConst(m_chkParamsConst->GetValue());				// Const
	param->IsPointer(m_chkParamsPointer->GetValue());			// Pointer
	param->SetPointerDepth(m_spcParamsPointerDpth->GetValue());	// Pointer Depth
	param->IsReference(m_chkParamsReference->GetValue());		// Reference
}

void ClassDialog::CreateMember(MemberGroup l) {
	if (l == Variables)	{	// Variables
		MemberVar m;

		m_Variables.push_back(m);
		m_lstVars->Append(m.GetUmlString());
	}
	else {					// Functions
		MemberFunc m;

		m_Functions.push_back(m);
		m_lstFuncs->Append(m.GetUmlString());
	}
}
void ClassDialog::DeleteMember(MemberGroup l, int i) {
	if (l == Variables)	{	// Variables
		m_Variables.erase(m_Variables.begin()+i);
		m_lstVars->Delete(i);
	}
	else {					// Functions
		m_Functions.erase(m_Functions.begin()+i);
		m_lstFuncs->Delete(i);
	}
}
void ClassDialog::CreateParameter() {
m_Functions[m_SelectedMemberItem].AddParameter(MemberVar(wxT("NewParam"))); // Creating the data
m_lstParams->Append(wxT("NewParam")); // Creating the entry
}
void ClassDialog::DeleteParameter(int i) {
m_Functions[m_SelectedMemberItem].DeleteParameter(i); // Deleting the data
m_lstParams->Delete(i); // Deleting the entry
}

//-------------------------------------------------
// ***Events***
//-------------------------------------------------

void ClassDialog::OnVarListBox(wxCommandEvent& event) {
	// Deselect FunctionList
	Manager::Get()->GetLogManager()->Log(_T("Doing Deselects on Func"));
	if (m_lstFuncs->GetSelection() != -1)
		m_lstFuncs->Deselect(m_lstFuncs->GetSelection());

	SaveMember();
	SelectMember(Variables, m_lstVars->GetSelection());
	LoadMember();
}
void ClassDialog::OnFuncListBox(wxCommandEvent& event) {
	// Deselect VarList
	Manager::Get()->GetLogManager()->Log(_T("Doing Deselects on Var"));
	if (m_lstVars->GetSelection() != -1)
		m_lstVars->Deselect(m_lstVars->GetSelection());

	SaveMember();
	SelectMember(Functions, m_lstFuncs->GetSelection());
	LoadMember();
}
void ClassDialog::OnInheritListBox(wxCommandEvent& event) {}
void ClassDialog::OnParamsListBox(wxCommandEvent& event) {
	SaveParameter();
	SelectParameter(m_lstParams->GetSelection());
	LoadParameter();
}

void ClassDialog::OnInheritDelBtn(wxCommandEvent& event){
	if (m_lstInherit->GetSelection() != -1)
		m_lstInherit->Delete(m_lstInherit->GetSelection());
}
void ClassDialog::OnInheritAddBtn(wxCommandEvent& event){
	if (m_chcInheritClass->GetSelection()+1 == m_chcInheritClass->GetCount())
		if (!m_txtInheritExtClass->GetValue().IsEmpty())
			m_lstInherit->Append(m_txtInheritExtClass->GetValue());
	else
		m_lstInherit->Append(m_chcInheritClass->GetString(m_chcInheritClass->GetSelection()));

	m_chcInheritClass->SetSelection(0);
	m_sxtInheritExtClass->Disable();
	m_txtInheritExtClass->Disable();
	m_txtInheritExtClass->SetValue(wxT(""));
}

void ClassDialog::OnVarNewBtn(wxCommandEvent& event){
	CreateMember(Variables);
}
void ClassDialog::OnVarDelBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem != -1) {
		DeleteMember(Variables, m_SelectedMemberItem);

		//if (m_SelectedMemberItem > m_lstVars->GetCount()-1)
		if (m_SelectedMemberItem >= m_lstVars->GetCount()) {
			m_SelectedMemberItem--;
		}
		m_lstVars->SetSelection(m_SelectedMemberItem);
	}
}
void ClassDialog::OnVarUpBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem <= 0 || m_SelectedMemberList == Functions)
		return;
	m_Variables.insert(m_Variables.begin()+m_SelectedMemberItem-1, m_Variables[m_SelectedMemberItem]);
	m_lstVars->Insert(m_lstVars->GetString(m_SelectedMemberItem), m_SelectedMemberItem-1);

	m_Variables.erase(m_Variables.begin()+m_SelectedMemberItem+1);
	m_lstVars->Delete(m_SelectedMemberItem+1);
	m_lstVars->SetSelection(--m_SelectedMemberItem);
}
void ClassDialog::OnVarDownBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem >= m_Variables.size()-1 || m_SelectedMemberList == Functions)
		return;

	if (m_SelectedMemberItem == m_Variables.size()-2){
		m_Variables.push_back(m_Variables[m_SelectedMemberItem]);
		m_lstVars->Append(m_lstVars->GetString(m_SelectedMemberItem));
	}
	else {
		m_Variables.insert(m_Variables.begin()+m_SelectedMemberItem+2, m_Variables[m_SelectedMemberItem]);
		m_lstVars->Insert(m_lstVars->GetString(m_SelectedMemberItem), m_SelectedMemberItem+2);
	}
	m_Variables.erase(m_Variables.begin()+m_SelectedMemberItem);
	m_lstVars->Delete(m_SelectedMemberItem);
	m_lstVars->SetSelection(++m_SelectedMemberItem);
}

void ClassDialog::OnFuncNewBtn(wxCommandEvent& event){
	CreateMember(Functions);
}
void ClassDialog::OnFuncDelBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem != -1) {
		DeleteMember(Functions, m_SelectedMemberItem);

		//if (m_SelectedMemberItem > m_lstFuncs->GetCount()-1)
		if (m_SelectedMemberItem >= m_lstFuncs->GetCount()) {
			m_SelectedMemberItem--;
		}
		m_lstFuncs->SetSelection(m_SelectedMemberItem);
	}
}
void ClassDialog::OnFuncUpBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem <= 0 || m_SelectedMemberList == Variables)
		return;
	m_Functions.insert(m_Functions.begin()+m_SelectedMemberItem-1, m_Functions[m_SelectedMemberItem]);
	m_lstFuncs->Insert(m_lstFuncs->GetString(m_SelectedMemberItem), m_SelectedMemberItem-1);

	m_Functions.erase(m_Functions.begin()+m_SelectedMemberItem+1);
	m_lstFuncs->Delete(m_SelectedMemberItem+1);
	m_lstFuncs->SetSelection(--m_SelectedMemberItem);
}
void ClassDialog::OnFuncDownBtn(wxCommandEvent& event){
	if (m_SelectedMemberItem >= m_Functions.size()-1 || m_SelectedMemberList == Variables)
		return;

	if (m_SelectedMemberItem == m_Functions.size()-2){
		m_Functions.push_back(m_Functions[m_SelectedMemberItem]);
		m_lstFuncs->Append(m_lstFuncs->GetString(m_SelectedMemberItem));
	}
	else {
		m_Functions.insert(m_Functions.begin()+m_SelectedMemberItem+2, m_Functions[m_SelectedMemberItem]);
		m_lstFuncs->Insert(m_lstFuncs->GetString(m_SelectedMemberItem), m_SelectedMemberItem+2);
	}
	m_Functions.erase(m_Functions.begin()+m_SelectedMemberItem);
	m_lstFuncs->Delete(m_SelectedMemberItem);
	m_lstFuncs->SetSelection(++m_SelectedMemberItem);
}

void ClassDialog::OnParamNewBtn(wxCommandEvent& event){
	CreateParameter();
}
void ClassDialog::OnParamDelBtn(wxCommandEvent& event){
	if (m_SelectedParamItem != -1) {
		DeleteParameter(m_SelectedParamItem);

		//if (m_SelectedParamItem > m_lstParams.GetCount()-1)
		if (m_SelectedParamItem >= m_lstParams->GetCount()) {
			m_SelectedParamItem--;
		}
		m_lstParams->SetSelection(m_SelectedParamItem);
	}
}
void ClassDialog::OnParamUpBtn(wxCommandEvent& event){
	std::vector<MemberVar>& Params = m_Functions[m_SelectedParamItem].m_Parameters;

	if (m_SelectedParamItem <= 0)
		return;
	Params.insert(Params.begin()+m_SelectedParamItem-1, Params[m_SelectedParamItem]);
	m_lstParams->Insert(m_lstParams->GetString(m_SelectedParamItem), m_SelectedParamItem-1);

	Params.erase(Params.begin()+m_SelectedParamItem+1);
	m_lstParams->Delete(m_SelectedParamItem+1);
	m_lstParams->SetSelection(--m_SelectedParamItem);
}
void ClassDialog::OnParamDownBtn(wxCommandEvent& event){
	std::vector<MemberVar>& Params = m_Functions[m_SelectedParamItem].m_Parameters;

	if (m_SelectedParamItem >= Params.size()-1)
		return;

	if (m_SelectedParamItem == Params.size()-2){
		Params.push_back(Params[m_SelectedParamItem]);
		m_lstParams->Append(m_lstParams->GetString(m_SelectedParamItem));
	}
	else {
		Params.insert(Params.begin()+m_SelectedParamItem+2, Params[m_SelectedParamItem]);
		m_lstParams->Insert(m_lstParams->GetString(m_SelectedParamItem), m_SelectedParamItem+2);
	}
	Params.erase(Params.begin()+m_SelectedParamItem);
	m_lstParams->Delete(m_SelectedParamItem);
	m_lstParams->SetSelection(++m_SelectedParamItem);
}

void ClassDialog::OnInheritChoice(wxCommandEvent& event){
	if (event.GetSelection()+1 == m_chcInheritClass->GetCount()){
		m_sxtInheritExtClass->Enable();
		m_txtInheritExtClass->Enable();
	}
	else{
		m_sxtInheritExtClass->Disable();
		m_txtInheritExtClass->Disable();
		m_txtInheritExtClass->SetValue(wxT(""));
	}
}

void ClassDialog::OnCreateBtn(wxCommandEvent& event) {
EndModal(wxID_OK);
}
void ClassDialog::OnCancelBtn(wxCommandEvent& event) {
EndModal(wxID_CANCEL);
}

void ClassDialog::OnClose(wxCloseEvent& event){
EndModal(wxID_CLOSE);
}