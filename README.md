# Godot-opus

This is a godot extension based on the [opus codec](https://opus-codec.org) allowing for real-time compression of audio recordings.  

It is part of a collection of tools aiming to provide modular audio processing for quality VOIP within godot.
Check out the other tools and the demo here : https://github.com/Mysgym/mysVOIPtools-godot4-demo

## Building

This project is built using Scons, and requires an [opus](https://opus-codec.org/downloads) static library, which should already be installed on most systems.

  1 - Clone this repo and the godot-cpp submodule  
  ```
  git clone --recurse-submodules https://github.com/Mysgym/Godot-opus && cd Godot-opus
  ```

  2 - Build using scons  
  (Godot-cpp sometimes doesn't compile correctly, try running the command again if you get a missing file)
  ```
  scons
  ```

  3 - Add the extension to your own project by copying the contents of the addons folder to your project's addons folder.  

Although this project has only been tested on linux, it should work on windows and macos provided an opus binary and minor adjustments to the SConstruct file.  
Windows and macOS support is currently a work in progress, I encourage anyone attempting to compile for those OS to report any encountered issue and create pull requests for functional builds.

## Usage  

### Demo

A demo incorporating this extension in a VOIP setting is available here : https://github.com/Mysgym/mysVOIPtools-godot4-demo

Here is the relevant code : 

#### encoding : 

```gdscript
  # --- Create objects
  @onready var encoder := GdOpusEncoder.new()

  #size to input in the resampler to get a correctly size packet for opus
  @onready var resamplerInputSize := encoder.get_resampler_input_size()

  [..]
  # encode and send frame
  var packet := encoder.encode(frame)
  send(packet)
  [..]

```

#### decoding : 

```gdscript
  # --- Create objects
  @onready var decoder := GdOpusDecoder.new()

  [..]
  # receive and decode frame
  var frame := decoder.decode(packet)
  [..]

```


### Methods detail
This extension add the "GdOpusEncoder" and "GdOpusDecoder" objects to godot, implementing the following methods :

1. Encoder

| Method definition | Method description |
| ----------------- | ------------------ |
| encode(samples : PackedVector2Array) -> PackedByteArray | encodes a frame. By default, the frame should be 48kHz sampling rate and 480 samples. See [configuration](https://github.com/Mysgym/Godot-opus/blob/main/README.md#configuration)|
| get_resampler_input_size() -> int | Utility function returning the input frame size for a resampler to output a correctly size packet for this encoder. Based on the AudioServer's mixrate| 

2. Decoder  

| Method definition | Method description |
| ------------------|--------------------|
| decode(packet : PackedByteArray) -> PackedVector2Array | decodes a packet encoded by a GdOpusEncoder|
<br>  

## Configuration

By default, this extension encodes frames of 10ms on a 48kHz sampling rate. 
This can be configured in the inc/opusConfig.h file.

## Contributing

This project is being actively maintained, any reported issue and contributions are greatly appreciated.

Windows and macOS users are encouraged to attempt compilation and share their work as I personally lack easy access to those OS.  

## License

this project is MIT licensed.
