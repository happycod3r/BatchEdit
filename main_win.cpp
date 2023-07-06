// main_win.cpp

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
using namespace System::Resources;

#include "main_win.h"
#include "process_win.h"
#include "script_process.h"
#include "reference_win.h"
#include "resource.h"

MainWin::MainWin()
{
	InitializeComponent();
}

MainWin::~MainWin()
{
	if (components) {
		delete components;
	}
	if (this)
	{
		file_name_output->TextChanged -= gcnew EventHandler(this, &MainWin::onFileNameOutputTextChanged);
		file_menu_new->Click -= gcnew EventHandler(this, &MainWin::onFileMenuNewClick);
		file_menu_open->Click -= gcnew EventHandler(this, &MainWin::onFileMenuOpenClick);
		file_menu_close->Click -= gcnew EventHandler(this, &MainWin::onFileMenuCloseClick);
		file_menu_save->Click -= gcnew EventHandler(this, &MainWin::onFileMenuSaveClick);
		file_menu_save_as->Click -= gcnew EventHandler(this, &MainWin::onFileMenuSaveAsClick);
		file_menu_restart->Click -= gcnew EventHandler(this, &MainWin::onFileMenuRestartClick);
		file_menu_exit->Click -= gcnew EventHandler(this, &MainWin::onFileMenuExitClick);
		txt_input->TextChanged -= gcnew EventHandler(this, &MainWin::onTxtInputTextChanged);
		output->TextChanged -= gcnew EventHandler(this, &MainWin::onOutputTextChanged);
		save_script_btn->Click -= gcnew EventHandler(this, &MainWin::onSaveScriptBtnClick);
		run_script_btn->Click -= gcnew EventHandler(this, &MainWin::onSaveScriptBtnClick);
		args_input->TextChanged -= gcnew EventHandler(this, &MainWin::onArgsInputTextChanged);
		add_arg_btn->Click -= gcnew EventHandler(this, &MainWin::onSaveScriptBtnClick);
		args_list_view->ControlAdded -= gcnew ControlEventHandler(this, &MainWin::onArgsListControlAdded);
		args_list_view->ControlRemoved -= gcnew ControlEventHandler(this, &MainWin::onArgsListControlRemoved);

		if (open_file_dialog)
		{
			open_file_dialog->FileOk -= gcnew CancelEventHandler(this, &MainWin::onOpenFileDialogFileOk);
		}

		if (save_as_file_dialog)
		{
			save_as_file_dialog->FileOk -= gcnew CancelEventHandler(this, &MainWin::onSaveAsFileDialogFileOk);
		}

	}
}

void MainWin::outputDataReceived(Object^ sender, DataReceivedEventArgs^ e)
{
	if (!String::IsNullOrEmpty(e->Data))
	{
		this->output->AppendText(OUTPUT_PROMPT + e->Data + Environment::NewLine);
	}
}

void  MainWin::runProcess(System::String^ process_name) {
	if (!System::String::IsNullOrEmpty(process_name)) {
		MessageBox::Show(process_name);
		Process^ process = gcnew Process();
		process->StartInfo = gcnew ProcessStartInfo(process_name);
		process->Start();
		ProcessWin^ processForm = (gcnew ProcessWin(process, process_name));
		processForm->Show();
	}
}

void  MainWin::runProcessWithArgs(System::String^ process_name, System::String^ process_args) {
	if (!System::String::IsNullOrEmpty(process_name)) {
		Process^ process = gcnew Process();
		process->StartInfo = gcnew ProcessStartInfo(process_name);
		process->StartInfo->Arguments = process_args;
		process->Start();
		ProcessWin^ processForm = (gcnew ProcessWin(process, process_name));
		processForm->Show();
	}
}

