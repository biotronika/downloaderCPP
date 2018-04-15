#pragma once

namespace DownloaderCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Net::Security;
	using namespace System::Security::Cryptography::X509Certificates;
	using namespace System::Text;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	/// <summary>
	/// Podsumowanie informacji o MainFrm
	/// </summary>
	public ref class MainFrm : public System::Windows::Forms::Form
	{
	private:
		String^ adress = "http://biotronika.pl/downloader.php?nodeid=";
		array<String^>^ serialPorts = nullptr;
		static List<String^>^ comPortResults = nullptr;
		List<String^>^ therapy = nullptr;
		bool myError;
		String^ fileName;
		static SerialPort^ _serialPort;

	private: System::Windows::Forms::Label^  lbPort;
	private: System::Windows::Forms::ComboBox^  cbPort;
	private: System::Windows::Forms::Button^  btnDownload;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::TextBox^  tbInformacja;
	private: System::Windows::Forms::LinkLabel^  llBiotronika;
	private: System::Windows::Forms::Timer^  tmClose;


			 StringComparer^ stringComparer;


	public:
		MainFrm(void)
		{
			InitializeComponent();
			myError = false;
			therapy = gcnew List<String^>();
			fileName = Environment::GetCommandLineArgs()[0];
			fileName = System::IO::Path::GetFileNameWithoutExtension(fileName);
			//fileName = "28";
			//tbInformacja->Text = fileName;
			//odczytujemy list� dost�pnych port�w szeregowych			
			ReadComPortList();

			btnDownload->Enabled = !myError;
			tmClose->Enabled = myError;
			if (myError)
			{
				tbInformacja->Text += "\r\nClosing!";
			}
		}

	static bool ValidateServerCertificate(Object^ sender, X509Certificate^ certificate, X509Chain^ chain, SslPolicyErrors sslPolicyErrors)
	{
		return true;
	}

	private: System::Void ReadComPortList()
	{
		try
		{
			// Get a list of serial port names.
			serialPorts = SerialPort::GetPortNames();
			cbPort->Items->Clear();
			for each(String^ port in serialPorts)
			{
				cbPort->Items->Add(port);
			}

			if (cbPort->Items->Count > 0)
			{
				cbPort->SelectedIndex = 0;
			}
			else
			{
				ShowError("No serial ports!");
				myError = true;
			}
		}
		catch (Win32Exception^ ex)
		{
			MessageBox::Show(this, ex->Message, "Error", MessageBoxButtons::OK);
			ShowError(ex->Message);
			myError = true;
		}
	}

	protected:
		/// <summary>
		/// Wyczy�� wszystkie u�ywane zasoby.
		/// </summary>
		~MainFrm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^  pnTop;
	private: System::ComponentModel::IContainer^  components;
	protected:


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Wymagana metoda obs�ugi projektanta � nie nale�y modyfikowa� 
		/// zawarto�� tej metody z edytorem kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pnTop = (gcnew System::Windows::Forms::Panel());
			this->llBiotronika = (gcnew System::Windows::Forms::LinkLabel());
			this->lbPort = (gcnew System::Windows::Forms::Label());
			this->cbPort = (gcnew System::Windows::Forms::ComboBox());
			this->btnDownload = (gcnew System::Windows::Forms::Button());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->tbInformacja = (gcnew System::Windows::Forms::TextBox());
			this->tmClose = (gcnew System::Windows::Forms::Timer(this->components));
			this->pnTop->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnTop
			// 
			this->pnTop->Controls->Add(this->llBiotronika);
			this->pnTop->Controls->Add(this->lbPort);
			this->pnTop->Controls->Add(this->cbPort);
			this->pnTop->Controls->Add(this->btnDownload);
			this->pnTop->Controls->Add(this->btnClose);
			this->pnTop->Dock = System::Windows::Forms::DockStyle::Top;
			this->pnTop->Location = System::Drawing::Point(0, 0);
			this->pnTop->Name = L"pnTop";
			this->pnTop->Size = System::Drawing::Size(667, 45);
			this->pnTop->TabIndex = 1;
			// 
			// llBiotronika
			// 
			this->llBiotronika->AutoSize = true;
			this->llBiotronika->Location = System::Drawing::Point(506, 15);
			this->llBiotronika->Name = L"llBiotronika";
			this->llBiotronika->Size = System::Drawing::Size(68, 13);
			this->llBiotronika->TabIndex = 4;
			this->llBiotronika->TabStop = true;
			this->llBiotronika->Text = L"biotronika.eu";
			this->llBiotronika->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainFrm::llBiotronika_LinkClicked);
			// 
			// lbPort
			// 
			this->lbPort->AutoSize = true;
			this->lbPort->Location = System::Drawing::Point(12, 15);
			this->lbPort->Name = L"lbPort";
			this->lbPort->Size = System::Drawing::Size(29, 13);
			this->lbPort->TabIndex = 3;
			this->lbPort->Text = L"Port:";
			// 
			// cbPort
			// 
			this->cbPort->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPort->FormattingEnabled = true;
			this->cbPort->Location = System::Drawing::Point(47, 12);
			this->cbPort->Name = L"cbPort";
			this->cbPort->Size = System::Drawing::Size(121, 21);
			this->cbPort->TabIndex = 2;
			// 
			// btnDownload
			// 
			this->btnDownload->Location = System::Drawing::Point(174, 12);
			this->btnDownload->Name = L"btnDownload";
			this->btnDownload->Size = System::Drawing::Size(75, 23);
			this->btnDownload->TabIndex = 1;
			this->btnDownload->Text = L"Download";
			this->btnDownload->UseVisualStyleBackColor = true;
			this->btnDownload->Click += gcnew System::EventHandler(this, &MainFrm::btnDownload_Click);
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(580, 10);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(75, 23);
			this->btnClose->TabIndex = 0;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &MainFrm::btnClose_Click);
			// 
			// tbInformacja
			// 
			this->tbInformacja->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tbInformacja->Location = System::Drawing::Point(0, 41);
			this->tbInformacja->Multiline = true;
			this->tbInformacja->Name = L"tbInformacja";
			this->tbInformacja->ReadOnly = true;
			this->tbInformacja->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->tbInformacja->Size = System::Drawing::Size(667, 231);
			this->tbInformacja->TabIndex = 2;
			// 
			// tmClose
			// 
			this->tmClose->Interval = 2000;
			this->tmClose->Tick += gcnew System::EventHandler(this, &MainFrm::tmClose_Tick);
			// 
			// MainFrm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(667, 272);
			this->Controls->Add(this->tbInformacja);
			this->Controls->Add(this->pnTop);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"MainFrm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Downloader - Biotronika.eu";
			this->Shown += gcnew System::EventHandler(this, &MainFrm::MainFrm_Shown);
			this->pnTop->ResumeLayout(false);
			this->pnTop->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
		Close();
	}
	private: System::Void ShowError(String^ message)
	{
		MessageBox::Show(this, message, "Error", MessageBoxButtons::OK);
		tbInformacja->Text += message + "\r\n";
		//tbInformacja->Lines->Add( message );
	}
