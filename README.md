# Fork Modifications (Forked from https://github.com/Mysgym/Godot-opus)

-Added config() function to update the sample mix-rate and sample duration (in ms) at runtime.<br>
-Merged the two classes GdOpusDecoder and GdOpusEncoder in GdOpus.

# Godot-opus

This is a godot extension based on the [opus codec](https://opus-codec.org) allowing for real-time compression of audio recordings.  

## Building

This project is built using Scons, and requires an [opus](https://opus-codec.org/downloads) static library, which should already be installed on most systems.

  1 - Clone this repo and the godot-cpp submodule  
  ```
  git clone --recurse-submodules https://github.com/zonfr/Godot-opus.git && cd Godot-opus
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

Here is the relevant code : 

#### Encoding : 

```gdscript
  # --- Create objects
  @onready var gdopus := GdOpus.new()
  
  # Setting the mix-rate and the duration of the sample in milliseconds
  gdopus.config(48000, 10);

  # Size to input in the resampler to get a correctly size packet for opus
  @onready var resamplerInputSize := gdopus.get_resampler_input_size()

  [..]
  # encode and send frame
  var packet := gdopus.encode(frame)
  send(packet)
  [..]

```

#### Decoding : 

```gdscript
  # --- Create objects
  @onready var gdopus := GdOpus.new()

  [..]
  # receive and decode frame
  var frame := gdopus.decode(packet)
  [..]

```


### Methods detail
This extension add the "GdOpus" object to godot, implementing the following methods :

| Method definition | Method description |
| ----------------- | ------------------ |
| encode(samples : PackedVector2Array) -> PackedByteArray | encodes a frame. By default, the frame should be 48kHz sampling rate and 480 samples. See [configuration](https://github.com/zonfr/Godot-opus/blob/main/README.md#configuration)|
| get_resampler_input_size() -> int | Utility function returning the input frame size for a resampler to output a correctly size packet for this encoder. Based on the AudioServer's mixrate| 
| decode(packet : PackedByteArray) -> PackedVector2Array | decodes a packet encoded by a GdOpus|
<br>  

## Configuration

By default, this extension encodes frames of 100ms on a 24kHz sampling rate. 
This can be configured in the inc/opusConfig.h file.

## Contributing
This forked is not maintained, the original project is.

## License

this project is MIT licensed.