void MainWin::runScript(System::String^ script_path, bool redirect) {
	if (!System::String::IsNullOrEmpty(script_path))
	{
		ScriptProcess^ process = gcnew ScriptProcess();
		process->StartInfo = gcnew ProcessStartInfo(script_path);
		if (redirect) {
			process->StartInfo->RedirectStandardOutput = true;
			process->StartInfo->UseShellExecute = false;
			process->StartInfo->CreateNoWindow = true;
			process->OutputDataReceived += gcnew DataReceivedEventHandler(this, &MainWin::outputDataReceived);
			process->Start();
			process->BeginOutputReadLine();
		}
		else {
			process->StartInfo->RedirectStandardOutput = false;
			process->StartInfo->UseShellExecute = true;
			process->StartInfo->CreateNoWindow = false;
			process->Start();
		}
		ProcessWin^ processForm = (gcnew ProcessWin(process, script_path));
		processForm->Show();
	}
}

void MainWin::runScriptWithArgs(System::String^ script_path, System::String^ script_args, bool redirect) {
	if (!System::String::IsNullOrEmpty(script_path))
	{
		ScriptProcess^ process = gcnew ScriptProcess();
		process->StartInfo = gcnew ProcessStartInfo(script_path);
		if (redirect) {
			process->StartInfo->Arguments = script_args;
			process->StartInfo->UseShellExecute = false;
			process->StartInfo->CreateNoWindow = true;
			process->StartInfo->RedirectStandardOutput = true;
			process->OutputDataReceived += gcnew DataReceivedEventHandler(this, &MainWin::outputDataReceived);
			process->Start();
			process->BeginOutputReadLine();
		}
		else {
			process->StartInfo->Arguments = script_args;
			process->StartInfo->UseShellExecute = true;
			process->StartInfo->CreateNoWindow = false;
			process->StartInfo->RedirectStandardOutput = false;
			process->Start();
		}
		ProcessWin^ processForm = (gcnew ProcessWin(process, script_path));
		processForm->Show();
	}
}

