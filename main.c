#include <stdlib.h>
#include <avcodec.h>
#include <avformat.h>
#include "fft.h"
#include "util.h"

int main(int argc, const char * argv[]){
    AVFormatContext *pFormatCtx = NULL;
    VideoResolution *res = NULL;
    AVRational * aspect_ratio = NULL;
    fft_stream_info_list *list;
    if(argc < 2) {
        return 1;
    }
    av_register_all();

    if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0) {
        return 1;
    }

    av_find_stream_info(pFormatCtx);
    //av_dump_format(pFormatCtx,0, argv[1], 0); 
    
    list = fft_get_stream_info(pFormatCtx);
    if(list) {
	fft_stream_info *node = list->node;
	while(node) {
		char* type[3] = {"AUDIO", "VIDEO", "UNKNOWN"};
		printf("%s=%s\n", type[node->type], node->name);
		node = node->next;
	}
    }
    fft_free_stream_info_list(list);
    res = fft_get_video_resolution(pFormatCtx);
    if(res) {
        printf("Resolution=%dx%d\n", res->width, res->height);
    }

    aspect_ratio = fft_get_video_aspect_ratio(pFormatCtx);
    if(aspect_ratio) {
        printf("Aspect_Ratio=%d:%d\n", aspect_ratio->num, aspect_ratio->den);
    }

    free(res);
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);
    return 0;
}
