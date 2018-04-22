camin
=====

C implementation of amin www.projectamin.org , intending to follow current Perl OO / inheritance patterns as much as possible.

Installation 
=====

Installation 

Requires libuv, libxml2, efl libraries.

Libxml2 install via distro etc.

Libuv install via distro ( libuv1-dev on debian / ubuntu )

Grab EFL 

`git clone http://git.enlightenment.org/core/efl.git/`

`mkdir build`

`cd build`

`meson ../`

`ninja`

`sudo ninja install`


Build camin 

mkdir build

cd build

cmake ..

make && sudo make install
