#include <Windows.h>
#include <sapi.h>
#include <iostream>
#include <atlbase.h>
#include <sphelper.h>

class TextToSpeech {
public:
	TextToSpeech() {
		HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_ISpVoice);
	}

	ISpVoice* m_ISpVoice = nullptr;
	~TextToSpeech();
private:
	bool m_Initialized = false;
};

int main()
{	
	
	return 0;
}