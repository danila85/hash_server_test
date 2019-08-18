How to build on Ubuntu 16:

# install packages
sudo apt-get install cmake libboost-all-dev libgtest-dev
# go to GTest folder
cd /usr/src/gtest
# Let's build gtest libraries
sudo cmake CMakeLists.txt
sudo make
# Copy static gtest libraries to our /usr/lib folder
sudo cp *.a /usr/lib
# build Server project
cd <path_to_sources>
mkdir build
cd build
cmake ..
make
make test