#ifndef MATRIX_HEADER
#define MATRIX_HEADER 

#include<TooFast/frame.hpp>

#include<sys/ioctl.h>
#include<unistd.h>

#include<vector>

namespace Matrix {
    int Get_Term_Size(struct winsize &Term_Size);
    
    typedef class Framebuffer_Class{
        std::vector<Frame> Frames;

        public:

        int Get_Buffer_Size(){return Frames.size();};

        int Push_Frame(); // pushes blank frame
        int Push_Frame(Frame Custom_Frame);

        Frame* Get_Frame(int Frame_Position);

        int Draw_Frame();
        int Pull_Frame();

    } Framebuffer;

};

#endif
