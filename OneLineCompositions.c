//HelloPA
//by Christopher Saunders
//
//based on a template by Thomas Hass August 2012

#include <CoreFoundation/CoreFoundation.h>
#include <AudioToolbox/AudioToolbox.h>
#include "portaudio.h"
#include "callback.c"

int main(int argc, const char * argv[])
{
    // The "handle", an address where sample values are written
    PaStream *stream;

    // A data structure to hold configuration information for the stream
    PaStreamParameters streamParams;

    // An error type
    PaError err;

    // Declare a persistant data structure
    CallbackInfo info;

    // From user input
    int durationSeconds, 
            outDevIndex, 
             numDevices,
               waveform, 
                   freq;

    // SAMPLE RATE
    double sr = 44100.0;

    // BUFFER SIZE
    int framesPerBuffer = 512;




    printf("Initializing PortAudio.\n");
    err  = Pa_Initialize();
    
    if (err != paNoError) 
    {
        printf("Failed to init PortAudio.\n");
        return -1;
    }
    

    // Get total of all audio devices
    numDevices = Pa_GetDeviceCount();

    // Declare a data structure to hold device configuration
    const PaDeviceInfo *devices[numDevices];

    // Print Device List
    for (int i = 0; i < numDevices; i++) {
        devices[i] = Pa_GetDeviceInfo(i);
        if (devices[i]->maxOutputChannels > 0) {
            printf("%d  %s\n", i, devices[i]->name);
        }
    }
    printf("Please select the output device: ");
    scanf("%d", &outDevIndex);
    
    // Ask user for play time in seconds.
    printf("Please specify play time in seconds: ");
    scanf("%d", &durationSeconds);

    // Define audio output parameters.
    streamParams.device = outDevIndex;
    streamParams.channelCount = devices[outDevIndex]->maxOutputChannels;
    streamParams.sampleFormat = paFloat32;
    streamParams.suggestedLatency = 0;
    streamParams.hostApiSpecificStreamInfo = NULL;
    
    printf("Opening stream...\n");
    err = Pa_OpenStream(&stream,
                        NULL,
                        &streamParams,
                        sr,
                        framesPerBuffer,
                        0,
                        RenderCallback, // Defined as function above main()
                        &info);
    if (err != paNoError) {
        printf("Failed to open stream.\n");
        Pa_Terminate();
        return -1;
    }
    
    info.sr = sr;
    info.inChnls = 0;
    info.outChnls = devices[outDevIndex]->maxOutputChannels;
    info.sampleCounter = 0;
    info.secondsCounter = 0;
    info.durationSeconds = durationSeconds;
    info.process = true;
    info.waveform_selector = waveform;
    
    printf("Starting stream.\n");
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        printf("Failed to start stream.\n");
        Pa_Terminate();
        return -1;
    }
    
    // Run Loop 
    while (info.process == true) ;
    

    // Clean Up 
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        printf("Failed to stop stream.\n");
        Pa_Terminate();
    }
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        printf("Failed to close stream.\n");
        Pa_Terminate();
        return -1;
    }
    Pa_Terminate();
    
    printf("All done.\n");
    
    return 0;
}

