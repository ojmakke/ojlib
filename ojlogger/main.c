#include "ojlogger.h"


int main(int argc, char* argv[])
{
  char* testString = "TestString";
  int val = 6;
  LOGE("This is error %d %s\n", val, testString);
  LOGW("This is warning %d %s\n", val, testString);
  LOGI("This is information %d %s\n", val, testString);
  LOGD("This is debug %d %s\n", val, testString);
  LOG1("This is level 1 %d %s\n", val, testString);
  LOG2("You got the idea\n");
  return 0;
}
