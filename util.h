#ifndef __FFT_UTIL_H__
#define __FFT_UTIL_H__ 

typedef struct fft_stream_info fft_stream_info;
typedef struct fft_stream_info_list fft_stream_info_list;

enum stream_type {
	AUDIO,
	VIDEO,
	UNKNOWN,
};

struct fft_stream_info {
	const char * name;
	enum stream_type type;
	struct fft_stream_info *next;
};

struct fft_stream_info_list {
	struct fft_stream_info *node;
};

AVStream * fft_get_video_stream(AVFormatContext *);
VideoResolution * fft_get_video_resolution(AVFormatContext *);
AVRational * fft_get_video_aspect_ratio(AVFormatContext *);
fft_stream_info_list * fft_get_stream_info(AVFormatContext *);
void fft_free_stream_info_list(fft_stream_info_list *);
#endif
