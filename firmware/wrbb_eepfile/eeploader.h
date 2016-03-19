/*
 * EEPROM FIle Loader
 *
 * Copyright (c) 2016 Wakayama.rb Ruby Board developers
 *
 * This software is released under the MIT License.
 * https://github.com/wakayamarb/wrbb-v1lib-firm/blob/master/MITL
 *
 */

void lineinput(char *arry);
void writefile(const char *fname, int size, char code);
void readfile(const char *fname, char code);
int fileloader(const char* str0, const char* str1);
