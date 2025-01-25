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