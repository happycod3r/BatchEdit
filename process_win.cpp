#include <cstdlib>
#using <mscorlib.dll>
#using <System.dll>	 
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Diagnostics;

#include "process_win.h"

ProcessWin::ProcessWin(System::Diagnostics::Process^ process, System::String^ script_path) {
	InitializeComponent(process, script_path);
}

ProcessWin::~ProcessWin() {
	if (components) {
		delete components;
	}
}

void ProcessWin::InitializeComponent(System::Diagnostics::Process^ process, System::String^ script_path) {
	this->SuspendLayout();

	this->start_time = gcnew Label();
	start_time->Size = Drawing::Size(500, 50);
	start_time->Location = Drawing::Point(0, 0);
	start_time->Text = "Start Time: " + process->StartTime.ToString();
	start_time->BackColor = SystemColors::ControlDark;
	start_time->Padding = System::Windows::Forms::Padding(8, 12, 8, 8);
	start_time->Font = (gcnew Drawing::Font("Segoi UI", 14.0, FontStyle::Bold));;

	this->start_info = gcnew Label();
	start_info->Size = Drawing::Size(400, 550);
	start_info->Location = Drawing::Point(600, 0);
	start_info->Padding = System::Windows::Forms::Padding(8, 8, 8, 8);
	start_info->Text =
		"Start Info: " + process->StartInfo + Environment::NewLine +
		"Arguments: " + process->StartInfo->Arguments + Environment::NewLine +
		"File Name: " + process->StartInfo->FileName + Environment::NewLine +
		"Working Directory: " + process->StartInfo->WorkingDirectory + Environment::NewLine +
		"Username: " + process->StartInfo->UserName + Environment::NewLine +
		"Use Shell Execute: " + process->StartInfo->UseShellExecute + Environment::NewLine +
		"Verb: " + process->StartInfo->Verb + Environment::NewLine +
		"Verbs: " + process->StartInfo->Verbs + Environment::NewLine +
		"Environment Variables: " + process->StartInfo->EnvironmentVariables + Environment::NewLine +
		"Environment: " + process->StartInfo->Environment + Environment::NewLine +
		"Std Output Encoding: " + process->StartInfo->StandardOutputEncoding;
	start_info->BackColor = SystemColors::ControlDark;
	start_info->Font = (gcnew Drawing::Font("Segoi UI", 12.0, FontStyle::Regular));

	this->process_info_list = (gcnew ListView());
	this->process_info_list->View = View::Details;
	this->process_info_list->Size = Drawing::Size(600, 550);
	this->process_info_list->Alignment = ListViewAlignment::Left;
	this->process_info_list->BackColor = SystemColors::ControlDark;
	this->process_info_list->Location = Drawing::Point(0, 50);
	this->process_info_list->Font = (gcnew Drawing::Font("Consolas", 12.0, FontStyle::Regular));
	this->process_info_list->Columns->Add("Process Info", 1000);

	ListViewItem^ item1 = gcnew ListViewItem();
	item1->Text = "Process Name: " + process->ProcessName;
	item1->BackColor = SystemColors::ControlDark;
	item1->ForeColor = Drawing::Color::Black;
	item1->UseItemStyleForSubItems = true;

	ListViewItem^ item2 = gcnew ListViewItem();
	item2->Text = "Process Id: " + process->Id.ToString();
	item2->BackColor = SystemColors::ControlDark;
	item2->ForeColor = Drawing::Color::Black;
	item2->UseItemStyleForSubItems = true;

	ListViewItem^ item3 = gcnew ListViewItem();
	item3->Text = "Process Handle: " + process->Handle;
	item3->BackColor = SystemColors::ControlDark;
	item3->ForeColor = Drawing::Color::Black;
	item3->UseItemStyleForSubItems = true;

	ListViewItem^ item4 = gcnew ListViewItem();
	item4->Text = "Handle Count: " + process->HandleCount;
	item4->BackColor = SystemColors::ControlDark;
	item4->ForeColor = Drawing::Color::Black;
	item4->UseItemStyleForSubItems = true;

	ListViewItem^ item5 = gcnew ListViewItem();
	item5->Text = "Base Priority: " + process->BasePriority.ToString();
	item5->BackColor = SystemColors::ControlDark;
	item5->ForeColor = Drawing::Color::Black;
	item5->UseItemStyleForSubItems = true;

	ListViewItem^ item6 = gcnew ListViewItem();
	item6->Text = "Machine Name: " + process->MachineName;
	item6->BackColor = SystemColors::ControlDark;
	item6->ForeColor = Drawing::Color::Black;
	item6->UseItemStyleForSubItems = true;

	ListViewItem^ item7 = gcnew ListViewItem();
	item7->Text = "Main Module: " + process->MainModule;
	item7->BackColor = SystemColors::ControlDark;
	item7->ForeColor = Drawing::Color::Black;
	item7->UseItemStyleForSubItems = true;

	ListViewItem^ item8 = gcnew ListViewItem();
	item8->Text = "Main Win Handle: " + process->MainWindowHandle;
	item8->BackColor = SystemColors::ControlDark;
	item8->ForeColor = Drawing::Color::Black;
	item8->UseItemStyleForSubItems = true;

	ListViewItem^ item9 = gcnew ListViewItem();
	item9->Text = "Main Win Title: " + process->MainWindowTitle;
	item9->BackColor = SystemColors::ControlDark;
	item9->ForeColor = Drawing::Color::Black;
	item9->UseItemStyleForSubItems = true;

	ListViewItem^ item10 = gcnew ListViewItem();
	item10->Text = "Max Working Set: " + process->MaxWorkingSet;
	item10->BackColor = SystemColors::ControlDark;
	item10->ForeColor = Drawing::Color::Black;
	item10->UseItemStyleForSubItems = true;

	ListViewItem^ item11 = gcnew ListViewItem();
	item11->Text = "Min Working Set: " + process->MinWorkingSet;
	item11->BackColor = SystemColors::ControlDark;
	item11->ForeColor = Drawing::Color::Black;
	item11->UseItemStyleForSubItems = true;

	ListViewItem^ item12 = gcnew ListViewItem();
	item12->Text = "Loaded Modules: " + process->Modules;
	item12->BackColor = SystemColors::ControlDark;
	item12->ForeColor = Drawing::Color::Black;
	item12->UseItemStyleForSubItems = true;
	/*for each (ProcessModule ^ module in process->Modules) {
		ListViewItem^ moduleItem = gcnew ListViewItem(module->ModuleName);
		moduleItem->SubItems->Add(module->FileName);
		moduleItem->SubItems->Add(module->FileVersionInfo->FileVersion);
		process_info_list->Items->Add(moduleItem);
	}*/

	ListViewItem^ item13 = gcnew ListViewItem();
	item13->Text = "Non-Paged Sys. Mem. Size: " + process->NonpagedSystemMemorySize;
	item13->BackColor = SystemColors::ControlDark;
	item13->ForeColor = Drawing::Color::Black;
	item13->UseItemStyleForSubItems = true;

	ListViewItem^ item14 = gcnew ListViewItem();
	item14->Text = "Non-Paged Sys. Mem. Size64: " + process->NonpagedSystemMemorySize64;
	item14->BackColor = SystemColors::ControlDark;
	item14->ForeColor = Drawing::Color::Black;
	item14->UseItemStyleForSubItems = true;

	ListViewItem^ item15 = gcnew ListViewItem();
	item15->Text = "Paged Memory Size: " + process->PagedMemorySize;
	item15->BackColor = SystemColors::ControlDark;
	item15->ForeColor = Drawing::Color::Black;
	item15->UseItemStyleForSubItems = true;

	ListViewItem^ item16 = gcnew ListViewItem();
	item16->Text = "Paged Memory Size64: " + process->PagedMemorySize64;
	item16->BackColor = SystemColors::ControlDark;
	item16->ForeColor = Drawing::Color::Black;
	item16->UseItemStyleForSubItems = true;

	ListViewItem^ item17 = gcnew ListViewItem();
	item17->Text = "Paged System Memory Size: " + process->PagedSystemMemorySize;
	item17->BackColor = SystemColors::ControlDark;
	item17->ForeColor = Drawing::Color::Black;
	item17->UseItemStyleForSubItems = true;

	ListViewItem^ item18 = gcnew ListViewItem();
	item18->Text = "Paged System Memory Size64: " + process->PagedSystemMemorySize64;
	item18->BackColor = SystemColors::ControlDark;
	item18->ForeColor = Drawing::Color::Black;
	item18->UseItemStyleForSubItems = true;

	ListViewItem^ item19 = gcnew ListViewItem();
	item19->Text = "Peak Paged Memory Size: " + process->PeakPagedMemorySize;
	item19->BackColor = SystemColors::ControlDark;
	item19->ForeColor = Drawing::Color::Black;
	item19->UseItemStyleForSubItems = true;

	ListViewItem^ item20 = gcnew ListViewItem();
	item20->Text = "Peak Paged Memory Size64: " + process->PeakPagedMemorySize64;
	item20->BackColor = SystemColors::ControlDark;
	item20->ForeColor = Drawing::Color::Black;
	item20->UseItemStyleForSubItems = true;
	/////////

	ListViewItem^ item21 = gcnew ListViewItem();
	item21->Text = "Peak Virtual Memory Size: " + process->PeakVirtualMemorySize;
	item21->BackColor = SystemColors::ControlDark;
	item21->ForeColor = Drawing::Color::Black;
	item21->UseItemStyleForSubItems = true;

	ListViewItem^ item22 = gcnew ListViewItem();
	item22->Text = "Peak Virtual Memory Size64: " + process->PeakVirtualMemorySize64;
	item22->BackColor = SystemColors::ControlDark;
	item22->ForeColor = Drawing::Color::Black;
	item22->UseItemStyleForSubItems = true;

	ListViewItem^ item23 = gcnew ListViewItem();
	item23->Text = "Peak Working Set: " + process->PeakWorkingSet;
	item23->BackColor = SystemColors::ControlDark;
	item23->ForeColor = Drawing::Color::Black;
	item23->UseItemStyleForSubItems = true;

	ListViewItem^ item24 = gcnew ListViewItem();
	item24->Text = "Peak Working Set64: " + process->PeakWorkingSet64;
	item24->BackColor = SystemColors::ControlDark;
	item24->ForeColor = Drawing::Color::Black;
	item24->UseItemStyleForSubItems = true;

	ListViewItem^ item25 = gcnew ListViewItem();
	item25->Text = "Priority Boost Enabled: " + process->PriorityBoostEnabled;
	item25->BackColor = SystemColors::ControlDark;
	item25->ForeColor = Drawing::Color::Black;
	item25->UseItemStyleForSubItems = true;

	ListViewItem^ item26 = gcnew ListViewItem();
	item26->Text = "Priority Class: " + process->PriorityClass.ToString();
	item26->BackColor = SystemColors::ControlDark;
	item26->ForeColor = Drawing::Color::Black;
	item26->UseItemStyleForSubItems = true;

	ListViewItem^ item27 = gcnew ListViewItem();
	item27->Text = "Private Memory Size: " + process->PrivateMemorySize;
	item27->BackColor = SystemColors::ControlDark;
	item27->ForeColor = Drawing::Color::Black;
	item27->UseItemStyleForSubItems = true;

	ListViewItem^ item28 = gcnew ListViewItem();
	item28->Text = "Private Memory Size64: " + process->PrivateMemorySize64;
	item28->BackColor = SystemColors::ControlDark;
	item28->ForeColor = Drawing::Color::Black;
	item28->UseItemStyleForSubItems = true;

	ListViewItem^ item29 = gcnew ListViewItem();
	item29->Text = "Privaleged Processor Time: " + process->PrivilegedProcessorTime;
	item29->BackColor = SystemColors::ControlDark;
	item29->ForeColor = Drawing::Color::Black;
	item29->UseItemStyleForSubItems = true;

	ListViewItem^ item30 = gcnew ListViewItem();
	item30->Text = "Processor Affinity: " + process->ProcessorAffinity;
	item30->BackColor = SystemColors::ControlDark;
	item30->ForeColor = Drawing::Color::Black;
	item30->UseItemStyleForSubItems = true;

	ListViewItem^ item31 = gcnew ListViewItem();
	item31->Text = "Process Safe Handle: " + process->SafeHandle;
	item31->BackColor = SystemColors::ControlDark;
	item31->ForeColor = Drawing::Color::Black;
	item31->UseItemStyleForSubItems = true;

	ListViewItem^ item32 = gcnew ListViewItem();
	item32->Text = "Session Id: " + process->SessionId;
	item32->BackColor = SystemColors::ControlDark;
	item32->ForeColor = Drawing::Color::Black;
	item32->UseItemStyleForSubItems = true;

	ListViewItem^ item33 = gcnew ListViewItem();
	item33->Text = "Process Site: " + process->Site;
	item33->BackColor = SystemColors::ControlDark;
	item33->ForeColor = Drawing::Color::Black;
	item33->UseItemStyleForSubItems = true;

	ListViewItem^ item34 = gcnew ListViewItem();
	item34->Text = "Synchronizing Object: " + process->SynchronizingObject;
	item34->BackColor = SystemColors::ControlDark;
	item34->ForeColor = Drawing::Color::Black;
	item34->UseItemStyleForSubItems = true;

	this->process_info_list->Items->Add(item1);
	this->process_info_list->Items->Add(item2);
	this->process_info_list->Items->Add(item3);
	this->process_info_list->Items->Add(item4);
	this->process_info_list->Items->Add(item5);
	this->process_info_list->Items->Add(item6);
	this->process_info_list->Items->Add(item7);
	this->process_info_list->Items->Add(item8);
	this->process_info_list->Items->Add(item9);
	this->process_info_list->Items->Add(item10);
	this->process_info_list->Items->Add(item11);
	this->process_info_list->Items->Add(item12);
	this->process_info_list->Items->Add(item13);
	this->process_info_list->Items->Add(item14);
	this->process_info_list->Items->Add(item15);
	this->process_info_list->Items->Add(item16);
	this->process_info_list->Items->Add(item17);
	this->process_info_list->Items->Add(item18);
	this->process_info_list->Items->Add(item19);
	this->process_info_list->Items->Add(item20);
	this->process_info_list->Items->Add(item21);
	this->process_info_list->Items->Add(item22);
	this->process_info_list->Items->Add(item23);
	this->process_info_list->Items->Add(item24);
	this->process_info_list->Items->Add(item25);
	this->process_info_list->Items->Add(item26);
	this->process_info_list->Items->Add(item27);
	this->process_info_list->Items->Add(item28);
	this->process_info_list->Items->Add(item29);
	this->process_info_list->Items->Add(item30);
	this->process_info_list->Items->Add(item31);
	this->process_info_list->Items->Add(item32);
	this->process_info_list->Items->Add(item33);
	this->process_info_list->Items->Add(item34);

	/*this->process_info_list->Items->AddRange(gcnew array<ListViewItem^>(2) {
		item1,
			item2
	});*/

	this->Text = process->Id.ToString();
	this->Size = Drawing::Size(1000, 550);
	this->Controls->AddRange(gcnew array<Control^>(3)
	{
		this->start_info,
			this->start_time,
			this->process_info_list
	});
	this->ResumeLayout(false);
	this->PerformLayout();
}