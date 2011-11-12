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

fft_stream_info_list * fft_get_stream_info(AVFormatContext *ic) {
	fft_stream_info_list *head = NULL;
	fft_stream_info *node = NULL;
	if(ic->nb_streams) {
		head = (fft_stream_info_list *)malloc(sizeof(fft_stream_info_list));
		if(!head) {
			return NULL;
		}
		head->node = NULL;
		for(unsigned int i = 0; i < ic->nb_streams; i++) {
			AVCodec *decoder;
			node = (fft_stream_info *)malloc(sizeof(fft_stream_info));
			if(!node) {
				goto fail;
			}

			switch(ic->streams[i]->codec->codec_type) {
				case AVMEDIA_TYPE_AUDIO:
					node->type = AUDIO;
					break;
				case AVMEDIA_TYPE_VIDEO:
					node->type = VIDEO;
					break;
				default:
					node->type = UNKNOWN;
			}

			decoder = avcodec_find_decoder(ic->streams[i]->codec->codec_id);
			if(decoder)
				node->name = decoder->name;
			else
				node->name = NULL;
			node->next = head->node;
			head->node = node;
		}
		return head;
	}
	return NULL;
fail:
	fft_free_stream_info_list(head);
	return NULL;
}

void fft_free_stream_info_list(fft_stream_info_list *list) {
	if(!list)
		return;

	fft_stream_info *node = list->node;
	while(node) {
		fft_stream_info *t = node->next;
		free(node);
		node = t;
	}

	free(list);
}
