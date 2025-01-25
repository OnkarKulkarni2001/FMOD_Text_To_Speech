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
	ISpVoice* m_ISpVoice = nullptr;
	~TextToSpeech() {
		m_ISpVoice->Release();
		m_ISpVoice = nullptr;
	}
private:
	bool m_Initialized = false;
};

int main()
{	
	
	return 0;
}