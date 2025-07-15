#include<TooFast/framebuffer.hpp>

#include<sstream>
#include<fstream>
#include<thread>  
#include<chrono>

typedef struct RGB_Color_Struct{
    int Red = 0;
    int Green = 0;
    int Blue = 0;

    RGB_Color_Struct(int Init_Red, int Init_Green, int Init_Blue) 
                   : Red(Init_Red), Green(Init_Green), Blue(Init_Blue){};
} RGB_Color;


RGB_Color Morph_Color(int Current_Increment, int Increment_End, RGB_Color Start_Color, RGB_Color End_Color){
    RGB_Color Morphing_Color = Start_Color;
    float Change = (float)Current_Increment/(float)Increment_End; 

    Morphing_Color.Red = Morphing_Color.Red-Morphing_Color.Red*Change+End_Color.Red*Change;
    Morphing_Color.Green = Morphing_Color.Green-Morphing_Color.Green*Change+End_Color.Green*Change;
    Morphing_Color.Blue = Morphing_Color.Blue-Morphing_Color.Blue*Change+End_Color.Blue*Change;

    return Morphing_Color;
}

int main(){
    Matrix::Framebuffer Framebuffer;

    while(1){
        Framebuffer.Push_Frame();

        Matrix::Frame* Frame_Ref = Framebuffer.Get_Frame(0);

        static int Morph_Iter = 1, Morph_Direction = 0;
        RGB_Color Start_Color(255,0,255);
        RGB_Color End_Color(0,255,255);

        if (Morph_Iter==120 && Morph_Direction){
            Morph_Direction++;        
        }else if (Morph_Iter<120 && Morph_Direction){
            Morph_Iter++;
        }

        if(Morph_Iter==0 && !Morph_Direction){
            Morph_Direction--;
        }else if(Morph_Iter>0 && !Morph_Direction){
            Morph_Iter--; 
        }

        RGB_Color Morphed_Color = Morph_Color(Morph_Iter, 120, Start_Color, End_Color);

        std::ifstream File("../ascii_art/binary_love");
        std::string File_Content = "";
        std::string File_Line = "";

        while(std::getline(File, File_Line)){
            File_Content+=File_Line;
        }

        Frame_Ref->Append_Multi_Line_String(Frame_Ref->Width/2-96/2, Frame_Ref->Height/2-18/2, File_Content, '+');

        Frame_Ref->Append_Foreground_Color(0, 0, Morphed_Color.Red, Morphed_Color.Green, Morphed_Color.Blue);
        Frame_Ref->Append_Background_Color(0, 0, 0,   0,   0);

        Framebuffer.Draw_Frame();
        Framebuffer.Pull_Frame();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
    }

    return 0;
}

