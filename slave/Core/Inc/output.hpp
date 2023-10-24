
#pragma once

#include "usbd_cdc_if.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
#include "main.h"

extern bool trace_is_on;

using namespace std;

#ifndef PC
// from https://stackoverflow.com/questions/533038/redirect-stdcout-to-a-custom-writer
class outbuf : public std::streambuf {
public:
    outbuf() {
        // no buffering, overflow on every char
        setp(0, 0);
    }

    virtual int_type overflow(int_type c = traits_type::eof()) {
        uint8_t ch[2];
        ch[0] = (uint8_t) c;
        if (c == '\n') {
            ch[0] = '\r';
            ch[1] = '\n';
            CDC_Transmit( ch, 2);
        } else {
            CDC_Transmit( ch, 1);
        }
        //if (c != EOF) {
        //    uprintf("%c", c);
        //}
        if (trace_is_on) {
            ITM_SendChar(c);
        }
        return c;
    }
};
#endif

#ifndef PC
// from https://gist.github.com/takashyx/937f3a794ad36cd98ec3
class debugStreambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c = EOF) {
        uint8_t ch[2];
        ch[0] = (uint8_t) c;
        if (c == '\n') {
            ch[0] = '\r';
            ch[1] = '\n';
            CDC_Transmit( ch, 2);
        } else {
            CDC_Transmit( ch, 1);
        }
        //if (c != EOF) {
        //    uprintf("%c", c);
        //}
        if (trace_is_on) {
            ITM_SendChar(c);
        }
        return c;
    }
};

class Cout2VisualStudioDebugOutput {

    debugStreambuf dbgstream;
    std::streambuf *default_stream;

public:
    Cout2VisualStudioDebugOutput() {
        default_stream = std::cout.rdbuf(&dbgstream);
    }

    ~Cout2VisualStudioDebugOutput() {
        std::cout.rdbuf(default_stream);
    }
};

extern Cout2VisualStudioDebugOutput c2v;
#endif

//  from https://stackoverflow.com/questions/50147663/store-snprintf-arguments-for-later-use
class Printer {
   private:
      char                              buffer[1024];
      std::string                       format;
      std::function<std::string(void)>  l;

   public:
      template <typename ... Args>
      Printer (char const * f0, Args & ... as) : format{f0}
       {
         l = [&] () -> std::string
          {
            snprintf(buffer, sizeof(buffer)/sizeof(buffer[0]),
                     format.c_str(), as...);

            return buffer;
          };
       }

      std::string callback () const
       { return l(); }
 };

void addToQueue(Printer p);

#ifndef PC
void uprintf(const char* format,...);
#endif
int _write(int file, char *ptr, int len);


// list from https://stackoverflow.com/questions/24281603/c-underline-output
//  002 (bold), 003 (colour), 017 (plain), 026 (reverse) and 037 (underline).
// for bold colors, change the 0 after the [ to a 1
// for underlined colors, change the 0 after the [ to a 4
static map<string, string> colorMap = {
        {"reset",   {0x1b,'[','0',';','3','9','m',0}},
        {"black",   {0x1b,'[','0',';','3','0','m',0}},
        {"red",     {0x1b,'[','0',';','3','1','m',0}},
        {"green",   {0x1b,'[','0',';','3','2','m',0}},
        {"yellow",  {0x1b,'[','0',';','3','3','m',0}},
        {"blue",    {0x1b,'[','0',';','3','4','m',0}},
        {"Upurple", {0x1b,'[','4',';','3','5','m',0}},
        {"cyan",    {0x1b,'[','0',';','3','6','m',0}},
        {"lgray",   {0x1b,'[','0',';','3','7','m',0}},
        {"dgray",   {0x1b,'[','0',';','3','8','m',0}},
        {"Bred",    {0x1b,'[','1',';','3','1','m',0}},
        {"bold",        {0x1b,'[','1','m'}},
        {"underline",   {0x1b,'[','4','m'}},
        {"blink",       {0x1b,'[','5','m'}},
        {"reverse",     {0x1b,'[','7','m'}},
        {"up",          {0x1b,'[','0','A'}},
        {"down",        {0x1b,'[','0','B'}},
        {"left",        {0x1b,'[','0','D'}},
        {"right",       {0x1b,'[','0','C'}},
};

string colorText(string str);

class Logger {
   private:
      std::stringstream buf;
   public:
      Logger(){}
      ~Logger() {
         // Add an newline before exit?
         buf << std::endl;
      }

      template<typename T>
      Logger &operator << (const T &t) {
         buf << t;
         uprintf("log: %s", const_cast<char*>(buf.str().c_str()));
         return * this;
      }
};

extern Logger logger;

int getMemSizeInKB();

void printHelloMsg();