private: System::Void llBiotronika_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	try
	{
		System::Diagnostics::Process::Start("https://biotronika.pl/");
		llBiotronika->LinkVisited = true;
	}
	catch (Exception^ ex)
	{
		ShowError(ex->Message);
	}
}
private: System::Void tmClose_Tick(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
	private: System::Void getScript()
	{
		System::Net::Security::RemoteCertificateValidationCallback^ clb = gcnew RemoteCertificateValidationCallback(ValidateServerCertificate);
		System::Net::ServicePointManager::ServerCertificateValidationCallback = clb;

		HttpWebRequest^ request = dynamic_cast<HttpWebRequest^>(WebRequest::Create(adress + fileName));

		request->MaximumAutomaticRedirections = 4;
		request->MaximumResponseHeadersLength = 4;

		// Set credentials to use for this request.
		request->Credentials = CredentialCache::DefaultCredentials;
		HttpWebResponse^ response = dynamic_cast<HttpWebResponse^>(request->GetResponse());

		Stream^ receiveStream = response->GetResponseStream();

		StreamReader^ readStream = gcnew StreamReader(receiveStream, Encoding::UTF8);
		String^ linia;
		while (!readStream->EndOfStream)
		{
			linia = readStream->ReadLine();
			tbInformacja->Text += linia + "\r\n";
			therapy->Add(linia);
		}
		if (therapy->Count <= 0)
		{
			ShowError("Invalid therapy");
			tmClose->Enabled = true;
		}

		response->Close();
		readStream->Close();
	}


private: System::Void MainFrm_Shown(System::Object^  sender, System::EventArgs^  e) {
	if (!myError)
	{
		getScript();
	};
}

	private: bool OpenPort(String^ portName)
	{
		bool result = false;
		try
		{
			stringComparer = StringComparer::OrdinalIgnoreCase;
			//readThread = gcnew Thread(gcnew ThreadStart(MainFrm::serialRead));
			_serialPort = gcnew SerialPort(portName);
			_serialPort->BaudRate = 9600;
			_serialPort->Parity = System::IO::Ports::Parity::None;
			_serialPort->DataBits = 8;
			//_serialPort->StopBits = System::IO::Ports::StopBits::None;
			_serialPort->Handshake = System::IO::Ports::Handshake::None;
			_serialPort->ReadTimeout = 500;
			_serialPort->WriteTimeout = 500;
			_serialPort->Open();
			Thread::Sleep(200);
			_serialPort->DtrEnable = true;
			Thread::Sleep(50);
			_serialPort->DtrEnable = false;
			//readThread->Start();				
			result = true;
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(this, ex->Message, "Error", MessageBoxButtons::OK);
			ShowError(ex->Message);
			result = false;
		}
		return(result);
	}

	private: void ClosePort()
	{
		_serialPort->Close();
	}

	private: System::Void serialWrite(String^ line)
	{
		_serialPort->WriteLine(line);
	}


private: System::Void btnDownload_Click(System::Object^  sender, System::EventArgs^  e) {
	//tbInformacja->Text = cbPort->Text;
	if (OpenPort(cbPort->Text))
	{
		tbInformacja->Text = "";

		String^ linia;

		try
		{
			DateTime czas = DateTime::Now;

			while ((DateTime::Now - czas).TotalMilliseconds<2000)
			{
				try
				{
					linia = _serialPort->ReadLine();
				}
				catch (Exception^) {}

				if (linia != "")
				{
					tbInformacja->Text += linia + "\r\n";
					linia = "";
				}
			}

			serialWrite("mem");
			serialWrite("@");

			for (int licznik = 0; licznik < therapy->Count; licznik++)
			{
				linia = therapy[licznik];
				serialWrite("mem @");
				serialWrite(linia);
				serialWrite("@");
				tbInformacja->Text += linia + "\r\n";
				Thread::Sleep(100);
			}
		}
		catch (Exception^) {

		}
		ClosePort();
	}
}
};
}