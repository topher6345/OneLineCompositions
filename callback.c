// Persistant data for the callback
//
//
//
//
#include "composition.c"
typedef struct 
{
    double sr;
    int inChnls, outChnls;
    bool process;
    long int sampleCounter;
    long int secondsCounter;
    long int durationSeconds;
    int waveform_selector;
    int t;
} 
CallbackInfo;

// Callback Function
//
static int RenderCallback(const void    *inputBuffer, // Arg 1 Input Adress 
                                void   *outputBuffer, // Arg 2 Output Adress
                       unsigned long framesPerBuffer, // Arg 3 Buffer Size
      const PaStreamCallbackTimeInfo       *timeInfo, // Arg 4 PA timer address
               PaStreamCallbackFlags     statusFlags, // Arg 5 PA Settings
                                void       *userData) // Arg 6 Persistant Data Structure
{
    // Get our Persistant Data Structure
    CallbackInfo *info = (CallbackInfo *)userData;

    // Get adress of our output Buffer
    float *out = (float *)outputBuffer;

    int i, j;

        for (i = 0; i < info->outChnls; i++) // Iterate over both Channels (Stereo)
        {
 
            // Fill Buffer Samples 
            for (j = 0; j < framesPerBuffer; j++) 
            {  
                out[j*info->outChnls+i] = COMPOSITION; 
                info->t++;
            }
            info->t = info->t - framesPerBuffer;
       }
    
    info->t = info->t + framesPerBuffer;
    // Keep a tally of samples by counting All
    // the samples in the Buffersize
    info->sampleCounter += framesPerBuffer;

    // When we get 1 second's worth of samples
    if (info->sampleCounter >= info->sr) 
    {
        // Reset Count
        info->sampleCounter = 0;
        
        // Tally Elapsed time in seconds
        info->secondsCounter++;
        
        // When we reach maximum duration in seconds, quit the audio process. 
        if (info->secondsCounter >= info->durationSeconds) { info->process = false; }
    }
    
    return 0;
}
