# Entrance monitor v2

The application monitors if a car is blocking the entrance and/or illegally parked there.
the application processes CCTV camera streams. using deep learning it filters out cars from other detected objects, then
runs them through a series of computational algorithms to determine if the car is blocking the entrance.
if the audio controller is running on a remote machine the alert is controlled using VoIP, the server transmits the alert sound (configurable), after determining the entrance is blocked in a 5
seconds interval, taking into account moving objects.
after receiving the audio, the client, which uses Bluetooth in order to send the audio, transmits it to a portable
speaker

## Project structure
    .
    ├── apps 
    │   ├── project_runner          # project runner executable 
    ├── src                         # Source files (libs, standalone)
    │   ├── stream_obtainer         # stream obtainer.
    │   ├── object_detector         # detects objects in a frame.
    │   ├── blocking_computation    # computes the blockage of an object to the entrance.
    │   ├── results_aggregator      # aggregates the blockage results into a decision.
    │   ├── audio_controller        # controls audio output based on a decision.
    │   ├── core                    # core components of the application (amqp/task_service/consumer,publisher...).
    │   ├── utils                   # utils project.
    │   └── models                  # view models shared between the services.


### stream_obtainer

obtains stream of set of source of frames (cctv camera,recorded video, etc...), compress the video into jpeg,
publishes them into exchange `frames`.

### object_detector

Receive frames from queue `frames`, detects objects in the frame and publishes them into exchange `detections`.

### blocking_computation

Receive detections from queue `detections`, computes blocking percentage of the entrance, outputs a result of blocking(
1)/non-blocking(0) into exchange `results`.

### results_aggregator

Receive results from queue `results`, compute a mean of the results of decided interval, then outputs a decision blocked`(1)`
/not-blocked`(0)` to exchange `decisions`.

### audio_controller

Receive decisions from queue `decisions`, controls audio output based on decision, (stops audio if the entrance is no longer
blocked, starts the audio otherwise).

### project_runner (apps)
project runner which runs all the services defined inside it. every service has its own `injector`.

### *_standalone
standalone executable, is a service runner seperated from the apps `project_runner`, used for running on different machine or multiple instances of the same service.


#### note
messages are packed using `msgpack` (`cppack`) to ensure smaller message size.
