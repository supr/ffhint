#ifndef __FFT_UTIL_H__
#define __FFT_UTIL_H__ 

AVStream * fft_get_video_stream(AVFormatContext *);
VideoResolution * fft_get_video_resolution(AVFormatContext *);
AVRational * fft_get_video_aspect_ratio(AVFormatContext *);
#endif
