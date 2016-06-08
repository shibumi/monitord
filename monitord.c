/* monitord.c - a simple colourized statusbar for DWM written in C
 * 
 * Copyright (c) 2016 by Christian Rebischke <chris.rebischke@archlinux.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http: *www.gnu.org/licenses/
 *
 *====================================================================== 
 * Author: Christian Rebischke
 * Email : chris.rebischke@archlinux.org
 * Github: www.github.com/Shibumi
 *
 * 
 * 
 *
 * vim:set et sw=8 ts=8 tw=79:
*/

#define TIME_BUFFER_SIZE 26
#define FILE_PATH_SIZE 1024
#define DISK_PATH "/"
#define MAGIC_NUMBER 1073741824
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <X11/Xlib.h>
#include <systemd/sd-bus.h>
#include <sys/statvfs.h>
#include <math.h>

char* datetime(){
        time_t timer;
        struct tm* time_info;
        char* buffer = malloc(TIME_BUFFER_SIZE);
        
        time(&timer);
        time_info = localtime(&timer);
        strftime(buffer, TIME_BUFFER_SIZE, "%Y-%m-%d %I:%M %p", time_info);
        free(buffer);      
        return buffer;
}

char* disk_space(){
        unsigned long total, used, blocksize, free;
        unsigned long usedP;
        struct statvfs vfs;
        char* buffer = malloc(FILE_PATH_SIZE);

        if(statvfs(DISK_PATH, &vfs) != 0){
                fprintf(stderr, "Couldn't stat mountpoint %s for disk space\n");
        } else {
                blocksize = vfs.f_bsize;
                total = vfs.f_blocks * blocksize;
                free = (vfs.f_bfree * blocksize);
                used = ceil((double)(total - free) / MAGIC_NUMBER);
                total = ceil((double)(total) / MAGIC_NUMBER);
                usedP = (used / total) * 100;
                printf("%lu\n", usedP);
                printf("D: %lu / %lu\n", used, total);
        }
        return "";
}

int main(){
        disk_space();
        return 0;
}
