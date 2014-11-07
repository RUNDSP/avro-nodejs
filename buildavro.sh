
sudo apt-get install -y libboost-all-dev cmake checkinstall g++ flex bison

cd
git clone https://github.com/apache/avro.git
cd avro
git checkout release-1.7.7
cd lang/c++
cmake -G "Unix Makefiles"
sudo checkinstall -y \
	--install=no \
	--pkgname="avro-cpp" \
	--pkgrelease="1.7.7" \
	--maintainer="mplacentra@runads.com" \
	--requires="flex,bison" \
	--addso=yes

# mv avro-cpp_20141023-1.7.7_amd64.deb avro-cpp_trusty_20141023-1.7.7_amd64.deb
# sudo dpkg -i avro-cpp_trusty_20141023-1.7.7_amd64.deb

cd
git clone https://github.com/RUNDSP/avro-nodejs.git
cd avro-nodejs
# fix bindings.gyp
npm install -g node-gyp
node-gyp configure build
# npm install mocha
# NODE_ENV=test node_modules/.bin/mocha --reporter dot tests/AvroSync.js

# for install:
# sudo apt-get install -y libfl-dev flex bison libboost-dev