void MainWin::InitializeComponent()
{
	this->SuspendLayout();
	Size = ::Size(600, 500);
	Text = "BatchEdit v1.0.0";
	MaximizeBox = false;
	MinimizeBox = true;
	ShowInTaskbar = true;
	ShowIcon = true;
	Load += gcnew System::EventHandler(this, &MainWin::onMainWinLoad);
	Shown += gcnew System::EventHandler(this, &MainWin::onMainWinShown);

	main_menu = (gcnew MenuStrip());
	main_menu->BackColor = SystemColors::ControlDark;
	main_menu->ForeColor = Color::Black;

	file_menu = (gcnew ToolStripMenuItem("File"));

	file_menu_new = (gcnew ToolStripMenuItem("New"));
	file_menu_new->Click += gcnew EventHandler(this, &MainWin::onFileMenuNewClick);

	file_menu_open = (gcnew ToolStripMenuItem("Open"));
	file_menu_open->Click += gcnew EventHandler(this, &MainWin::onFileMenuOpenClick);

	file_menu_close = (gcnew ToolStripMenuItem("Close"));
	file_menu_close->Click += gcnew EventHandler(this, &MainWin::onFileMenuCloseClick);

	file_menu_save = (gcnew ToolStripMenuItem("Save"));
	file_menu_save->Click += gcnew EventHandler(this, &MainWin::onFileMenuSaveClick);

	file_menu_save_as = (gcnew ToolStripMenuItem("Save as"));
	file_menu_save_as->Click += gcnew EventHandler(this, &MainWin::onFileMenuSaveAsClick);

	file_menu_restart = (gcnew ToolStripMenuItem("Restart"));
	file_menu_restart->Click += gcnew EventHandler(this, &MainWin::onFileMenuRestartClick);

	file_menu_exit = (gcnew ToolStripMenuItem("Exit"));
	file_menu_exit->Click += gcnew EventHandler(this, &MainWin::onFileMenuExitClick);

	array<ToolStripMenuItem^>^ file_menu_items = (gcnew array<ToolStripMenuItem^>(7)
	{
		file_menu_new,
			file_menu_open,
			file_menu_close,
			file_menu_save,
			file_menu_save_as,
			file_menu_restart,
			file_menu_exit
	});

	file_menu->DropDownItems->AddRange(file_menu_items);

	reference_menu = (gcnew ToolStripMenuItem("Reference"));

	reference_menu_cmds = (gcnew ToolStripMenuItem("Commands"));
	reference_menu_cmds->Click += gcnew System::EventHandler(this, &MainWin::onReferenceMenuCmdsClick);

	array<ToolStripMenuItem^>^ reference_menu_items = (gcnew array<ToolStripMenuItem^>(1) {
		reference_menu_cmds
	});

	reference_menu->DropDownItems->AddRange(reference_menu_items);

	array<ToolStripMenuItem^>^ main_menu_items = (gcnew array<ToolStripMenuItem^>(2)
	{
		file_menu,
			reference_menu
	});

	main_menu->Items->AddRange(main_menu_items);

	file_name_output = (gcnew RichTextBox());
	file_name_output->Location = Point(2, 26);
	file_name_output->Size = ::Size(580, 20);
	file_name_output->AcceptsTab = false;
	file_name_output->DetectUrls = true;
	file_name_output->Enabled = true;
	file_name_output->Font = (gcnew ::Font("Segoi UI", 10.0, FontStyle::Bold));
	file_name_output->MaxLength = INT_MAX;
	file_name_output->Multiline = true;
	file_name_output->ReadOnly = true;
	file_name_output->BorderStyle = ::BorderStyle::None;
	file_name_output->BackColor = SystemColors::ControlDarkDark;
	file_name_output->ForeColor = Color::WhiteSmoke;
	file_name_output->ShortcutsEnabled = true;
	file_name_output->Text = getFullyQualifiedDefaultFileName();
	file_name_output->TextChanged += gcnew System::EventHandler(this, &MainWin::onFileNameOutputTextChanged);

	txt_input = (gcnew RichTextBox());
	txt_input->Location = Point(2, 48);
	txt_input->Size = ::Size(583, 300);//583, 300
	txt_input->BorderStyle = ::BorderStyle::None;
	txt_input->AcceptsTab = true;
	txt_input->DetectUrls = false;
	txt_input->Enabled = true;
	txt_input->Font = (gcnew ::Font("Segoi UI", 10.0, FontStyle::Regular));
	txt_input->MaxLength = INT_MAX;
	txt_input->Multiline = true;
	txt_input->BackColor = SystemColors::ControlDark; //SystemColors::ControlLight;
	txt_input->ForeColor = Color::Black;
	txt_input->TextChanged += gcnew EventHandler(this, &MainWin::onTxtInputTextChanged);

	output = (gcnew RichTextBox());
	output->Location = Point(1, 350);
	output->Size = ::Size(404, 59);
	output->AcceptsTab = false;
	output->DetectUrls = true;
	output->Enabled = true;
	output->Font = (gcnew ::Font("Segoi UI", 10.0, FontStyle::Regular));
	output->MaxLength = INT_MAX;
	output->Multiline = true;
	output->Text = OUTPUT_PROMPT;
	output->ReadOnly = true;
	output->BorderStyle = ::BorderStyle::Fixed3D;
	output->BackColor = SystemColors::ControlDark;
	output->ForeColor = Color::Black;
	output->TextChanged += gcnew EventHandler(this, &MainWin::onOutputTextChanged);

	save_script_btn = (gcnew Button());
	save_script_btn->Location = Point(2, 409);
	save_script_btn->Size = ::Size(60, 26);
	save_script_btn->Text = "Save Script";
	save_script_btn->FlatStyle = ::FlatStyle::Popup;
	save_script_btn->BackColor = SystemColors::ControlLight;
	save_script_btn->ForeColor = Color::Black;
	save_script_btn->Click += gcnew EventHandler(this, &MainWin::onSaveScriptBtnClick);

	run_script_btn = (gcnew Button());
	run_script_btn->Location = Point(60, 409);
	run_script_btn->Size = ::Size(60, 26);
	run_script_btn->Text = "Run Script";
	run_script_btn->FlatStyle = ::FlatStyle::Popup;
	run_script_btn->BackColor = SystemColors::ControlLight;
	run_script_btn->ForeColor = Color::Black;
	run_script_btn->Click += gcnew EventHandler(this, &MainWin::onRunScriptBtnClick);

	args_input = (gcnew RichTextBox());
	args_input->Location = Point(180, 409);
	args_input->Size = ::Size(222, 25);
	args_input->AcceptsTab = false;
	args_input->DetectUrls = true;
	args_input->Enabled = true;
	args_input->Font = (gcnew ::Font("Segoi UI", 10.0, FontStyle::Regular));
	args_input->MaxLength = 512;
	args_input->Multiline = false;
	args_input->Text = ARGS_INPUT_DEFAULT_TXT;
	args_input->BorderStyle = ::BorderStyle::None;
	args_input->BackColor = SystemColors::ControlDark;
	args_input->ForeColor = Color::Black;
	args_input->RichTextShortcutsEnabled = true;
	args_input->TextChanged += gcnew EventHandler(this, &MainWin::onArgsInputTextChanged);

	clear_output_btn = (gcnew Button());
	clear_output_btn->Location = Point(120, 409);
	clear_output_btn->Size = ::Size(60, 26);
	clear_output_btn->Text = "";
	clear_output_btn->FlatStyle = ::FlatStyle::Popup;
	clear_output_btn->BackColor = SystemColors::Control;
	clear_output_btn->ForeColor = Color::Black;
	clear_output_btn->Click += gcnew EventHandler(this, &MainWin::onClearOutputBtnClick);

	add_arg_btn = (gcnew Button());
	add_arg_btn->Location = Point(404, 409);
	add_arg_btn->Size = ::Size(60, 26);
	add_arg_btn->Text = "Add arg";
	add_arg_btn->FlatStyle = ::FlatStyle::Popup;
	add_arg_btn->BackColor = SystemColors::Control;
	add_arg_btn->ForeColor = Color::Black;
	add_arg_btn->Click += gcnew EventHandler(this, &MainWin::onAddArgBtnClick);

	args_list_view = (gcnew ListView());
	args_list_view->Location = Drawing::Point(464, 375);
	args_list_view->Size = Drawing::Size(125, 87);
	args_list_view->BackColor = SystemColors::ControlDark;
	args_list_view->ForeColor = Color::Black;
	args_list_view->Alignment = ListViewAlignment::Top;
	args_list_view->View = System::Windows::Forms::View::Details;
	args_list_view->Columns->Add("Arguments", 100);
	args_list_view->ControlAdded += gcnew ControlEventHandler(this, &MainWin::onArgsListControlAdded);
	args_list_view->ControlRemoved += gcnew ControlEventHandler(this, &MainWin::onArgsListControlRemoved);

	redirect_proc_output_checkbox = (gcnew CheckBox());
	redirect_proc_output_checkbox->Size = Drawing::Size(40, 20);
	redirect_proc_output_checkbox->Location = Drawing::Point(410, 350);
	redirect_proc_output_checkbox->CheckState = CheckState::Checked;
	redirect_proc_output_checkbox->Text = "In";
	redirect_proc_output_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MainWin::onRedirectProcCheckedChanged);
	redirect_proc_output_checkbox->BackColor = SystemColors::Control;

	alt_process_input = (gcnew RichTextBox());
	alt_process_input->Size = ::Size(115, 25);
	alt_process_input->Location = ::Point(468, 348);
	alt_process_input->Font = (gcnew ::Font("Segoi UI", 10.0, FontStyle::Regular));
	alt_process_input->TextChanged += gcnew System::EventHandler(this, &MainWin::onRunAltProcessTextBoxTextChanged);

	alt_process_checkbox = (gcnew CheckBox());
	alt_process_checkbox->Size = Drawing::Size(40, 20);
	alt_process_checkbox->Location = Drawing::Point(410, 380);
	alt_process_checkbox->CheckState = CheckState::Unchecked;
	alt_process_checkbox->Text = "Alt";
	alt_process_checkbox->BackColor = SystemColors::Control;
	alt_process_checkbox->CheckedChanged += gcnew System::EventHandler(this, &MainWin::onRunAltProcessCheckBoxCheckedChanged);

	array<Control^>^ ctrls = (gcnew array<Control^>(14)
	{
		main_menu,
			file_name_output,
			txt_input,
			output,
			save_script_btn,
			run_script_btn,
			args_input,
			clear_output_btn,
			add_arg_btn,
			args_list_view,
			redirect_proc_output_checkbox,
			alt_process_input,
			alt_process_checkbox
	});

	Controls->AddRange(ctrls);

	this->ResumeLayout(false);
	this->PerformLayout();
}

