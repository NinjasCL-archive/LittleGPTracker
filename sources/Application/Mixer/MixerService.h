#ifndef _MIXER_SERVICE_H_
#define _MIXER_SERVICE_H_

#include "Foundation/T_Singleton.h"
#include "Foundation/Observable.h"
#include "Services/Audio/AudioMixer.h"
#include "Services/Audio/AudioOut.h"
#include "Application/Commands/CommandDispatcher.h" // Would be better done externally and call an API here
#include "MixBus.h"
#include "SDL/SDL.h"

enum MixerServiceMode {
	MSM_AUDIO,
	MSM_FILE,
	MSM_FILESPLIT,
	MSM_FILERT,
	MSM_FILESPLITRT
} ;

#define MAX_BUS_COUNT 10

class MixerService: 
      public T_Singleton<MixerService>,
      public Observable,
      public I_Observer,
      public CommandExecuter      
{

public:
	MixerService() ;
	virtual ~MixerService() ;

	bool Init() ;
	void Close() ;

	bool Start() ;
	void Stop() ;

	MixBus *GetMixBus(int i) ;	

	virtual void Update(Observable &o,I_ObservableData *d) ;	

	void OnPlayerStart() ;
	void OnPlayerStop() ;

	bool Clipped() ;
	void SetMasterVolume(int) ;
	int GetPlayedBufferPercentage() ;
	
	virtual void Execute(FourCC id,float value) ;

	AudioOut *GetAudioOut() ;

	void Lock() ;
	void Unlock() ;

protected:
	void toggleRendering(bool enable) ;
private:
	AudioOut *out_ ;
	MixBus master_ ;
	MixBus bus_[MAX_BUS_COUNT] ;
	MixerServiceMode mode_ ;
	SDL_mutex *sync_ ;  

} ;
#endif
