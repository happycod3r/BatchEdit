#pragma once

// The main window is Autobatch's GUI.
public ref class MainWin : System::Windows::Forms::Form
{
public:

	MainWin();

	~MainWin();

private:

	System::Windows::Forms::MenuStrip^ main_menu;
	System::Windows::Forms::ToolStripMenuItem^ file_menu;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_open;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_new;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_close;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_save;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_save_as;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_restart;
	System::Windows::Forms::ToolStripMenuItem^ file_menu_exit;

	System::Windows::Forms::OpenFileDialog^ open_file_dialog;
	System::Windows::Forms::SaveFileDialog^ save_as_file_dialog;

	System::Windows::Forms::RichTextBox^ txt_input;
	System::Windows::Forms::RichTextBox^ output;
	System::Windows::Forms::RichTextBox^ args_input;
	System::Windows::Forms::RichTextBox^ file_name_output;

	System::Windows::Forms::Button^ save_script_btn;
	System::Windows::Forms::Button^ add_arg_btn;
	System::Windows::Forms::Button^ run_script_btn;

	System::Windows::Forms::ListView^ args_list_view;
	System::Windows::Forms::ListViewItem^ arg_list_item;

	static System::String^ APP_AUTHOR = "Paul McCarthy";
	static System::String^ APP_TITLE = "AutoBatch";
	static System::String^ APP_VERSION = "2.0";
	static System::String^ OUTPUT_PROMPT = ":>> ";
	static System::String^ ARGS_INPUT_DEFAULT_TXT = " Arguments...";
	static System::String^ CURRENT_FILE_PATH = "\0";
	static System::String^ DEFAULT_FILE_NAME = "file";
	static System::String^ DEFAULT_FILE_EXTENSION = ".bat";

	System::String^ getFullyQualifiedDefaultFileName();

	System::IO::File^ current_file = nullptr;
	System::IO::StreamReader^ current_file_reader = nullptr;
	System::IO::StreamWriter^ current_file_writer = nullptr;

	// A visual flag to signal to the user that the file has been modified and should be saved.
	static System::String^ UNSAVED_FILE_CHAR = "*";
	bool fileNameOutputTextHasUnsavedFileCharAtEnd();
	void appendUnsavedFileCharToFileNameOutputText();
	void removeUnsavedFileCharFromFileNameOutputText();
	void setFileNameOutputText(System::String^ file_name);
	System::String^ getFileNameOutputText();
	bool fileNameOutputTextIsEmpty();


	static bool FILE_IS_SAVED = true; // Flag to signal if the current file is saved or not.
	static bool FILE_HAS_BEEN_CREATED = false; // Flag to signal if the current file has been previously created or not.
	static bool FILE_IS_MODIFIED = false; // Flag to signal that the current file has been modified.

	void newFile();
	void showOpenFileDialog();
	void openFile();
	void closeFile();
	void saveFile();
	void showSaveAsFileDialog();
	void saveFileAs();
	void exitApp();
	void restartApp();
	void init();

	void onMainWinShown(System::Object^ sender, System::EventArgs^ e);
	void onMainWinLoad(System::Object^ sender, System::EventArgs^ e);
	void onFileNameOutputTextChanged(System::Object^ sender, System::EventArgs^ e);
	void onFileMenuNewClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuOpenClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuCloseClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuSaveClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuSaveAsClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuRestartClick(System::Object^ sender, System::EventArgs^ ea);
	void onFileMenuExitClick(System::Object^ sender, System::EventArgs^ ea);
	void onTxtInputTextChanged(System::Object^ sender, System::EventArgs^ ea);
	void onOutputTextChanged(System::Object^ sender, System::EventArgs^ ea);
	void onArgsInputTextChanged(System::Object^ sender, System::EventArgs^ ea);
	void onSaveScriptBtnClick(System::Object^ sender, System::EventArgs^ ea);
	void onRunScriptBtnClick(System::Object^ sender, System::EventArgs^ ea);
	void onAddArgBtnClick(System::Object^ sender, System::EventArgs^ ea);
	void onArgsListControlAdded(System::Object^ sender, System::Windows::Forms::ControlEventArgs^ ea);
	void onArgsListControlRemoved(System::Object^ sender, System::Windows::Forms::ControlEventArgs^ ea);
	void onOpenFileDialogFileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ ea);
	void onSaveAsFileDialogFileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ ea);
};
