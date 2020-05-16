#pragma once 


///Colors of text in the console
///Use functions color_on(color) and color_off
#ifdef COLORS

const char RES[] = "\033[0m";
const char RED[] = "\033[1;31m";
const char GREEN[] = "\033[1;32m";
const char BLUE[] = "\033[1;34m";
const char YELLOW[] = "\033[1;33m";
const char BLACK[] = "\033[1;30m";
const char MAGENTA[] = "\033[1;35m";
const char CYAN[] = "\033[1;36m";
const char WHITE[] = "\033[1;37m";


#endif

#ifndef COLORS

const char RES[] = " ";
const char RED[] = " ";
const char GREEN[] = " ";
const char BLUE[] = " ";
const char YELLOW[] = " ";
const char BLACK[] = " ";
const char MAGENTA[] = " ";
const char CYAN[] = " ";
const char WHITE[] = " ";


#endif

