if [ ! -f ./stachu ]; then
  g++ stachu.cc -o stachu
fi

sudo cp ./stachu /usr/local/bin
