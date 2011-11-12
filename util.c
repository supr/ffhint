#include <stdlib.h>
#include <avformat.h>
#include "fft.h"
#include "util.h"

AVStream * fft_get_video_stream(AVFormatContext *ic) {
    AVStream * s = NULL;
    for(int i=0; i < ic->nb_streams; i++ ) {
        if(ic->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            s = ic->streams[i];
            return s;
        }
    }
    return NULL;
}

VideoResolution * fft_get_video_resolution(AVFormatContext *ic) {
    const AVStream * video_stream = fft_get_video_stream(ic);
    VideoResolution * res = NULL;
    if(video_stream) {
        AVCodecContext * pAVCodecCtx = video_stream->codec;
        res = (VideoResolution *)malloc(sizeof(VideoResolution));
        if(res) {
            res->width = pAVCodecCtx->width;
            res->height = pAVCodecCtx->height;
            return res;
        }
    }
    return NULL;    
}

AVRational * fft_get_video_aspect_ratio(AVFormatContext *ic) {
    const AVStream * video_stream = fft_get_video_stream(ic);
    
    if(video_stream) {
        AVRational * aspect_ratio = (AVRational *)malloc(sizeof(AVRational));
        if(aspect_ratio) {
            av_reduce(&aspect_ratio->num, &aspect_ratio->den,
                    video_stream->codec->width * video_stream->codec->sample_aspect_ratio.num,
                    video_stream->codec->height * video_stream->codec->sample_aspect_ratio.den,
                    1024*1024);
            return aspect_ratio;
        }
    }
    return NULL;
}
