
public ref class ScriptRunner {
public:
	ScriptRunner(System::String^ file_path);
protected:
	~ScriptRunner();

	void init(System::String^ file_path);

	int runScript(System::String^ path_to_script);


};