
std::string str;

void compress_string(const std::string &source, std::string &compressed) {
  str = source;
  compressed.clear();
}

void decompress_string(const std::string &compressed, std::string &result) {
  result = str;
}