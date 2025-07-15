#include<TooFast/frame.hpp>

#include<iostream>
#include<sstream>

//TODO: add error handling to these functions...

int Matrix::Frame::Append_String(int X_Cord, int Y_Cord, std::string Input_Str){

    for(int Char_Iter = 0; Char_Iter<Input_Str.length(); Char_Iter++){
        Characters[Y_Cord*Width+X_Cord+Char_Iter] = Input_Str[Char_Iter];
    }

    return 0;
}

int Matrix::Frame::Append_Multi_Line_String(int X_Cord, int Y_Cord, std::string Input_Str, char Newline_Marker){

    std::vector<std::string> String_After_Split; 
    std::stringstream String_Stream(Input_Str); 
    std::string Str_Buf;

    while (std::getline(String_Stream, Str_Buf, Newline_Marker)) {
        String_After_Split.push_back(Str_Buf); 
    }

    for(int Print_Iter = 0; Print_Iter<String_After_Split.size(); Print_Iter++){
        Append_String(X_Cord, Y_Cord+Print_Iter, String_After_Split[Print_Iter]);
    }

    return 0;
}

int Matrix::Frame::Append_Foreground_Color(int X_Cord, int Y_Cord, int Red, int Green, int Blue){

    std::stringstream String_Stream_For_Formatting;
    String_Stream_For_Formatting<<"\e[38;2;"<<Red<<";"<<Green<<";"<<Blue<<"m";

    Terminal_Commands[Y_Cord*Width+X_Cord] += String_Stream_For_Formatting.str();

    return 0;
}

int Matrix::Frame::Append_Background_Color(int X_Cord, int Y_Cord, int Red, int Green, int Blue){

    std::stringstream String_Stream_For_Formatting;
    String_Stream_For_Formatting<<"\e[48;2;"<<Red<<";"<<Green<<";"<<Blue<<"m";

    Terminal_Commands[Y_Cord*Width+X_Cord] += String_Stream_For_Formatting.str();

    return 0;
}
