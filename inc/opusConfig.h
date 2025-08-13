#ifndef OPUSCONFIG_H
#define OPUSCONFIG_H

// Duration of a sample : sample size = (OPUS_FRAMEDURATION_MS/1000.0) * OPUS_SAMPLE_RATE
#define OPUS_FRAMEDURATION_MS 100

// must be one of 8000, 12000, 16000, 24000, 48000
#define OPUS_SAMPLE_RATE 24000

#endif