void MainWin::onMainWinShown(Object^ sender, EventArgs^ ea)
{
	txt_input->Focus();
}

void MainWin::onMainWinLoad(Object^ sender, EventArgs^ ea)
{

}

String^ MainWin::getFullyQualifiedDefaultFileName()
{
	return (DEFAULT_FILE_NAME + DEFAULT_FILE_EXTENSION);
}

void MainWin::setFileNameOutputText(String^ file_name)
{
	file_name_output->Text = file_name;
}

String^ MainWin::getFileNameOutputText()
{
	return file_name_output->Text;
}

bool MainWin::fileNameOutputTextIsEmpty()
{
	if (file_name_output->TextLength == 0)
	{
		return true;
	}
	return false;
}

bool MainWin::fileNameOutputTextHasUnsavedFileCharAtEnd()
{
	if (getFileNameOutputText()->EndsWith("*"))
	{
		return true;
	}
	return false;
}

void MainWin::appendUnsavedFileCharToFileNameOutputText()
{
	FILE_IS_MODIFIED = true;
	FILE_IS_SAVED = false;
	if (!fileNameOutputTextHasUnsavedFileCharAtEnd())
	{
		setFileNameOutputText(getFileNameOutputText() + UNSAVED_FILE_CHAR);
	}

}

void MainWin::removeUnsavedFileCharFromFileNameOutputText()
{
	FILE_IS_MODIFIED = false;
	FILE_IS_SAVED = true;
	if (fileNameOutputTextHasUnsavedFileCharAtEnd())
	{
		String^ file_name = getFileNameOutputText();
		String^ file_name_with_unsaved_file_char_removed = file_name->Replace("*", "");
		setFileNameOutputText(file_name_with_unsaved_file_char_removed);
	}
}

