// Copyright (c) 2018 winking324
//


#include "model/flv_body.h"

#include <sstream>
#include <QDebug>

#include "commons/read_bytes.h"


namespace flv_parser {


FlvBody::FlvBody() {
  previous_size_ = 0;
}

size_t FlvBody::ParseData(const std::string &data) {
  if (data.size() < 4) return 0;

  size_t read_pos = 0;
  previous_size_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  size_t tag_size = tag_.ParseData(data, read_pos);
  qInfo() << "read flv body, previous size: " << previous_size_
          << ", tag size: " << tag_size;
  if (tag_size > 0) {
    return tag_size + read_pos;
  }
  return 0;
}

std::string FlvBody::Type() {
  return tag_.Type();
}

std::string FlvBody::Info() {
  std::string tag_info = tag_.Info();
  std::stringstream ss;
  ss << "PreSize:" << previous_size_ << (tag_info.empty() ? "" : "|")
     << tag_info;
  return ss.str();
}

YAML::Node FlvBody::Detail() {
  YAML::Node root;
  root["PreviousTagSize"] = previous_size_;
  root["Tag"] = tag_.Detail();
  return root;
}

std::string FlvBody::Data() {
  return tag_.Data();
}


}  // namespace flv_parser

