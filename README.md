camin
=====

C implementation of amin www.projectamin.org , intending to follow current Perl OO / inheritance patterns as much as possible.

Installation 
=====

Installation 

Requires libuv, libxml2, ecore and eo libraries.

Libxml2 install via distro etc.

Grab Libuv 

https://github.com/joyent/libuv

./autoconf && ./configure --prefix=/usr && make && make install

Grab EFL 

git clone http://git.enlightenment.org/core/efl.git/

./autoconf --prefix=/usr && make && make install 

Build camin 

./autoconf --prefix=/usr && make && make install 
