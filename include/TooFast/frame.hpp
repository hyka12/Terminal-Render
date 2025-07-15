#ifndef FRAME_HEADER
#define FRAME_HEADER

#include<vector>
#include<string>

namespace Matrix {
    typedef struct Frame_Struct{
        std::vector<char> Characters;
        std::vector<std::string> Terminal_Commands;
        int Width;
        int Height;

        int Append_String(int X_Cord, int Y_Cord, std::string Input_String);
        int Append_Multi_Line_String(int X_Cord, int Y_Cord, std::string Input_Str, char Newline_Marker);

        int Append_Foreground_Color(int X_Cord, int Y_Cord, int Red, int Green, int Blue);
        int Append_Background_Color(int X_Cord, int Y_Cord, int Red, int Green, int Blue);

    } Frame;
}

#endif 
