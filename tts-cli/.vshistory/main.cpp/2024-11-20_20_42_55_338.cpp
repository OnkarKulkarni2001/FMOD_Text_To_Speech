#include <Windows.h>
#include <sapi.h>
#include <iostream>
#include <atlbase.h>
#include <sphelper.h>

class TextToSpeech {
public:
	TextToSpeech() {
		HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_ISpVoice);
		m_Initialized = true;
	}

	~TextToSpeech() {
		m_ISpVoice->Release();
		m_ISpVoice = nullptr;
	}

	void Speak(LPCWSTR text) {
		if (!m_Initialized) {
			return;
		}

		m_ISpVoice->Speak(text, 0, nullptr);
	}

	void SetVoice() {
		if (!m_Initialized) {
			return;
		}

		HRESULT hr = S_OK;

		CComPtr<ISpObjectToken> cpVoiceToken;
		CComPtr<IEnumSpObjectTokens> cpEnum;
		CComPtr<ISpVoice> cpVoice;
		ULONG ulCount = 0;

		hr = cpVoice.CoCreateInstance(CLSID_SpVoice);

		if (SUCCEEDED(hr)) {
			hr = SpEnumTokens(SPCAT_VOICES, NULL, NULL, &cpEnum);
		}

		if (SUCCEEDED(hr)) {
			hr = cpEnum->GetCount(&ulCount);
		}

		hr = cpEnum->Next(1, &cpVoiceToken, NULL);

		if (SUCCEEDED(hr)) {
			PWSTR voiceName = nullptr;

			hr = SpGetDescription(cpVoiceToken, &voiceName);
			if (SUCCEEDED(hr) && voiceName != nullptr) {
				hr = cpVoice->SetVoice(cpVoiceToken);
				if (SUCCEEDED(hr)) {
					wprintf(L"Speaking with voice: %s\n", voiceName);
					hr = cpVoice->Speak(L"Yo yo yo, this is a different voice ma dudeds", SPF_DEFAULT, NULL);
				}

				CoTaskMemFree(voiceName);
			}
			system("Pause");
		}
	}

	ISpVoice* m_ISpVoice = nullptr;
private:
	bool m_Initialized = false;
};

int main()
{	
	HRESULT hr = CoInitialize(0);
	if (FAILED(hr)) {
		printf("Unable to intialize the COM library!\n");
		return -1;
	}
	TextToSpeech tts;
	tts.Speak(L"Hey this is super dooper cool!");

	system("Pause");

	CoUninitialize();

	return 0;
}