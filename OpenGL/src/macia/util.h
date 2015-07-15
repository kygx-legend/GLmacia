#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;


const string SHADER_PATH = "/home/legend/myfile/GLmacia/resources/shaders";

static bool ReadFile(char* content, char* file_path) {
  FILE* file_pointer = fopen(file_path, "r");
  if (!file_pointer)
    return false;
  fseek(file_pointer, 0, SEEK_END);
  long file_length = ftell(file_pointer);
  rewind(file_pointer);
  if (file_length <= 0)
    return false;
  content = static_cast<char*>(malloc(file_length + 1));
  fread(content, file_length, 1, file_pointer);
  fclose(file_pointer);
  content[file_length] = '\0';
  return true;
}

static bool ReadFile(string& content, string file_path) {
  content.clear();
  ifstream in_file(file_path.c_str(), ifstream::in);
  if (!in_file.is_open())
    return false;
  while(!in_file.eof()) {
    string temp_line;
    getline(in_file, temp_line);      
    content.append(temp_line);
  }
  in_file.close();
  return true;
}

#endif
