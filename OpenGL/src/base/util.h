#ifndef UTIL_H
#define UTIL_H

#include "import.h"
#include "structure.h"

#include <SOIL/SOIL.h>


const string kImagePath = "/home/legend/myfile/GLmacia/resources/img";
const string kShaderPath = "/home/legend/myfile/GLmacia/resources/shaders";
const string kVertexSuffix = ".vert";
const string kFragmentSuffix = ".frag";

static bool ReadShaderFile(char* content, char* file_path) {
  FILE* in_file = fopen(file_path, "r");
  if (!in_file)
    return false;
  fseek(in_file, 0, SEEK_END);
  long file_length = ftell(in_file);
  rewind(in_file);
  if (file_length <= 0)
    return false;
  content = new char[file_length + 1];
  fread(content, file_length, 1, in_file);
  fclose(in_file);
  content[file_length] = '\0';
  return true;
}

static bool ReadShaderFile(string& content, string file_path) {
  content.clear();
  ifstream in_file(file_path.c_str(), ifstream::in);
  if (!in_file.is_open())
    return false;
  while (!in_file.eof()) {
    string temp_line;
    getline(in_file, temp_line);      
    content.append(temp_line);
  }
  in_file.close();
  return true;
}

static bool ReadImageFile(ImageData& image, string file) {
  image.pixels = SOIL_load_image(file.c_str(), &image.width, &image.height, 0, SOIL_LOAD_RGB);
  return image.pixels != NULL;
}

#endif
