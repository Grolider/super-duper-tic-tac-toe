#pragma once
#include "msclr\marshal_cppstd.h"
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>

SOCKET Connection;
char id[10];
char key;
int count;//переменна€  дл€ счЄта строк в сообщении об игроках
std::string _key;
std::string text;
char* list[100];

#pragma warning(disable: 4996)
namespace Reform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			ClientHandlerThread = gcnew Thread(gcnew ThreadStart(this, &MyForm::ClientHandler));
			ClientHandlerThread->IsBackground = true;
			ClientHandlerThread->Start();
		}


		void Update() {

			cell1->Visible = false;
			cell2->Visible = false;
			cell3->Visible = false;
			cell4->Visible = false;
			cell5->Visible = false;
			cell6->Visible = false;
			cell7->Visible = false;
			cell8->Visible = false;
			cell9->Visible = false;
			BackButton->Visible = false;

			NameLabel->Visible = false;
			IPLabel->Visible = false;
			NameTextBox->Visible = false;
			IPTextBox->Visible = false;
			RegistrationButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;
			label3->Visible = false;

			listBox1->Visible = true;
			InviteButton->Visible = true;

			listBox1->Items->Clear();
			for (int i = 0; i < count; i++) {

				text = list[i];
				listBox1->Items->Add(gcnew System::String(text.c_str()));

			}
			//toolStripStatusLabel1->Text = "";
		}

		void PlayerDisconnected() {
			Update();
			text = "Connection with player ";
			text += id;
			text += " failed";
			toolStripStatusLabel1->Text = msclr::interop::marshal_as<String^>(text);
		}

		void Invitation() {
			listBox1->Visible = false;
			label3->Visible = false;
			InviteButton->Visible = false;

			NoButton->Visible = true;
			YesButton->Visible = true;

			text = "Player ";
			text += id;
			text += " invited you to game";
			label3->Text= msclr::interop::marshal_as<String^>(text);
			label3->Visible = true;
			toolStripStatusLabel1->Text = "New invitation";
		}

		void RefusedInvitation() {
			Update();
			text = "Player ";
			text += id;
			text += " refused your invitation";
			toolStripStatusLabel1->Text = msclr::interop::marshal_as<String^>(text);
		}

		void GameStart() {
			NameLabel->Visible = false;
			IPLabel->Visible = false;
			NameTextBox->Visible = false;
			IPTextBox->Visible = false;
			RegistrationButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;
			label3->Visible = false;
			listBox1->Visible = false;
			InviteButton->Visible = false;
			BackButton->Visible = false;

			cell1->Text = "";
			cell2->Text = "";
			cell3->Text = "";
			cell4->Text = "";
			cell5->Text = "";
			cell6->Text = "";
			cell7->Text = "";
			cell8->Text = "";
			cell9->Text = "";

			cell1->Visible = true;
			cell2->Visible = true;
			cell3->Visible = true;
			cell4->Visible = true;
			cell5->Visible = true;
			cell6->Visible = true;
			cell7->Visible = true;
			cell8->Visible = true;
			cell9->Visible = true;



		}

		void YourMoveMSG() {
			toolStripStatusLabel1->Text = "Your move";
		}

		void OpponentMoveMSG() {
			toolStripStatusLabel1->Text = "Opponent move...";
		}

		void WrongMoveMSG() {
			toolStripStatusLabel1->Text = "Wrong Move, try again.";
		}

		void YourMoveView() {
			switch (key) {
			case 'a':
				cell1->ForeColor = Color::SkyBlue;
				cell1->Text = "X";
				break;
			case 'b':
				cell2->ForeColor = Color::SkyBlue;
				cell2->Text = "X";
				break;
			case 'c':
				cell3->ForeColor = Color::SkyBlue;
				cell3->Text = "X";
				break;
			case 'd':
				cell4->ForeColor = Color::SkyBlue;
				cell4->Text = "X";
				break;
			case 'e':
				cell5->ForeColor = Color::SkyBlue;
				cell5->Text = "X";
				break;
			case 'f':
				cell6->ForeColor = Color::SkyBlue;
				cell6->Text = "X";
				break;
			case 'g':
				cell7->ForeColor = Color::SkyBlue;
				cell7->Text = "X";
				break;
			case 'h':
				cell8->ForeColor = Color::SkyBlue;
				cell8->Text = "X";
				break;
			case 'i':
				cell9->ForeColor = Color::SkyBlue;
				cell9->Text = "X";
				break;
			}
			OpponentMoveMSG();
		}

		void OpponentMoveView() {
			switch (key) {
			case 'a':
				cell1->ForeColor = Color::Crimson;
				cell1->Text = "O";
				break;
			case 'b':
				cell2->ForeColor = Color::Crimson;
				cell2->Text = "O";
				break;
			case 'c':
				cell3->ForeColor = Color::Crimson;
				cell3->Text = "O";
				break;
			case 'd':
				cell4->ForeColor = Color::Crimson;
				cell4->Text = "O";
				break;
			case 'e':
				cell5->ForeColor = Color::Crimson;
				cell5->Text = "O";
				break;
			case 'f':
				cell6->ForeColor = Color::Crimson;
				cell6->Text = "O";
				break;
			case 'g':
				cell7->ForeColor = Color::Crimson;
				cell7->Text = "O";
				break;
			case 'h':
				cell8->ForeColor = Color::Crimson;
				cell8->Text = "O";
				break;
			case 'i':
				cell9->ForeColor = Color::Crimson;
				cell9->Text = "O";
				break;
			}
			YourMoveMSG();
		}

		void VictoryMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "VICTORY!";
		}

		void DefeatMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "DEFEAT";
		}

		void DrawMSG() {
			BackButton->Visible = true;
			toolStripStatusLabel1->Text = "DRAW";
		}

		void Disconnect() {
			NameLabel->Visible = true;
			IPLabel->Visible = true;
			NameTextBox->Visible = true;
			IPTextBox->Visible = true;
			RegistrationButton->Visible = true;

			listBox1->Visible = false;
			label3->Visible = false;
			InviteButton->Visible = false;
			NoButton->Visible = false;
			YesButton->Visible = false;

			toolStripStatusLabel1->Text = "Connection failed";
		}

		int iResult = 0;
		//функци€ дл€ обработки сообщений с сервера
		void ClientHandler() {

			char msg[2500];
			char code[2] = "";

			int n;//переменна€ дл€ исправного считывани€ сообщени€ по символам
			int size;//переменна€ размера отправл€емого сообщени€
			char msg_c[10];
			while (true) {
				if (iResult > 0) {
					while (iResult > 0) {
						iResult = recv(Connection, msg, 2500, NULL);
						strncpy(code, msg, 2);
						switch (atoi(code))
						{
						case 2://код списка игроков
							n = 1;
							for (int i = 0; i < 100; i++) {
								count = i;
								if (msg[n + 1] == '\n') break;
								if (n == sizeof(msg)) break;
								list[i] = new char[25];
								strcpy(list[i], "");
								for (int j = n + 1; j < sizeof(msg); j++) {
									if (msg[j] == '\n') {
										n = j;
										break;
									}
									strncat(list[i], msg + j, 1);
									if (msg[j] == '\0') {
										j = sizeof(msg);
										n = j;
									}
								}
							}
							if (iResult > 0) {
								if (this->InvokeRequired) {
									this->Invoke(gcnew Action(this, &MyForm::Update));
								}
								else {
									Update();
								}
							}
							break;

						case 3://код ошибки соединени€ с игроком
							strcpy(id, msg + 2);

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "84", 2);
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "02", 2);
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::PlayerDisconnected));
							}
							else {
								PlayerDisconnected();
							}

							break;

						case 13://код приглашени€ игрока
							strcpy(id, msg + 2);
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::Invitation));
							}
							else {
								Invitation();
							}
							break;

						case 23://код ответа на приглашение
							strcpy(id, msg + 2);
							break;

						case 33://код отказа на приглашение
							strcpy(id, msg + 2);
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::RefusedInvitation));
							}
							else {
								RefusedInvitation();
							}
							break;

						case 4://код подключени€ к игре
							iResult = send(Connection, msg, sizeof(msg), NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::GameStart));
							}
							else {
								GameStart();
							}
							break;

						case 14://код хода игрока
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::YourMoveMSG));
							}
							else {
								YourMoveMSG();
							}
							break;

						case 24://код хода оппонента
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::OpponentMoveMSG));
							}
							else {
								OpponentMoveMSG();
							}
							break;

						case 34://код неправильного хода
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::WrongMoveMSG));
							}
							else {
								WrongMoveMSG();
							}
							break;

						case 44://код отображени€ хода оппонента
							key = msg[2];

							memset(msg_c, '\0', 10);
							strncpy(msg_c, "74", 2);
							_key = key;
							strcat(msg_c, _key.c_str());
							size = strlen(msg_c) + 1;
							send(Connection, msg_c, size, NULL);

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::OpponentMoveView));
							}
							else {
								OpponentMoveView();
							}
							break;

						case 54://код победы
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::VictoryMSG));
							}
							else {
								VictoryMSG();
							}
							break;

						case 64://код поражени€
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::DefeatMSG));
							}
							else {
								DefeatMSG();
							}

							break;

						case 94://код ничьей
							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::DrawMSG));
							}
							else {
								DrawMSG();
							}

							break;

						case 5://код подтверждени€ хода игрока
							key = msg[2];

							if (this->InvokeRequired) {
								this->Invoke(gcnew Action(this, &MyForm::YourMoveView));
							}
							else {
								YourMoveView();
							}
							break;

						default:
							break;
						}
					}
					if (this->InvokeRequired) {
						this->Invoke(gcnew Action(this, &MyForm::Disconnect));
					}
					else {
						Disconnect();
					}
				}
			}
			
		}
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			delete ClientHandlerThread;
			if (components)
			{
				delete components;
			}
		}
