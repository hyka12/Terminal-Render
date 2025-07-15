#include<TooFast/framebuffer.hpp>

#include<string>
#include<unistd.h>

int Matrix::Get_Term_Size(struct winsize &Term_size){
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &Term_size) == -1)
        return 1;

    return 0;
};

int Matrix::Framebuffer::Push_Frame(){

    struct winsize Term_Size;
    Matrix::Get_Term_Size(Term_Size);

    Matrix::Frame Blank_Frame;
    Blank_Frame.Width = Term_Size.ws_col;
    Blank_Frame.Height = Term_Size.ws_row;

    for(int Frame_Row = 0; Frame_Row<Blank_Frame.Width; Frame_Row++){
        for(int Frame_Col = 0; Frame_Col<Blank_Frame.Height; Frame_Col++){
            Blank_Frame.Characters.push_back(' ');
            Blank_Frame.Terminal_Commands.push_back("");
        }
    }

    Frames.insert(Frames.begin(), Blank_Frame);

    return 0;
}

int Matrix::Framebuffer::Push_Frame(Matrix::Frame Custom_Frame){
    Frames.insert(Frames.begin(), Custom_Frame);

    return 0;
};

Matrix::Frame* Matrix::Framebuffer::Get_Frame(int Frame_Position){
    return &Frames[Frame_Position];
}

int Matrix::Framebuffer::Draw_Frame(){

    Matrix::Frame First_Frame = Frames[Frames.size()-1];

    std::string Print_Batch;

    for(int Matrix_Iter = 0; Matrix_Iter<First_Frame.Width*First_Frame.Height; Matrix_Iter++){
        Print_Batch+=First_Frame.Terminal_Commands[Matrix_Iter];
        Print_Batch+=First_Frame.Characters[Matrix_Iter];
    }

    write(STDOUT_FILENO, Print_Batch.c_str(), Print_Batch.length());

    return 0;
}

int Matrix::Framebuffer::Pull_Frame(){

    if (!Frames.empty()) { 
        Frames.pop_back();
    }else{
        return 1;
    }

    return 0;
}









