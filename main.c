#include <stdlib.h>
#include <avcodec.h>
#include <avformat.h>
#include "fft.h"
#include "util.h"

int main(int argc, const char * argv[]){
    AVFormatContext *pFormatCtx = NULL;
    VideoResolution *res;
    AVRational * aspect_ratio = NULL;
    if(argc < 2) {
        return 1;
    }
    av_register_all();
   
    if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0) {
        return 1;
    }
   
    av_find_stream_info(pFormatCtx);
    //av_dump_format(pFormatCtx,0, argv[1], 0); 
    //printf("%s: %s\n", pFormatCtx->iformat->name, pFormatCtx->iformat->long_name);
    
    res = fft_get_video_resolution(pFormatCtx);
    if(res) {
        printf("Resolution: %dx%d\n", res->width, res->height);
    }

    aspect_ratio = fft_get_video_aspect_ratio(pFormatCtx);
    if(aspect_ratio) {
        printf("Aspect Ratio: %d:%d\n", aspect_ratio->num, aspect_ratio->den);
    }
    free(res);
    return 0;
}