void MainWin::onFileNameOutputTextChanged(Object^ sender, EventArgs^ ea)
{

}

void MainWin::onFileMenuNewClick(Object^ sender, EventArgs^ ea)
{
	if (!FILE_IS_SAVED)
	{
		if (::DialogResult::Yes == MessageBox::Show("Your current file is unsaved!. Would you like to save before creating a new file?", "Save?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button1, MessageBoxOptions::DefaultDesktopOnly))
		{
			saveFile();
		}
	}
	newFile();
}

void MainWin::newFile()
{
	CURRENT_FILE_PATH = getFullyQualifiedDefaultFileName();
	setFileNameOutputText(CURRENT_FILE_PATH);
	txt_input->ResetText();
	FILE_HAS_BEEN_CREATED = false;
	// Note to future self:
	// resetting a rich text box's text triggers the 'onTextChanged()' event  since
	// input is being removed from the control. This then in turn causes the 'UNSAVED_FILE_CHAR'
	// to be added to the end of the file name in the 'file_name_output' control as well
	// as causes the 'FILE_IS_MODIFIED' flag to be raised. In order to get around this we
	// have to reset 'FILE_IS_MODIFIED' to false and set 'FILE_IS_SAVED' to false since a new
	// file is not yet saved. Thirdly we then have to remove the 'UNSAVED_FILE_CHAR' from the file name. 
	// All of this can be achieved in one shot by simply making a call to the 
	// 'removeUnsavedFileCharFromFileNameOutputText()' function which does all 3.
	removeUnsavedFileCharFromFileNameOutputText();
}

void MainWin::onFileMenuOpenClick(Object^ sender, EventArgs^ ea)
{
	if (!FILE_IS_SAVED)
	{
		if (::DialogResult::Yes == MessageBox::Show("Your current file is unsaved!. Would you like to save before opening a new file?", "Save?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2, MessageBoxOptions::DefaultDesktopOnly))
		{
			saveFile();
		}
	}
	showOpenFileDialog();
}

void MainWin::showOpenFileDialog()
{
	open_file_dialog = (gcnew OpenFileDialog());
	open_file_dialog->Filter = "Batch script files (*.bat)|*.bat|Text files (*.txt)|*.txt|All files (*.*)|*.*";
	open_file_dialog->DefaultExt = DEFAULT_FILE_EXTENSION;
	open_file_dialog->FileOk += gcnew CancelEventHandler(this, &MainWin::onOpenFileDialogFileOk);
	open_file_dialog->RestoreDirectory = true;
	open_file_dialog->InitialDirectory = "C://Users//";
	open_file_dialog->CheckPathExists = true;
	open_file_dialog->CheckFileExists = true;
	open_file_dialog->ShowDialog();
}

void MainWin::onOpenFileDialogFileOk(Object^ sender, CancelEventArgs^ ea)
{
	openFile();
}

void MainWin::openFile()
{
	CURRENT_FILE_PATH = open_file_dialog->FileName;
	setFileNameOutputText(CURRENT_FILE_PATH);
	txt_input->LoadFile(CURRENT_FILE_PATH, RichTextBoxStreamType::PlainText);
	FILE_HAS_BEEN_CREATED = true;
	// Loading the file into a rich text box triggers the 'onTextChanged()' event  since
	// input is being entered into the control. This then in turn causes the 'UNSAVED_FILE_CHAR'
	// to be added to the end of the file name in the 'file_name_output' control as well
	// as causes the 'FILE_IS_MODIFIED' flag to be raised even though the file has not
	// been modified, and has only just been loaded. In order to get around this we
	// have to reset 'FILE_IS_MODIFIED' to false and set 'FILE_IS_SAVED' to true since opening a file implies that 
	// it has been previously created and saved, so it would be considered saved. Thirdly we then 
	// have to remove the 'UNSAVED_FILE_CHAR' from the file name. All of this can be achieved in 
	// one shot by simply making a call to the 'removeUnsavedFileCharFromFileNameOutputText()' 
	// function which does all 3.
	removeUnsavedFileCharFromFileNameOutputText();
}

void MainWin::onFileMenuCloseClick(Object^ sender, EventArgs^ ea)
{
	if (!FILE_IS_SAVED)
	{
		if (::DialogResult::Yes == MessageBox::Show("Your current file is unsaved!. Would you like to save before closing the file?", "Save?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button1, MessageBoxOptions::DefaultDesktopOnly))
		{
			saveFile();
		}
	}
	closeFile();
}

void MainWin::closeFile()
{
	CURRENT_FILE_PATH = getFullyQualifiedDefaultFileName();
	setFileNameOutputText(CURRENT_FILE_PATH);
	txt_input->ResetText();
	FILE_HAS_BEEN_CREATED = false;
	// Loading the file into a rich text box triggers the 'onTextChanged()' event  since
	// input is being entered into the control. This then in turn causes the 'UNSAVED_FILE_CHAR'
	// to be added to the end of the file name in the 'file_name_output' control as well
	// as causes the 'FILE_IS_MODIFIED' flag to be raised even though the file has not
	// been modified, and has only just been loaded. In order to get around this we
	// have to reset 'FILE_IS_MODIFIED' to false and set 'FILE_IS_SAVED' to true since opening a file implies that 
	// it has been previously created and saved, so it would be considered saved. Thirdly we then 
	// have to remove the 'UNSAVED_FILE_CHAR' from the file name. All of this can be achieved in 
	// one shot by simply making a call to the 'removeUnsavedFileCharFromFileNameOutputText()' 
	// function which does all 3.
	removeUnsavedFileCharFromFileNameOutputText();
}

void MainWin::onFileMenuSaveClick(Object^ sender, EventArgs^ ea)
{
	saveFile();
}

void MainWin::saveFile()
{
	if (FILE_IS_MODIFIED)
	{
		if (FILE_HAS_BEEN_CREATED)
		{
			txt_input->SaveFile(CURRENT_FILE_PATH, RichTextBoxStreamType::PlainText);
			removeUnsavedFileCharFromFileNameOutputText();
			FILE_IS_MODIFIED = false;
			FILE_HAS_BEEN_CREATED = true;
			FILE_IS_SAVED = true;
		}
		else
		{
			showSaveAsFileDialog();
		}
	}
}

void MainWin::onFileMenuSaveAsClick(Object^ sender, EventArgs^ ea)
{
	showSaveAsFileDialog();
}

void MainWin::showSaveAsFileDialog()
{
	save_as_file_dialog = (gcnew SaveFileDialog());
	save_as_file_dialog->Filter = "Batch script files (*.bat)|*.bat|Text files (*.txt)|*.txt|All files (*.*)|*.*";
	save_as_file_dialog->FileOk += gcnew CancelEventHandler(this, &MainWin::onSaveAsFileDialogFileOk);
	save_as_file_dialog->DefaultExt = DEFAULT_FILE_EXTENSION;
	save_as_file_dialog->RestoreDirectory = true;
	save_as_file_dialog->InitialDirectory = "C://Users//";
	save_as_file_dialog->ShowDialog();
}

void MainWin::onSaveAsFileDialogFileOk(Object^ sender, CancelEventArgs^ ea)
{
	saveFileAs();
}

void MainWin::saveFileAs()
{
	CURRENT_FILE_PATH = save_as_file_dialog->FileName;
	setFileNameOutputText(CURRENT_FILE_PATH);
	txt_input->SaveFile(CURRENT_FILE_PATH, RichTextBoxStreamType::PlainText);
	removeUnsavedFileCharFromFileNameOutputText();
	FILE_IS_MODIFIED = false;
	FILE_HAS_BEEN_CREATED = true;
	FILE_IS_SAVED = true;

}

void MainWin::onFileMenuRestartClick(Object^ sender, EventArgs^ ea)
{
	if (::DialogResult::Yes == MessageBox::Show("Are you sure you want to restart?", "Restart?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2, MessageBoxOptions::DefaultDesktopOnly))
	{
		restartApp();
	}
}

void MainWin::restartApp()
{
	if (!FILE_IS_SAVED)
	{
		if (::DialogResult::Yes == MessageBox::Show("Your current file is unsaved!. Would you like to save before restarting?", "Save?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2, MessageBoxOptions::DefaultDesktopOnly))
		{
			saveFile();
		}
	}
	Application::Restart();
}

void MainWin::onFileMenuExitClick(Object^ sender, EventArgs^ ea)
{
	if (::DialogResult::Yes == MessageBox::Show("Are you sure you would like to exit", "Exit?", MessageBoxButtons::YesNo, MessageBoxIcon::Question,
		MessageBoxDefaultButton::Button2, MessageBoxOptions::DefaultDesktopOnly))
	{
		exitApp();
	}
}

void MainWin::exitApp()
{
	if (!FILE_IS_SAVED)
	{
		if (::DialogResult::Yes == MessageBox::Show("Your current file is unsaved!. Would you like to save before Exiting?", "Save?", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2, MessageBoxOptions::DefaultDesktopOnly))
		{
			saveFile();
		}
	}
	Application::Exit();
}

void MainWin::onTxtInputTextChanged(Object^ sender, EventArgs^ ea)
{
	appendUnsavedFileCharToFileNameOutputText();
}

void MainWin::onOutputTextChanged(Object^ sender, EventArgs^ ea)
{

}

void MainWin::onArgsInputTextChanged(Object^ sender, EventArgs^ ea)
{
	SCRIPT_ARGS = this->args_input->Text;
}

void MainWin::onSaveScriptBtnClick(Object^ sender, EventArgs^ ea)
{
	saveFile();
}

void MainWin::onRunScriptBtnClick(Object^ sender, EventArgs^ ea)
{
	if (!RUN_ALT_PROCESS) {
		String^ ALL_SCRIPT_ARGS = "";
		for (int i = 0; i < this->args_list_view->Items->Count; i++) {
			ALL_SCRIPT_ARGS += this->args_list_view->Items[i]->Text;
		}
		saveFile();
		// If there is no arguments...
		if (ALL_SCRIPT_ARGS == "" || System::String::IsNullOrEmpty(ALL_SCRIPT_ARGS)) {
			if (REDIRECT_PROC_OUTPUT == true) {
				this->runScript(CURRENT_FILE_PATH, true);
			}
			else {
				this->runScript(CURRENT_FILE_PATH, false);
			}
		}
		// If there are arguments...
		else {
			if (REDIRECT_PROC_OUTPUT == true) {
				this->runScriptWithArgs(CURRENT_FILE_PATH, ALL_SCRIPT_ARGS, true);
			}
			else {
				this->runScriptWithArgs(CURRENT_FILE_PATH, ALL_SCRIPT_ARGS, false);
			}
		}
	}
	else {
		String^ ALL_SCRIPT_ARGS = "";
		for (int i = 0; i < this->args_list_view->Items->Count; i++) {
			ALL_SCRIPT_ARGS += this->args_list_view->Items[i]->Text;
		}
		if (ALL_SCRIPT_ARGS == "" || System::String::IsNullOrEmpty(ALL_SCRIPT_ARGS)) {
			runProcess(ALT_PROCESS_NAME);
		}
		else {
			runProcessWithArgs(ALT_PROCESS_NAME, ALL_SCRIPT_ARGS);
		}
	}
}

void MainWin::onClearOutputBtnClick(Object^ sender, EventArgs^ ea)
{
	this->output->Clear();
}

void MainWin::onAddArgBtnClick(Object^ sender, EventArgs^ ea)
{
	ListViewItem^ arg_list_item = gcnew ListViewItem();
	arg_list_item->Text = SCRIPT_ARGS + " ";
	arg_list_item->BackColor = SystemColors::Control;
	arg_list_item->Font = (gcnew ::Font("Consolas", 10.0, FontStyle::Regular));

	this->args_input->Clear();

	this->args_list_view->Items->Add(arg_list_item);
}

void MainWin::onArgsListControlAdded(Object^ sender, ControlEventArgs^ ea)
{

}

void MainWin::onArgsListControlRemoved(Object^ sender, ControlEventArgs^ ea)
{

}

void MainWin::onRedirectProcCheckedChanged(System::Object^ sender, System::EventArgs^ ea) {
	bool checked_state = this->redirect_proc_output_checkbox->Checked;
	if (checked_state) {
		REDIRECT_PROC_OUTPUT = true;
		this->redirect_proc_output_checkbox->Text = "In";
	}
	else {
		REDIRECT_PROC_OUTPUT = false;
		this->redirect_proc_output_checkbox->Text = "Ex";
	}
}

void MainWin::onRunAltProcessTextBoxTextChanged(System::Object^ sender, System::EventArgs^ e)
{
	ALT_PROCESS_NAME = this->alt_process_input->Text;
}

void MainWin::onRunAltProcessCheckBoxCheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	bool checked_state = this->alt_process_checkbox->Checked;
	if (checked_state) {
		this->RUN_ALT_PROCESS = true;
	}
	else {
		this->RUN_ALT_PROCESS = false;
	}
}

void MainWin::onReferenceMenuCmdsClick(System::Object^ sender, System::EventArgs^ e)
{
	ReferenceWin^ reference_win = (gcnew ReferenceWin());
	reference_win->Show();
}
