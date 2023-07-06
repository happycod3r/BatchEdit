#pragma once

public ref class ProcessWin : System::Windows::Forms::Form {
public:
	ProcessWin(System::Diagnostics::Process^ process, System::String^ script_path);
protected:
	~ProcessWin();
private:
	System::ComponentModel::Container^ components;
	void ProcessWin::InitializeComponent(System::Diagnostics::Process^ process, System::String^ script_path);
public:
	System::Diagnostics::Process^ current_process;
	System::Windows::Forms::Label^ start_info;
	System::Windows::Forms::Label^ start_time;
	System::Windows::Forms::Button^ exit_process_btn;

	System::Windows::Forms::ListView^ process_info_list;
	System::Windows::Forms::ListViewItem^ item1;
	System::Windows::Forms::ListViewItem^ item2;
	System::Windows::Forms::ListViewItem^ item3;
	System::Windows::Forms::ListViewItem^ item4;
	System::Windows::Forms::ListViewItem^ item5;
	System::Windows::Forms::ListViewItem^ item6;
	System::Windows::Forms::ListViewItem^ item7;
	System::Windows::Forms::ListViewItem^ item8;
	System::Windows::Forms::ListViewItem^ item9;
	System::Windows::Forms::ListViewItem^ item10;
	System::Windows::Forms::ListViewItem^ item11;
	System::Windows::Forms::ListViewItem^ item12;
	System::Windows::Forms::ListViewItem^ item13;
	System::Windows::Forms::ListViewItem^ item14;
	System::Windows::Forms::ListViewItem^ item15;
	System::Windows::Forms::ListViewItem^ item16;
	System::Windows::Forms::ListViewItem^ item17;
	System::Windows::Forms::ListViewItem^ item18;
	System::Windows::Forms::ListViewItem^ item19;
	System::Windows::Forms::ListViewItem^ item20;
	System::Windows::Forms::ListViewItem^ item21;
	System::Windows::Forms::ListViewItem^ item22;
	System::Windows::Forms::ListViewItem^ item23;
	System::Windows::Forms::ListViewItem^ item24;
	System::Windows::Forms::ListViewItem^ item25;
	System::Windows::Forms::ListViewItem^ item26;
	System::Windows::Forms::ListViewItem^ item27;
	System::Windows::Forms::ListViewItem^ item28;
	System::Windows::Forms::ListViewItem^ item29;
	System::Windows::Forms::ListViewItem^ item30;
	System::Windows::Forms::ListViewItem^ item31;
	System::Windows::Forms::ListViewItem^ item32;
	System::Windows::Forms::ListViewItem^ item33;
	System::Windows::Forms::ListViewItem^ item34;
	void onExitProcessBtnClick(System::Object^ sender, System::EventArgs^ e);
};