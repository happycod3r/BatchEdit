#pragma once

public ref class ReferenceWin : System::Windows::Forms::Form
{
public:

	ReferenceWin();

protected:

	~ReferenceWin();

private:
	System::ComponentModel::Component^ components;
	System::Windows::Forms::WebBrowser^ reference_browser;
	System::Windows::Forms::Button^ forward;
	System::Windows::Forms::Button^ back;

	void InitializeComponent();
	void onReferenceWinLoad(System::Object^ sender, System::EventArgs^ e);
	void onForwardBtnClick(System::Object^ sender, System::EventArgs^ e);
	void onBackBtnClick(System::Object^ sender, System::EventArgs^ e);
};