private: System::Windows::Forms::Button^ RegistrationButton;
private: System::Windows::Forms::TextBox^ IPTextBox;

private: System::Windows::Forms::TextBox^ NameTextBox;

private: System::Windows::Forms::Label^ IPLabel;

private: System::Windows::Forms::Label^ NameLabel;

private: System::Windows::Forms::Button^ InviteButton;


	private: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::ListBox^ listBox1;
private: System::Windows::Forms::Button^ NoButton;

private: System::Windows::Forms::Button^ YesButton;

	private: System::Windows::Forms::Button^ cell9;


	private: System::Windows::Forms::Button^ cell8;

	private: System::Windows::Forms::Button^ cell6;

	private: System::Windows::Forms::Button^ cell5;
	private: System::Windows::Forms::Button^ cell7;


	private: System::Windows::Forms::Button^ cell4;

	private: System::Windows::Forms::Button^ cell3;

	private: System::Windows::Forms::Button^ cell2;

	private: System::Windows::Forms::Button^ cell1;

	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;

private: System::Windows::Forms::Button^ BackButton;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->RegistrationButton = (gcnew System::Windows::Forms::Button());
			this->IPTextBox = (gcnew System::Windows::Forms::TextBox());
			this->NameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->IPLabel = (gcnew System::Windows::Forms::Label());
			this->NameLabel = (gcnew System::Windows::Forms::Label());
			this->InviteButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->NoButton = (gcnew System::Windows::Forms::Button());
			this->YesButton = (gcnew System::Windows::Forms::Button());
			this->cell9 = (gcnew System::Windows::Forms::Button());
			this->cell8 = (gcnew System::Windows::Forms::Button());
			this->cell6 = (gcnew System::Windows::Forms::Button());
			this->cell5 = (gcnew System::Windows::Forms::Button());
			this->cell7 = (gcnew System::Windows::Forms::Button());
			this->cell4 = (gcnew System::Windows::Forms::Button());
			this->cell3 = (gcnew System::Windows::Forms::Button());
			this->cell2 = (gcnew System::Windows::Forms::Button());
			this->cell1 = (gcnew System::Windows::Forms::Button());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->BackButton = (gcnew System::Windows::Forms::Button());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// RegistrationButton
			// 
			this->RegistrationButton->BackColor = System::Drawing::Color::Transparent;
			this->RegistrationButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->RegistrationButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->RegistrationButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->RegistrationButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->RegistrationButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->RegistrationButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->RegistrationButton->Location = System::Drawing::Point(127, 305);
			this->RegistrationButton->Name = L"RegistrationButton";
			this->RegistrationButton->Size = System::Drawing::Size(203, 49);
			this->RegistrationButton->TabIndex = 9;
			this->RegistrationButton->Text = L"Registration";
			this->RegistrationButton->UseVisualStyleBackColor = false;
			this->RegistrationButton->Click += gcnew System::EventHandler(this, &MyForm::RegistrationButton_Click);
			// 
			// IPTextBox
			// 
			this->IPTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPTextBox->Location = System::Drawing::Point(104, 219);
			this->IPTextBox->Name = L"IPTextBox";
			this->IPTextBox->Size = System::Drawing::Size(262, 31);
			this->IPTextBox->TabIndex = 8;
			// 
			// NameTextBox
			// 
			this->NameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NameTextBox->Location = System::Drawing::Point(104, 123);
			this->NameTextBox->Name = L"NameTextBox";
			this->NameTextBox->Size = System::Drawing::Size(262, 31);
			this->NameTextBox->TabIndex = 7;
			this->NameTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::NameTextBox_KeyPress_1);
			// 
			// IPLabel
			// 
			this->IPLabel->AutoSize = true;
			this->IPLabel->BackColor = System::Drawing::Color::Transparent;
			this->IPLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IPLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->IPLabel->Location = System::Drawing::Point(210, 178);
			this->IPLabel->Name = L"IPLabel";
			this->IPLabel->Size = System::Drawing::Size(40, 31);
			this->IPLabel->TabIndex = 6;
			this->IPLabel->Text = L"IP";
			// 
			// NameLabel
			// 
			this->NameLabel->AutoSize = true;
			this->NameLabel->BackColor = System::Drawing::Color::Transparent;
			this->NameLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->NameLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->NameLabel->Location = System::Drawing::Point(188, 74);
			this->NameLabel->Name = L"NameLabel";
			this->NameLabel->Size = System::Drawing::Size(86, 31);
			this->NameLabel->TabIndex = 5;
			this->NameLabel->Text = L"Name";
			// 
			// InviteButton
			// 
			this->InviteButton->BackColor = System::Drawing::Color::Transparent;
			this->InviteButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->InviteButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->InviteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->InviteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->InviteButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->InviteButton->Location = System::Drawing::Point(194, 382);
			this->InviteButton->Name = L"InviteButton";
			this->InviteButton->Size = System::Drawing::Size(92, 36);
			this->InviteButton->TabIndex = 13;
			this->InviteButton->Text = L"Invite";
			this->InviteButton->UseVisualStyleBackColor = false;
			this->InviteButton->Visible = false;
			this->InviteButton->Click += gcnew System::EventHandler(this, &MyForm::InviteButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label3->Location = System::Drawing::Point(50, 232);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 25);
			this->label3->TabIndex = 11;
			this->label3->Text = L"*empty*";
			this->label3->Visible = false;
			// 
			// listBox1
			// 
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 20;
			this->listBox1->Location = System::Drawing::Point(88, 12);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(306, 364);
			this->listBox1->TabIndex = 10;
			this->listBox1->Visible = false;
			// 
			// NoButton
			// 
			this->NoButton->BackColor = System::Drawing::Color::Transparent;
			this->NoButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->NoButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->NoButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->NoButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NoButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->NoButton->Location = System::Drawing::Point(338, 360);
			this->NoButton->Name = L"NoButton";
			this->NoButton->Size = System::Drawing::Size(100, 54);
			this->NoButton->TabIndex = 15;
			this->NoButton->Text = L"No";
			this->NoButton->UseVisualStyleBackColor = false;
			this->NoButton->Visible = false;
			this->NoButton->Click += gcnew System::EventHandler(this, &MyForm::NoButton_Click);
			// 
			// YesButton
			// 
			this->YesButton->BackColor = System::Drawing::Color::Transparent;
			this->YesButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->YesButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->YesButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->YesButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->YesButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->YesButton->Location = System::Drawing::Point(36, 360);
			this->YesButton->Name = L"YesButton";
			this->YesButton->Size = System::Drawing::Size(100, 54);
			this->YesButton->TabIndex = 14;
			this->YesButton->Text = L"Yes";
			this->YesButton->UseVisualStyleBackColor = false;
			this->YesButton->Visible = false;
			this->YesButton->Click += gcnew System::EventHandler(this, &MyForm::YesButton_Click);
			// 
			// cell9
			// 
			this->cell9->BackColor = System::Drawing::Color::Transparent;
			this->cell9->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell9->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell9->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell9->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell9->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell9->Location = System::Drawing::Point(308, 284);
			this->cell9->Name = L"cell9";
			this->cell9->Size = System::Drawing::Size(130, 130);
			this->cell9->TabIndex = 30;
			this->cell9->UseVisualStyleBackColor = false;
			this->cell9->Visible = false;
			this->cell9->Click += gcnew System::EventHandler(this, &MyForm::cell9_Click);
			// 
			// cell8
			// 
			this->cell8->BackColor = System::Drawing::Color::Transparent;
			this->cell8->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell8->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell8->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell8->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell8->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell8->Location = System::Drawing::Point(172, 284);
			this->cell8->Name = L"cell8";
			this->cell8->Size = System::Drawing::Size(130, 130);
			this->cell8->TabIndex = 29;
			this->cell8->UseVisualStyleBackColor = false;
			this->cell8->Visible = false;
			this->cell8->Click += gcnew System::EventHandler(this, &MyForm::cell8_Click);
			// 
			// cell6
			// 
			this->cell6->BackColor = System::Drawing::Color::Transparent;
			this->cell6->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell6->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell6->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell6->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell6->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell6->Location = System::Drawing::Point(308, 148);
			this->cell6->Name = L"cell6";
			this->cell6->Size = System::Drawing::Size(130, 130);
			this->cell6->TabIndex = 28;
			this->cell6->UseVisualStyleBackColor = false;
			this->cell6->Visible = false;
			this->cell6->Click += gcnew System::EventHandler(this, &MyForm::cell6_Click);
			// 
			// cell5
			// 
			this->cell5->BackColor = System::Drawing::Color::Transparent;
			this->cell5->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell5->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell5->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell5->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell5->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell5->Location = System::Drawing::Point(172, 148);
			this->cell5->Name = L"cell5";
			this->cell5->Size = System::Drawing::Size(130, 130);
			this->cell5->TabIndex = 27;
			this->cell5->UseVisualStyleBackColor = false;
			this->cell5->Visible = false;
			this->cell5->Click += gcnew System::EventHandler(this, &MyForm::cell5_Click);
			// 
			// cell7
			// 
			this->cell7->BackColor = System::Drawing::Color::Transparent;
			this->cell7->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell7->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell7->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell7->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell7->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell7->Location = System::Drawing::Point(36, 284);
			this->cell7->Name = L"cell7";
			this->cell7->Size = System::Drawing::Size(130, 130);
			this->cell7->TabIndex = 26;
			this->cell7->UseVisualStyleBackColor = false;
			this->cell7->Visible = false;
			this->cell7->Click += gcnew System::EventHandler(this, &MyForm::cell7_Click);
			// 
			// cell4
			// 
			this->cell4->BackColor = System::Drawing::Color::Transparent;
			this->cell4->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell4->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell4->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell4->Location = System::Drawing::Point(36, 148);
			this->cell4->Name = L"cell4";
			this->cell4->Size = System::Drawing::Size(130, 130);
			this->cell4->TabIndex = 25;
			this->cell4->UseVisualStyleBackColor = false;
			this->cell4->Visible = false;
			this->cell4->Click += gcnew System::EventHandler(this, &MyForm::cell4_Click);
			// 
			// cell3
			// 
			this->cell3->BackColor = System::Drawing::Color::Transparent;
			this->cell3->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell3->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell3->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell3->Location = System::Drawing::Point(308, 12);
			this->cell3->Name = L"cell3";
			this->cell3->Size = System::Drawing::Size(130, 130);
			this->cell3->TabIndex = 24;
			this->cell3->UseVisualStyleBackColor = false;
			this->cell3->Visible = false;
			this->cell3->Click += gcnew System::EventHandler(this, &MyForm::cell3_Click);
			// 
			// cell2
			// 
			this->cell2->BackColor = System::Drawing::Color::Transparent;
			this->cell2->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell2->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell2->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell2->Location = System::Drawing::Point(172, 12);
			this->cell2->Name = L"cell2";
			this->cell2->Size = System::Drawing::Size(130, 130);
			this->cell2->TabIndex = 23;
			this->cell2->UseVisualStyleBackColor = false;
			this->cell2->Visible = false;
			this->cell2->Click += gcnew System::EventHandler(this, &MyForm::cell2_Click);
			// 
			// cell1
			// 
			this->cell1->BackColor = System::Drawing::Color::Transparent;
			this->cell1->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->cell1->FlatAppearance->CheckedBackColor = System::Drawing::Color::Silver;
			this->cell1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->cell1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->cell1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cell1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->cell1->ForeColor = System::Drawing::Color::GhostWhite;
			this->cell1->Location = System::Drawing::Point(36, 12);
			this->cell1->Name = L"cell1";
			this->cell1->Size = System::Drawing::Size(130, 130);
			this->cell1->TabIndex = 22;
			this->cell1->UseVisualStyleBackColor = false;
			this->cell1->Visible = false;
			this->cell1->Click += gcnew System::EventHandler(this, &MyForm::cell1_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->BackColor = System::Drawing::Color::Transparent;
			this->statusStrip1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 503);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(484, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 31;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->toolStripStatusLabel1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(0, 17);
			// 
			// BackButton
			// 
			this->BackButton->BackColor = System::Drawing::Color::Transparent;
			this->BackButton->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightSlateGray;
			this->BackButton->FlatAppearance->MouseOverBackColor = System::Drawing::Color::LightSteelBlue;
			this->BackButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->BackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->BackButton->ForeColor = System::Drawing::Color::GhostWhite;
			this->BackButton->Location = System::Drawing::Point(172, 424);
			this->BackButton->Name = L"BackButton";
			this->BackButton->Size = System::Drawing::Size(130, 53);
			this->BackButton->TabIndex = 32;
			this->BackButton->Text = L"Back";
			this->BackButton->UseVisualStyleBackColor = false;
			this->BackButton->Visible = false;
			this->BackButton->Click += gcnew System::EventHandler(this, &MyForm::BackButton_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(484, 525);
			this->Controls->Add(this->BackButton);
			this->Controls->Add(this->NoButton);
			this->Controls->Add(this->YesButton);
			this->Controls->Add(this->InviteButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->RegistrationButton);
			this->Controls->Add(this->IPTextBox);
			this->Controls->Add(this->NameTextBox);
			this->Controls->Add(this->IPLabel);
			this->Controls->Add(this->NameLabel);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->cell9);
			this->Controls->Add(this->cell8);
			this->Controls->Add(this->cell6);
			this->Controls->Add(this->cell5);
			this->Controls->Add(this->cell7);
			this->Controls->Add(this->cell4);
			this->Controls->Add(this->cell3);
			this->Controls->Add(this->cell2);
			this->Controls->Add(this->cell1);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tic-tac-toe";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		bool nick_ip(String^ nick, String^ ipS);
		Boolean b = true;

	private: System::Void YesButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void RegistrationButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell2_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell3_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell4_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell5_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell6_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell7_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell8_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void cell9_Click(System::Object^ sender, System::EventArgs^ e);
	   public:System::Threading::Thread^ ClientHandlerThread;
private: System::Void InviteButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NoButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void NameTextBox_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};
}
