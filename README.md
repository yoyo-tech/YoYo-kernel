# YoYo-kernel
YoYo - operating system for ARM processors. The basic and primary testing platform is Raspberry PI with max level of expansion(Ethernet, WiFi, etc.). Our next testing platforms are asus tinker board, beagle bone, etc. We try to do "PC with ARMs" era, and why we think that we can commercially succeed? We think that way because the YoYo will provide and maintain 100% compatibility with currently existing Windows applications! The kernel of YoYo itself will be very light, monolithic and unix-like designed. We will be developing very comfortable for programming GUI subsystem based on Java and XML.

# Some coding conventions

These brackets: if(condition) {

}
                
instead of these:                
if(condition)

{

}

                
camelCase for variables

CamelCase for type names

Typedefs for structs

For example arm/rand.h can use gpio.h by #include "gpio.h", but musn't include system header from yoyo/someHeader.h. There is single exception in that rule - every file can include yoyo/status.h

NO RETURNING INTEGER AS STATUS FROM FUNCTION! Make use of yoyo/status.h.

# Main people working at kernel

Grzegorz "gjm" Malyska

Sundara Vinayagam

Jakub "XVoir" Niesciur

James Uy

Aravind

Devi Prasad

Marimuthu Veeramuthu

Rony Paul

Shaik Aleem Ur Rehaman

# Blacklisted people

Milosz Komada

Bartosz Gonder

Bartlomiej Rzepecki